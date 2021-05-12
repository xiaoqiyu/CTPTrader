#include <iostream>
#include "QTStrategyBase.h"

int QTStrategyBase::init(std::vector<std::string>&  _v_ins, const std::string _conf_file_name)
{
	//初始
	FileName _conf_file = {'\0'};
	// snprintf(_conf_file, 100, "conf/%s.ini", argv[1]);

	snprintf(_conf_file, 100, "conf/%s.ini", _conf_file_name.c_str());
	INIReader reader(_conf_file);
	if (reader.ParseError() != 0)
	{
		std::cout << "Can't load config file in current directory:" << _conf_file << std::endl;
		return 1;
	}

	char mdAddr[40];
	char ch[40];

	//CTP Trader handler init
	this->p_trader_handler = new CTPTraderHandler();
	this->p_trader_handler->CreateFtdcTraderApi();
	this->p_trader_handler->RegisterFront(strcpy(ch, reader.Get("td", "FrontAddr", "127.0.0.1:1234").c_str()));
	this->p_trader_handler->init();
	sleep(5);

	this->broker_id = reader.Get("user", "BrokerID", "9999");
	this->user_id = reader.Get("user", "UserID", "123456");

	std::cout << "===============Start CTP Authenticate================" << std::endl;
	CThostFtdcReqAuthenticateField reqAuth = {0};
	strcpy(reqAuth.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
	strcpy(reqAuth.UserID, reader.Get("user", "UserID", "123456").c_str());
	strcpy(reqAuth.AuthCode, reader.Get("user", "AuthCode", "!@#$%^&*").c_str());
	strcpy(reqAuth.AppID, reader.Get("user", "AppID", "MyProgram").c_str());

	this->p_trader_handler->ReqAuthenticate(&reqAuth, nRequestID++);
	sleep(5);

	std::cout << "==================Start CTP Login====================" << std::endl;
	CThostFtdcReqUserLoginField reqUserLogin = {0};
	strcpy(reqUserLogin.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
	strcpy(reqUserLogin.UserID, reader.Get("user", "UserID", "123456").c_str());
	strcpy(reqUserLogin.Password, reader.Get("user", "Password", "123456").c_str());
	strcpy(reqUserLogin.MacAddress, reader.Get("user", "MacAddress", "123456").c_str());
	strcpy(reqUserLogin.UserProductInfo, reader.Get("user", "UserProductInfo", "123456").c_str());

	this->p_trader_handler->ReqUserLogin(&reqUserLogin, nRequestID++);
	sleep(5);

	std::string trading_date = this->p_trader_handler->getTradingDay();
	std::cout << "Trading date is: " << trading_date << endl;

	//CTP MD init
	this->p_md_handler = new CTPMdHandler();
	this->p_md_handler->set_config(_conf_file);
	this->p_md_handler->CreateFtdcMdApi();
	this->p_md_handler->RegisterFront(strcpy(mdAddr, reader.Get("md", "FrontMdAddr", "127.0.0.1:1234").c_str()));
	std::cout<<"in qt strategy:"<<_v_ins.size()<<std::endl;
	this->p_md_handler->init(_v_ins);

	//data/order thread init
	this->data_thread = thread(&QTStrategyBase::on_tick, this);
	this->order_thread = thread(&QTStrategyBase::process_order, this);

	int cnt = 0;
	//private varilbe init
	for(auto iter = _v_ins.begin(); iter!=_v_ins.end(); ++iter)
	{
		std::string _instrumentid = *iter;
		this->v_instrummentID.push_back(_instrumentid);
		FileName mkt_depth_file_name = {'\0'};
		FileName kline_file_name = {'\0'};
		sprintf(mkt_depth_file_name, "cache/%s_depth_market_data_%s.txt", _instrumentid.c_str(), trading_date.c_str());
		sprintf(kline_file_name, "cache/%s_kline_market_data_%s.txt", _instrumentid.c_str(), trading_date.c_str());
		std::ofstream mkt_depth_outfile;
		std::ofstream  kline_outfile;
		// mkt_depth_outfile.open(mkt_depth_file_name, std::ios::app); // append mode
		// kline_outfile.open(kline_file_name, std::ios::app);
		m_filename_idx.insert(std::pair<std::string, int>(_instrumentid, cnt));
		m_depth_filename.insert(std::pair<std::string, std::string>(_instrumentid, mkt_depth_file_name));
		m_kline_filename.insert(std::pair<std::string, std::string>(_instrumentid, kline_file_name));
		// std::cout<<"before push back mkt depth file:"<<&mkt_depth_outfile<<this->v_depth_outfile.size()<<std::endl;
		// std::ofstream * p_finstr = &mkt_depth_outfile;
		// std::cout<<p_finstr<<" write to file:"<<mkt_depth_file_name<<std::endl;
		// p_finstr->write(this->user_id.c_str(), this->user_id.length()+1);
		// v_depth_outfile.push_back(&mkt_depth_outfile);
		// std::cout<<"after push back mkt depth file:"<<&mkt_depth_outfile<<this->v_depth_outfile.size()<<std::endl;
		// v_kline_outfile.push_back(&kline_outfile);
		TickToKlineHelper *p_kline_helper =  new TickToKlineHelper();
		v_t2k_helper.push_back(p_kline_helper);
		cnt ++;
	}
	
	// p_kline_helper = new TickToKlineHelper();
	// p_mktdata_queue = new DataQueue();
	this->p_order_queue = new DataQueue();
	this->active_ = true;
	return 0;
};


void QTStrategyBase::on_tick()
{
	try
	{
		while (this->active_)
		{
			DataField data = this->p_md_handler->get_data_queue()->pop();
			switch (data.data_type)
			{
			case FDEPTHMKT: //期货深度行情数据
			{
				// std::cout<<"in on_tick:"<<data.data_type<<std::endl;

				if (data._data)
				{
					CThostFtdcDepthMarketDataField *pDepthMarketData = reinterpret_cast<CThostFtdcDepthMarketDataField *>(data._data);
					this->calculate_signal();//calculate signal details will be deterimined by subclass,buy specific strategy
					this->calculate_factors(pDepthMarketData, 7200);//this could be overwritten by subclass
					// std::cout << "Save Data: " << pDepthMarketData->InstrumentID<<std::endl;//减少IO阻塞
					// std::cout<<"get fstream index:"<<std::endl;
					int _idx = this->m_filename_idx[pDepthMarketData->InstrumentID];
					// std::cout<<"fstream index is: "<<_idx<<std::endl;
					// std::cout<<"depth file stream pointer:"<<this->v_depth_outfile.size()<<std::endl;
					// std::ofstream* p_f = reinterpret_cast<std::ofstream*>(this->v_depth_outfile[_idx]);
					// std::cout<<"file stream pointer:"<<p_f<<std::endl;
					// std::string str = formatString("%s,%s,%s.%d,%f,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%d,%f,%d,%f,%f,%f\n",
					// 								pDepthMarketData->InstrumentID,
					// 								pDepthMarketData->ActionDay,
					// 								pDepthMarketData->UpdateTime,pDepthMarketData->UpdateMillisec,
					// 								pDepthMarketData->LastPrice,
					// 								pDepthMarketData->PreSettlementPrice,
					// 								pDepthMarketData->PreClosePrice,
					// 								pDepthMarketData->OpenPrice,
					// 								pDepthMarketData->HighestPrice,
					// 								pDepthMarketData->LowestPrice,
					// 								pDepthMarketData->AveragePrice,		
					// 								// pDepthMarketData->ClosePrice,
					// 								pDepthMarketData->Volume,
					// 								pDepthMarketData->Turnover,
					// 								// pDepthMarketData->SettlementPrice ,
					// 								pDepthMarketData->UpperLimitPrice ,
					// 								pDepthMarketData->LowerLimitPrice,
					// 								pDepthMarketData->BidPrice1 ,
					// 								pDepthMarketData->BidVolume1 ,
					// 								pDepthMarketData->AskPrice1 ,
					// 								pDepthMarketData->AskVolume1 ,
					// 								pDepthMarketData->PreOpenInterest ,
					// 								pDepthMarketData->OpenInterest ,
					// 								pDepthMarketData->PreDelta
					// 								// pDepthMarketData->CurrDelta
					// 								);
					std::string _depth_file_name = this->m_depth_filename[pDepthMarketData->InstrumentID];
					std::ofstream _depth_file;
					_depth_file.open(_depth_file_name, std::ios::app);
					_depth_file<< pDepthMarketData->InstrumentID << ","
											<< pDepthMarketData->ActionDay << ","
											<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << ","
											<< pDepthMarketData->LastPrice << ","
											<< pDepthMarketData->PreSettlementPrice << ","
											<< pDepthMarketData->PreClosePrice << ","
											<< pDepthMarketData->OpenPrice << ","
											<< pDepthMarketData->HighestPrice << ","
											<< pDepthMarketData->LowestPrice << ","
											<< pDepthMarketData->AveragePrice << ","
											// << pDepthMarketData->ClosePrice << ","
											<< pDepthMarketData->Volume << ","
											<< pDepthMarketData->Turnover << ","
											// << pDepthMarketData->SettlementPrice << ","
											<< pDepthMarketData->UpperLimitPrice << ","
											<< pDepthMarketData->LowerLimitPrice << ","
											<< pDepthMarketData->BidPrice1 << ","
											<< pDepthMarketData->BidVolume1 << ","
											<< pDepthMarketData->AskPrice1 << ","
											<< pDepthMarketData->AskVolume1 << ","
											<< pDepthMarketData->PreOpenInterest << ","
											<< pDepthMarketData->OpenInterest << ","
											<< pDepthMarketData->PreDelta << ","
											// << pDepthMarketData->CurrDelta << ","
											<< std::endl;

					delete pDepthMarketData;
					_depth_file.close();
					KLineDataType *p_kline_data = new KLineDataType();

					bool ret = this->v_t2k_helper[_idx]->KLineFromRealtimeData(pDepthMarketData, p_kline_data);

					if(ret)
					{
					// 	std::string str1 = formatString("%s,%s,%f,%f,%f,%f,%d\n",
					// 								pDepthMarketData->InstrumentID,
					// 								pDepthMarketData->UpdateTime,
					// 								p_kline_data->open_price,
					// 								p_kline_data->high_price,
					// 								p_kline_data->low_price,	
					// 								p_kline_data->close_price,
					// 								p_kline_data->volume);
						// std::ofstream* p_ff = this->v_kline_outfile[_idx];
						// std::cout<<"f stream pointer:"<<p_ff<<std::endl;
						// p_ff->write(str1.c_str(), str1.length());
						std::string _kline_file_name1 = this->m_kline_filename[pDepthMarketData->InstrumentID];
						std::ofstream _kline_file;
						_kline_file.open(_kline_file_name1, std::ios::app);
						_kline_file<<pDepthMarketData->InstrumentID << ","
													<<pDepthMarketData->UpdateTime << ","
													<<p_kline_data->open_price << ","
													<<p_kline_data->high_price << ","
													<<p_kline_data->low_price << ","
													<<p_kline_data->close_price << ","
													<<p_kline_data->volume<< std::endl;
						_kline_file.close();

					}
					delete p_kline_data;
				}
				if (data.error)
				{
					std::cout <<"handle error in market data subscribe" << std::endl;
					// delete data.error;
				}

				break;
			}
			default:
				break;
			}
		}
	}
	catch (const TerminatedError &)
	{
	}
}

void QTStrategyBase::calculate_kline(){};


void QTStrategyBase::start()
{
	this->start_ = true;
	this->p_md_handler->SubscribeMarketData();

}


void QTStrategyBase::insert_limit_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType order_ref,  TThostFtdcDirectionType direction,TThostFtdcInstrumentIDType instrumentID)
{
	CThostFtdcInputOrderField * p_input_order_field = new CThostFtdcInputOrderField();
	strcpy(p_input_order_field->InstrumentID, instrumentID);
	strcpy(p_input_order_field->OrderRef, order_ref);
	p_input_order_field->VolumeTotalOriginal = volume;
	p_input_order_field->LimitPrice = limit_price;
	p_input_order_field->Direction = direction;
	p_input_order_field->OrderPriceType = '2';
	DataField data = DataField();
	data.data_type = ORDERFIELD;
	data._data = p_input_order_field;
	this->p_order_queue->push(data);
	// this->p_trader_handler->ReqOrderInsert(&input_order_field, nRequestID);
}
void QTStrategyBase::insert_market_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType order_ref, TThostFtdcOrderPriceTypeType order_price_type, TThostFtdcDirectionType direction, TThostFtdcInstrumentIDType instrumentID)
{
	CThostFtdcInputOrderField * p_input_order_field = new CThostFtdcInputOrderField();
	strcpy(p_input_order_field->InstrumentID, instrumentID);
	strcpy(p_input_order_field->OrderRef, order_ref);
	p_input_order_field->VolumeTotalOriginal = volume;
	p_input_order_field->LimitPrice = limit_price;
	p_input_order_field->Direction = direction;
	p_input_order_field->OrderPriceType = order_price_type;
	DataField data = DataField();
	data.data_type = ORDERFIELD;
	data._data = p_input_order_field;
	this->p_order_queue->push(data);
	// this->p_trader_handler->ReqOrderInsert(&input_order_field, nRequestID);
}

int QTStrategyBase::get_instrument_by_product(std::string product_id)
{
	std::cout<<"Query Instrument for productID:"<<product_id<<std::endl;
	CThostFtdcQryInstrumentField pQryInstrument = {0};
	std::strcpy(pQryInstrument.InstrumentID, product_id.c_str());
	return this->p_trader_handler->ReqQryInstrument(&pQryInstrument, nRequestID++);
}

int QTStrategyBase::get_investor_position(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryInvestorPositionField investor_pos_fields = {0};
	std::strcpy(investor_pos_fields.InvestorID, investor_id.c_str());
	std::strcpy(investor_pos_fields.BrokerID, broker_id.c_str());
	return this->p_trader_handler->ReqQryInvestorPosition(&investor_pos_fields, nRequestID++);
}

void QTStrategyBase::stop()
{
	//TODO stop data_thread, but the ctp instance is still active
	this->data_thread.join();
	this->order_thread.join();
    sleep(3);
}


void QTStrategyBase::release()
{
	delete p_order_queue;
	for(auto iter=v_t2k_helper.begin(); iter!=v_t2k_helper.end(); ++iter)
	{
		delete *iter;
	}

	//TODO this will be added if maintain fstream pointer when file open in init and close in exit
	// for(auto iter=v_depth_outfile.begin(); iter!=v_depth_outfile.end();++iter)
	// {
	// 	(*iter)->close();
	// }
	// for(auto iter=v_kline_outfile.begin(); iter!=v_kline_outfile.end(); ++iter)
	// {
	// 	(*iter)->close();
	// }
	this->p_md_handler->exit();
	this->p_trader_handler->exit();
}

//this could be overwritten by subclass, this is the basic factor
void QTStrategyBase::calculate_factors(CThostFtdcDepthMarketDataField *pDepthMarketData, int cache_len)
{
	if (this->v_factor.size()>=cache_len)
	{
		this->v_factor.clear();
	}
	std::vector<float> v_factor_val;
	v_factor_val.push_back(pDepthMarketData->LastPrice);
	v_factor_val.push_back(pDepthMarketData->AveragePrice);
	v_factor_val.push_back(pDepthMarketData->BidPrice1-pDepthMarketData->AskPrice1);
	this->v_factor.push_back(v_factor_val);
}


std::vector<std::string> QTStrategyBase::getInstrumentID()
{
	return this->v_instrummentID;
}

void QTStrategyBase::setInstrumentID(std::vector<std::string> v_instrumentid)
{
	if (!v_instrummentID.empty())
	{
		for(auto iter=v_instrummentID.begin(); iter!=v_instrummentID.end(); ++iter)
		{
			this->v_instrummentID.push_back(*iter);
		}
	}
}

//TODO to add the check logic
bool QTStrategyBase::verify_order_condition()
{
	return true;
}

void QTStrategyBase::process_order()
{
	while(this->active_)
	{
		DataField data = this->p_order_queue->pop();
		switch (data.data_type)
			{
			case ORDERFIELD:
				if (data._data)
				{
					CThostFtdcInputOrderField *p_order_field_ = reinterpret_cast<CThostFtdcInputOrderField *>(data._data);
					//TODO: verify account status and check order condition
					this->verify_order_condition();
					this->p_trader_handler->ReqOrderInsert(p_order_field_, nRequestID);
				}
			}
	}
}

