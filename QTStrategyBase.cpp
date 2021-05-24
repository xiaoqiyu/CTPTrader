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
	// std::cout<<"in qt strategy:"<<_v_ins.size()<<std::endl;
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
		sprintf(mkt_depth_file_name, "cache/%s_depth_market_data_%s.recordio", _instrumentid.c_str(), trading_date.c_str());
		sprintf(kline_file_name, "cache/%s_kline_market_data_%s.recordio", _instrumentid.c_str(), trading_date.c_str());
		std::ofstream* p_mkt_depth_outfile = new std::ofstream();
		// FILE* fp_depth_mkt;
		std::ofstream* p_kline_outfile = new std::ofstream();
		// FILE* fp_kline; 
		p_mkt_depth_outfile->open(mkt_depth_file_name, std::ios::app|std::ios::binary); // append mode
		// fp_depth_mkt = fopen(mkt_depth_file_name, "a");
		// fp_kline = fopen(kline_file_name, "a");
		p_kline_outfile->open(kline_file_name, std::ios::app|std::ios::binary);
		m_filename_idx.insert(std::pair<std::string, int>(_instrumentid, cnt));
		m_depth_filename.insert(std::pair<std::string, std::string>(_instrumentid, mkt_depth_file_name));
		m_kline_filename.insert(std::pair<std::string, std::string>(_instrumentid, kline_file_name));
		// v_depth_outfile.push_back(p_mkt_depth_outfile);

		// std::ofstream ofs(path, std::ios::binary);
  		recordio::RecordWriter _depth_mkt_writer(p_mkt_depth_outfile);
		v_depth_writer.push_back(_depth_mkt_writer);

		recordio::RecordWriter _kline_writer(p_kline_outfile);
		v_kline_writer.push_back(_kline_writer);

		// if (NULL != fp_depth_mkt){v_depth_file_handler.push_back(fp_depth_mkt);}
		// if(NULL != fp_kline){v_kline_file_handler.push_back(fp_kline);}
		// v_kline_outfile.push_back(p_kline_outfile);
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
		while (true)
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
					// this->calculate_signal();//calculate signal details will be deterimined by subclass,buy specific strategy
					this->calculate_factors(pDepthMarketData, 7200);//this could be overwritten by subclass
					// std::cout << "Save Data: " << pDepthMarketData->InstrumentID<<std::endl;//减少IO阻塞
					// std::cout<<"get fstream index:"<<std::endl;
					int _idx = this->m_filename_idx[pDepthMarketData->InstrumentID];
					
					// fwrite(pDepthMarketData, 1, sizeof(CThostFtdcDepthMarketDataField),this->v_depth_file_handler[_idx]);
					v_depth_writer[_idx].WriteBuffer(reinterpret_cast<const char*>(pDepthMarketData), sizeof(CThostFtdcDepthMarketDataField));
					KLineDataType *p_kline_data = new KLineDataType();
					bool ret = this->v_t2k_helper[_idx]->KLineFromRealtimeData(pDepthMarketData, p_kline_data);
					int w_kline;
					if(ret)
					{
						// w_kline = fwrite(p_kline_data, 1, sizeof(KLineDataType), this->v_kline_file_handler[_idx]);
						int ret_write_buffer = v_kline_writer[_idx].WriteBuffer(reinterpret_cast<const char*>(p_kline_data), sizeof(KLineDataType));
					}
					delete p_kline_data;
					delete pDepthMarketData;
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


std::tuple<std::vector<std::string>, std::vector<std::string>> QTStrategyBase::get_instrument_by_product(std::string product_id)
{
	std::cout<<"Query Instrument for productID:"<<product_id<<std::endl;
	CThostFtdcQryInstrumentField pQryInstrument = {0};
	std::strcpy(pQryInstrument.InstrumentID, product_id.c_str());
	//TODO check return value
	int ret = this->p_trader_handler->ReqQryInstrument(&pQryInstrument, nRequestID++);
	return std::make_tuple(this->p_trader_handler->GetFutureInstrumentID(),this->p_trader_handler->GetOptionInstrumentID());
	// return this->p_trader_handler->GetFutureInstrumentID();

}

int QTStrategyBase::get_investor_position(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryInvestorPositionField investor_pos_fields = {0};
	std::strcpy(investor_pos_fields.InvestorID, investor_id.c_str());
	std::strcpy(investor_pos_fields.BrokerID, broker_id.c_str());
	return this->p_trader_handler->ReqQryInvestorPosition(&investor_pos_fields, nRequestID++);
}

int QTStrategyBase::get_account(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryTradingAccountField trading_account_fields = {0};
	std::strcpy(trading_account_fields.AccountID, investor_id.c_str());
	std::strcpy(trading_account_fields.BrokerID, broker_id.c_str());
	int ret_req = this->p_trader_handler->ReqQryTradingAccount(&trading_account_fields, nRequestID++);	
	std::cout<<"Req return is:"<<ret_req<<std::endl;
	return ret_req;
}

int QTStrategyBase::req_trade(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryTradeField trade_fields = {0};
	std::strcpy(trade_fields.InvestorID, investor_id.c_str());
	std::strcpy(trade_fields.BrokerID, broker_id.c_str());
	// int ret_req = this->p_trader_handler->ReqQryTradingAccount(&trade_fields, nRequestID++);	
	int ret_req = this->p_trader_handler->ReqQryTrade(&trade_fields, nRequestID++);
	std::cout<<"Req return is:"<<ret_req<<std::endl;
	return ret_req;
}

int QTStrategyBase::get_depth_mkt(std::string instrument_id)
{
	CThostFtdcQryDepthMarketDataField mkt_fields = {0};
	std::strcpy(mkt_fields.InstrumentID, instrument_id.c_str());
	int ret_req = this->p_trader_handler->ReqQryDepthMarketData(&mkt_fields, nRequestID++);
	std::cout<<"Req return in depth market is:"<<ret_req<<std::endl;
	return ret_req;
}

int QTStrategyBase::get_position_details(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryInvestorPositionDetailField pos_detail_fields = {0};
	std::strcpy(pos_detail_fields.InvestorID, investor_id.c_str());
	std::strcpy(pos_detail_fields.BrokerID, broker_id.c_str());
	int ret_req = this->p_trader_handler->ReqQryInvestorPositionDetail(&pos_detail_fields,nRequestID++);
	std::cout<<"Req return in position details is:"<<ret_req<<std::endl;
	return ret_req;
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
	for(auto  iter=v_depth_file_handler.begin(); iter!=v_depth_file_handler.end();++iter)
	{
		fclose(*iter);
	}
	for(auto iter=v_kline_file_handler.begin(); iter!=v_kline_file_handler.end();++iter)
	{
		fclose(*iter);
	}
	for(auto iter=v_depth_writer.begin(); iter!=v_depth_writer.end(); ++iter)
	{
		(*iter).Close();
	}
	for(auto  iter=v_kline_writer.begin(); iter!=v_kline_writer.end(); ++iter)
	{
		(*iter).Close();
	}
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

