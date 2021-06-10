#include <iostream>
#include "QTStrategyBase.h"

bool cmp_max(std::pair<std::string, double> x, std::pair<std::string, double>y)
{
	return x.second > y.second;
}
void cache_main_instruments(std::vector<std::string> _v_instrument_id);

int QTStrategyBase::init(std::vector<std::string>&  _v_product_ids, const std::string _conf_file_name)
{
	//初始
	FileName _conf_file = {'\0'};
	// snprintf(_conf_file, 100, "conf/%s.ini", argv[1]);

	// snprintf(_conf_file, 50, _conf_file_name.c_str());
	strcpy(_conf_file, _conf_file_name.c_str());
	INIReader reader(_conf_file);
	if (reader.ParseError() != 0)
	{
		LOG(FATAL)<< "Fail to load config file in current directory:"<< _conf_file;
		return 1;
	}

	char mdAddr[40];
	char ch[40];

	this->task_tag = _v_product_ids[0];
	//CTP Trader handler init
	this->p_trader_handler = new CTPTraderHandler();
	this->p_trader_handler->CreateFtdcTraderApi();
	this->p_trader_handler->RegisterFront(strcpy(ch, reader.Get("td", "FrontAddr", "127.0.0.1:1234").c_str()));
	this->p_trader_handler->init(task_tag);
	sleep(5);

	this->broker_id = reader.Get("user", "BrokerID", "9999");
	this->user_id = reader.Get("user", "UserID", "123456");

	LOG(INFO) << "Start CTP Authenticate.......";
	CThostFtdcReqAuthenticateField reqAuth = {0};
	strcpy(reqAuth.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
	strcpy(reqAuth.UserID, reader.Get("user", "UserID", "123456").c_str());
	strcpy(reqAuth.AuthCode, reader.Get("user", "AuthCode", "!@#$%^&*").c_str());
	strcpy(reqAuth.AppID, reader.Get("user", "AppID", "MyProgram").c_str());

	this->p_trader_handler->ReqAuthenticate(&reqAuth, nRequestID++);
	sleep(5);

	LOG(INFO)<< "Start CTP Login......" << std::endl;
	CThostFtdcReqUserLoginField reqUserLogin = {0};
	strcpy(reqUserLogin.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
	strcpy(reqUserLogin.UserID, reader.Get("user", "UserID", "123456").c_str());
	strcpy(reqUserLogin.Password, reader.Get("user", "Password", "123456").c_str());
	strcpy(reqUserLogin.MacAddress, reader.Get("user", "MacAddress", "123456").c_str());
	strcpy(reqUserLogin.UserProductInfo, reader.Get("user", "UserProductInfo", "123456").c_str());

	this->p_trader_handler->ReqUserLogin(&reqUserLogin, nRequestID++);
	sleep(5);

	std::string trading_date = this->p_trader_handler->getTradingDay();
	LOG(INFO)<< "Trading date is: " << trading_date;

	this->cache_main_instruments(_v_product_ids);
	for(auto it=v_main_contract_ids.begin(); it!=v_main_contract_ids.end();++it)
	{
		LOG(INFO)<<"push main contract id in init:"<<(*it);
		this->v_instrummentID.push_back((*it));
	}
	for(auto it=v_option_ids.begin(); it!=v_option_ids.end();++it)
	{
		LOG(INFO)<<"push option id in init(strategy base):"<<(*it);
		this->v_instrummentID.push_back((*it));
	}
	

	//CTP MD init
	this->p_md_handler = new CTPMdHandler();
	this->p_md_handler->set_config(_conf_file);
	this->p_md_handler->CreateFtdcMdApi();
	this->p_md_handler->RegisterFront(strcpy(mdAddr, reader.Get("md", "FrontMdAddr", "127.0.0.1:1234").c_str()));
	this->p_md_handler->init(this->v_instrummentID);

	//data/order thread init
	this->data_thread = thread(&QTStrategyBase::on_tick, this);
	this->order_thread = thread(&QTStrategyBase::process_order, this);



	int cnt = 0;
	//private varilbe init
	for(auto iter = this->v_instrummentID.begin(); iter!=this->v_instrummentID.end(); ++iter)
	{

		// std::string _instrumentid = *iter;
		// FileName mkt_depth_file_name = {'\0'};
		// FileName kline_file_name = {'\0'};
		// sprintf(mkt_depth_file_name, "cache/mkt/%s_depth_market_data_%s.recordio", _instrumentid.c_str(), trading_date.c_str());
		// sprintf(kline_file_name, "cache/mkt/%s_kline_market_data_%s.recordio", _instrumentid.c_str(), trading_date.c_str());
		// std::ofstream* p_mkt_depth_outfile = new std::ofstream();
		// std::ofstream* p_kline_outfile = new std::ofstream();
		
		
		// p_mkt_depth_outfile->open(mkt_depth_file_name, std::ios::app|std::ios::binary); // append mode
	
		// p_kline_outfile->open(kline_file_name, std::ios::app|std::ios::binary);
		// m_filename_idx.insert(std::pair<std::string, int>(_instrumentid, cnt));
		// m_depth_filename.insert(std::pair<std::string, std::string>(_instrumentid, mkt_depth_file_name));
		// m_kline_filename.insert(std::pair<std::string, std::string>(_instrumentid, kline_file_name));
	

  		// recordio::RecordWriter _depth_mkt_writer(p_mkt_depth_outfile);
		// v_depth_writer.push_back(_depth_mkt_writer);

		// recordio::RecordWriter _kline_writer(p_kline_outfile);
		// v_kline_writer.push_back(_kline_writer);

		TickToKlineHelper *p_kline_helper =  new TickToKlineHelper();
		v_t2k_helper.push_back(p_kline_helper);
		cnt ++;
	}
	std::ofstream * p_depth_mkt = new std::ofstream();
	FileName _depth_mkt_filename = {'\0'};
	sprintf(_depth_mkt_filename, "cache/mkt/%s_depth_market_data_%s.recordio", this->task_tag.c_str(), trading_date.c_str());
	p_depth_mkt->open(_depth_mkt_filename, std::ios::app|std::ios::binary);
	// recordio::RecordWriter _depth_mkt_writer(p_depth_mkt);
	this->p_depth_mkt_writer = new recordio::RecordWriter(p_depth_mkt);
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
				if (data._data)
				{
					CThostFtdcDepthMarketDataField *pDepthMarketData = reinterpret_cast<CThostFtdcDepthMarketDataField *>(data._data);
					this->calculate_signal();//calculate signal details will be deterimined by subclass,buy specific strategy
					this->calculate_factors(pDepthMarketData, 7200);//this could be overwritten by subclass
				
					// int _idx = this->m_filename_idx[pDepthMarketData->InstrumentID];
					// v_depth_writer[_idx].WriteBuffer(reinterpret_cast<const char*>(pDepthMarketData), sizeof(CThostFtdcDepthMarketDataField));
					this->p_depth_mkt_writer->WriteBuffer(reinterpret_cast<const char*>(pDepthMarketData), sizeof(CThostFtdcDepthMarketDataField));

					// KLineDataType *p_kline_data = new KLineDataType();
					// bool ret = this->v_t2k_helper[_idx]->KLineFromRealtimeData(pDepthMarketData, p_kline_data);
					// int w_kline;
					// if(ret)
					// {
					// 	int ret_write_buffer = v_kline_writer[_idx].WriteBuffer(reinterpret_cast<const char*>(p_kline_data), sizeof(KLineDataType));
					// }
					// delete p_kline_data;
					delete pDepthMarketData;
				}
				if (data.error)
				{
					// delete data.error;
					LOG(ERROR)<<"ERROR msg in mkt data subscribe";
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
	CThostFtdcQryInstrumentField pQryInstrument = {0};
	std::strcpy(pQryInstrument.InstrumentID, product_id.c_str());
	//TODO check return value
	int ret = this->p_trader_handler->ReqQryInstrument(&pQryInstrument, nRequestID++);
	return std::make_tuple(this->p_trader_handler->GetFutureInstrumentID(),this->p_trader_handler->GetOptionInstrumentID());
	// return this->p_trader_handler->GetFutureInstrumentID();

}

std::vector<CThostFtdcInvestorPositionField *> QTStrategyBase::get_investor_position(std::string investor_id, std::string broker_id)
{
	return p_trader_handler->get_investor_position(investor_id, broker_id);
}

std::vector<CThostFtdcTradingAccountField*> QTStrategyBase::get_account(std::string investor_id, std::string broker_id)
{
	return p_trader_handler->get_account(investor_id, broker_id);
}

int QTStrategyBase::req_trade(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryTradeField trade_fields = {0};
	std::strcpy(trade_fields.InvestorID, investor_id.c_str());
	std::strcpy(trade_fields.BrokerID, broker_id.c_str());
	// int ret_req = this->p_trader_handler->ReqQryTradingAccount(&trade_fields, nRequestID++);	
	int ret_req = this->p_trader_handler->ReqQryTrade(&trade_fields, nRequestID++);
	LOG(INFO)<<"Req return in req_trade:"<<ret_req;
	return ret_req;
}

// int QTStrategyBase::get_depth_mkt(std::string instrument_id)
// {
// 	CThostFtdcQryDepthMarketDataField mkt_fields = {0};
// 	std::strcpy(mkt_fields.InstrumentID, instrument_id.c_str());
// 	int ret_req = this->p_trader_handler->ReqQryDepthMarketData(&mkt_fields, nRequestID++);
// 	std::cout<<"Req return in depth market is:"<<ret_req<<std::endl;
// 	return ret_req;
// }

int QTStrategyBase::get_position_details(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryInvestorPositionDetailField pos_detail_fields = {0};
	std::strcpy(pos_detail_fields.InvestorID, investor_id.c_str());
	std::strcpy(pos_detail_fields.BrokerID, broker_id.c_str());
	int ret_req = this->p_trader_handler->ReqQryInvestorPositionDetail(&pos_detail_fields,nRequestID++);
	LOG(INFO)<<"Req return in position details is:"<<ret_req;
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

	// for(auto iter=v_depth_writer.begin(); iter!=v_depth_writer.end(); ++iter)
	// {
	// 	(*iter).Close();
	// }
	// for(auto  iter=v_kline_writer.begin(); iter!=v_kline_writer.end(); ++iter)
	// {
	// 	(*iter).Close();
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
	
	std::vector<double> v_factor_val;
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

void QTStrategyBase::cache_main_instruments(std::vector<std::string> _v_instrument_id)
{
	std::vector<CThostFtdcInstrumentField*> ret_instruments = get_instruments(_v_instrument_id);
	std::vector<CThostFtdcDepthMarketDataField*> ret_depth_market_data = get_market_datas(_v_instrument_id);
	std::unordered_map<std::string, double> m_ins2openinterest;
	//cache {instrument_id:open_interest}
	for(auto it=ret_depth_market_data.begin(); it!=ret_depth_market_data.end();++it)
	{
		std::string _ins_id = (*it)->InstrumentID;
		CThostFtdcDepthMarketDataField* p_tmp = reinterpret_cast<CThostFtdcDepthMarketDataField*>(*it);
		m_ins2openinterest[_ins_id] = p_tmp->OpenInterest;
	}
	// cal main future contracts group by productid, sort by open interest
	for (auto it=ret_instruments.begin(); it!=ret_instruments.end(); ++it)
	{
		CThostFtdcInstrumentField* p_tmp = reinterpret_cast<CThostFtdcInstrumentField*>(*it);
		if(p_tmp->ProductClass=='1'){//single future 
			if(m_main_futures.find(p_tmp->ProductID)==m_main_futures.end()){//"key not exist"
				m_main_futures.insert(std::pair<std::string, std::string>(p_tmp->ProductID, p_tmp->InstrumentID));
			}else{ //"key exist"
				std::string _prev_ins_id = m_main_futures[p_tmp->ProductID];
				if(m_ins2openinterest.find(_prev_ins_id)==m_ins2openinterest.end()){ 
					m_main_futures.insert(std::pair<std::string, std::string>(p_tmp->ProductID, p_tmp->InstrumentID));
				}else if(m_ins2openinterest.find(p_tmp->InstrumentID)!=m_ins2openinterest.end()){
					if(m_ins2openinterest[p_tmp->InstrumentID] > m_ins2openinterest[_prev_ins_id]){
						m_main_futures[p_tmp->ProductID] = p_tmp->InstrumentID;
					}
				}
			}
		}
	}
	//get main future ids by cal results
	for(const auto& n:m_main_futures)
	{
		LOG(INFO)<<"push  main contract id in cache main contract->"<<n.first<<","<<n.second;
		v_main_contract_ids.push_back(n.second);
	}

	//get target options id 
	std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> m_option_val;
	//{main_contract:[option_id, open_interest]}
	for (auto it=ret_instruments.begin(); it!=ret_instruments.end(); ++it)
	{
		CThostFtdcInstrumentField* p_tmp = reinterpret_cast<CThostFtdcInstrumentField*>(*it);
		if(p_tmp->ProductClass=='2'){//single option
			std::string _underlying_id = p_tmp->UnderlyingInstrID;
			auto it = find(v_main_contract_ids.begin(), v_main_contract_ids.end(), _underlying_id);
			if(it != v_main_contract_ids.end()){ //underlying instrument is in main contract
				if(m_ins2openinterest.find(p_tmp->InstrumentID)!=m_ins2openinterest.end()){
					m_option_val[_underlying_id].push_back(std::pair<std::string, double>(p_tmp->InstrumentID, m_ins2openinterest[p_tmp->InstrumentID]));
				}
			}
		}
	}

	//calculate target option id lst
	for(auto& t:m_option_val){
		LOG(INFO)<<t.first<<"option size:"<<t.second.size();
		sort(t.second.begin(), t.second.end(), [](const std::pair<std::string, double>& x, const std::pair<std::string, double>& y) -> bool {return x.second>=y.second;});
		const auto it = t.second.begin();
		int cnt = 0;
		while(cnt<option_size){
			v_option_ids.push_back((*(it+cnt)).first);
			cnt ++;
		}
	}

	for(auto it=ret_instruments.begin(); it!=ret_instruments.end();++it){
		CThostFtdcInstrumentField* p_tmp = reinterpret_cast<CThostFtdcInstrumentField*>(*it);
		std::string _instrument_id = p_tmp->InstrumentID;
		auto f_it = find(v_main_contract_ids.begin(), v_main_contract_ids.end(), _instrument_id);
		if(f_it!=v_main_contract_ids.end()){
			m_target_instruments.insert(std::pair<std::string, CThostFtdcInstrumentField*>(_instrument_id,p_tmp));
		}
		auto o_it = find(v_option_ids.begin(), v_option_ids.end(), _instrument_id);
		if(o_it!=v_option_ids.end()){
			m_target_instruments.insert(std::pair<std::string, CThostFtdcInstrumentField*>(_instrument_id,p_tmp));
		}
	}
	

	for(auto it =ret_instruments.begin(); it!=ret_instruments.end();++it)
	{
		delete *it;
	}

	for(auto it=ret_depth_market_data.begin(); it!=ret_depth_market_data.end(); ++it)
	{
		delete *it;
	}


}
