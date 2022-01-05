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
	// LOG(INFO)<<"Init Strategy with mode: "<<this->mode<< "conf file: "<<_conf_file_name;
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
	std::string trading_date;

	this->task_tag = _v_product_ids[0];

	//FIXME remove hardcode in the init of factor
	for(int i = 0; i<7;++i) this->v_last_vector.push_back(0.0);
	this->v_last_vector[2] = __DBL_MAX__;
	this->v_last_vector[1] = __DBL_MIN__;

	// TODO SIMTRADE 
	position_limit = 0;

	LOG(INFO)<<"before init ctp td";
	if (this->mode == 2 || this->mode == 0 || this->mode == 1){
		LOG(INFO)<<"Mode 0&2: Init CTP TD";
		//mode 0(subscribe depth market) and mode 2(live trade) need to connect to ctp td; mode 0 for query api, mode 2 for order api 
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

		trading_date = this->p_trader_handler->getTradingDay();
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
	}else{
		LOG(ERROR)<<"Invalid mode";
	}
	LOG(INFO)<<"after init ctp td ";

	LOG(INFO)<<"after init ctp md";

	if(this->mode == 0){//mode 0 need to connect CTPMD to subscribe depth market data
		LOG(INFO)<<"Mode 0: init CTP MD";
		//CTP MD connect and init
		this->p_md_handler = new CTPMdHandler();
		this->p_md_handler->set_config(_conf_file);
		this->p_md_handler->CreateFtdcMdApi();
		this->p_md_handler->RegisterFront(strcpy(mdAddr, reader.Get("md", "FrontMdAddr", "127.0.0.1:1234").c_str()));
		this->p_md_handler->init(this->v_instrummentID);
	}

	LOG(INFO)<<"after init ctp md";

	LOG(INFO)<<"before init simtrade";
	if(this->mode == 1){//mode 1 will connet to simtrade server for simulation
		LOG(INFO)<<"Mode 1: init simtrade";
		//Simtrade connect and init
		// code to connect gm trade trade and login
		// SimTrader mt ("a1128cf0aaa3735b04a2706c8029a562e8c2c6b6"); 
		
		simtrade_ptr.reset(new SimTrader(reader.Get("simtrade", "token", "a1128cf0aaa3735b04a2706c8029a562e8c2c6b6").c_str()));
		// 设置服务地址api.myquant.cn:9000
		simtrade_ptr->set_endpoint ( reader.Get("simtrade", "endpoint", "api.myquant.cn:9000").c_str());
		std::string future_acc = reader.Get("simtrade", "account_id", "a1a91403-2fc2-11ec-bd15-00163e0a4100");		
		simtrade_account_id = future_acc;
		
		// 登录账户id
		simtrade_ptr->login(future_acc.c_str());
		simtrade_ptr->init_positions(future_acc);
		//开始接收事件
		int status = simtrade_ptr->start();
		//判断状态
		if (status == 0)
		{
		    LOG(INFO) << "Connected to simtrade server" << std::endl;
		}
		else
		{
		    LOG(INFO) << "Fail to connect to simtrade server" << std::endl;
		}
	}
	LOG(INFO)<<"after init simtrade";

	//data/order thread init
	if (this->mode == 0){ // start the data thread to process depth markets
		LOG(INFO)<<"Mode 0: Create thread for tick processs";
		this->data_thread = thread(&QTStrategyBase::on_tick, this);
	}else if(this->mode == 1 || this->mode == 2){ // mode 1/2 for sim/live trade, start the thread to insert order fa
		LOG(INFO)<<"Mode 1&2:Create thread to process ordder";

	}

	if (this->mode  == 0){ //mode 0 for kline resample and depth market cache
	    LOG(INFO)<<"Mode 0: create cache writer";
		int cnt = 0;
		//private varilbe init
		for(auto iter = this->v_instrummentID.begin(); iter!=this->v_instrummentID.end(); ++iter)
		{
			TickToKlineHelper *p_kline_helper =  new TickToKlineHelper();
			v_t2k_helper.push_back(p_kline_helper);
			cnt ++;
		}
		std::ofstream * p_depth_mkt = new std::ofstream();
		FileName _depth_mkt_filename = {'\0'};
		sprintf(_depth_mkt_filename, "cache/mkt/%s_depth_market_data_%s.recordio", this->task_tag.c_str(), trading_date.c_str());
		p_depth_mkt->open(_depth_mkt_filename, std::ios::app|std::ios::binary);
		this->p_depth_mkt_writer = new recordio::RecordWriter(p_depth_mkt);									
	} else if (this-> mode == 1 || this->mode ==2){
		LOG(INFO)<<"Mode 1 &2: create order data queue";
		// order data queue for sim/live trade
		this->p_order_queue = new DataQueue();
		this->p_sig = new OrderSignal();
	}else{
		LOG(ERROR)<< "Invalid mode for strategy";
	}
	this->active_ = true;
	return 0;
};

void QTStrategyBase::on_event()
{
	LOG(INFO)<<"Start process signal: on event";
	try
	{
		while(true)
		{
			shm::shared_string v(*char_alloc_ptr);
    		if (p_queue->pop(v))
			{
				std::string msg = v.data();
				std::vector<std::string> v_rev;
				char c = ',';
				std::stringstream sstr(msg);
				std::string token;
				while(getline(sstr, token, c)){
					v_rev.push_back(token);
				}

				if (this->mode == 1){//simtrade
					//FIXME HARDCODE for testing, move account_id to config
					std::string account_id = "a1a91403-2fc2-11ec-bd15-00163e0a4100";
					std::string _symbol = v_rev[0];
					std::string full_symbol = "DCE."+_symbol; //FIXME remove exchange hardcode 
					std::vector<Position *> v_pos = this->simtrade_ptr->get_positions(full_symbol);
					Order _order;
					LOG(INFO)<<"Get position size in strategy:"<<v_pos.size()<<",symbol:"<<full_symbol;
					OrderData* p_orderdata = p_sig->get_signal(v_rev, this->mode, v_pos);
					// LOG(INFO)<<"Get signal in stratege:"<<p_orderdata->status<<","<<p_orderdata->side;
					if(p_orderdata->status == 1 || p_orderdata->status == 2){
						LOG(INFO)<<"Start order volume";
						_order = simtrade_ptr->order_volume(p_orderdata->symbol.c_str(), p_orderdata->volume,p_orderdata->side, p_orderdata->order_type,p_orderdata->position_effect,p_orderdata->price, simtrade_account_id.c_str());
						LOG(INFO)<<"Order return:"<<_order.status<<","<<_order.ord_rej_reason<<","<<_order.ord_rej_reason_detail;
					}
				}//end of mode 1 simtrade 
			}
		}
	}
	catch(const std::exception& e)
	{
		LOG(ERROR)<< e.what() << '\n';
	}
	
}


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
					// this->calculate_factors(pDepthMarketData, 7200);//this could be overwritten by subclass
					//FIXME  HARD CODE for shared memory test
					if(this->task_tag == "eg"){
						// char s[128];
						// int offset = 0;
						// offset += sprintf(s+offset, "%s,", pDepthMarketData->InstrumentID);
						// offset += sprintf(s+offset, "%s,", pDepthMarketData->UpdateTime);
						// offset += sprintf(s+offset, "%d,", pDepthMarketData->UpdateMillisec);
						// offset += sprintf(s+offset, "%d,", pDepthMarketData->Volume);
						// for (auto it = this->v_last_vector.begin(); it!=this->v_last_vector.end();++it){
							// offset += sprintf(s+offset, "%f,", *it);
						// }
						char s[factor_len];
						p_factor->update_factor(pDepthMarketData, s);		
						// LOG(INFO)<<"Got Factor len:"<<strlen(s)<<",value:"<<s;
						p_queue->push(shm::shared_string(s, *char_alloc_ptr));
						
					}
					
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


	if(this->mode == 0){
		LOG(INFO)<<"mode 0: start subscribe mkt data";
		this->p_md_handler->SubscribeMarketData();
	}else if(this->mode == 1){
		LOG(INFO)<<"mode 1: Simtrade, listening to factor";
		this->signal_thread = thread(&QTStrategyBase::on_event, this); 
		this->order_thread = thread(&QTStrategyBase::process_order, this);
	}else if (this->mode == 2){
		LOG(INFO)<<"mode 2: livetrade, listening to factor";
		this->signal_thread = thread(&QTStrategyBase::on_event, this); 
		this->order_thread = thread(&QTStrategyBase::process_order, this);
	}else{
		LOG(ERROR)<<"invalid mode";
	}
	LOG(INFO)<<"end of start in strategy";
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
	if(this->mode == 0){
		LOG(INFO)<<"Mode 0: join data thread";
		this->data_thread.join();
	}else if (this->mode == 1 || this->mode == 2){
		LOG(INFO)<<"Mode 1&2: join order thread";
		this->order_thread.join();
		this->signal_thread.join();
	}else{
		LOG(ERROR)<<"Invalid mode in stop:"<<this->mode;
	}
    sleep(3);
}


void QTStrategyBase::release()
{
	if (this->mode == 0){
		LOG(INFO)<<"Mode 0: delete t2k helper";
		for(auto iter=v_t2k_helper.begin(); iter!=v_t2k_helper.end(); ++iter)
		{
			delete *iter;
		}
		LOG(INFO)<<"Mode 0 in relase:stop CTP MD";
		this->p_md_handler->exit();
	}else if(this->mode == 1 || this->mode==2){
		LOG(INFO)<<"Mode 1&2: delete order queue in release";
		delete p_order_queue;
	}else{
		LOG(INFO)<<"Invalide mode in relase:"<<this->mode;
	}
	LOG(INFO)<<"release:stop CTP TD";
	this->p_trader_handler->exit();
}

//this could be overwritten by subclass, this is the basic factor
void QTStrategyBase::calculate_factors(CThostFtdcDepthMarketDataField *pDepthMarketData, int cache_len)
{
	// FIXME:  the cache method has bug and not efficient
	// if (this->v_factor.size()>=cache_len)
	// {
		// this->v_factor.clear();
	// }
	// 
	// std::vector<double> v_factor_val;
	// v_factor_val.push_back(pDepthMarketData->LastPrice);
	// v_factor_val.push_back(pDepthMarketData->AveragePrice);
	// v_factor_val.push_back(pDepthMarketData->BidPrice1-pDepthMarketData->AskPrice1);
	// this->v_factor.push_back(v_factor_val);

	// last, max, min, spread, mid_price,avg, slope
	double _prev_max = this->v_last_vector[1];
	double _prev_min = this->v_last_vector[2];
	double _prev_vwap = this->v_last_vector[5];
	double _prev_slope = this->v_last_vector[6];
	
	this->v_last_vector.clear();
	double _curr_last = pDepthMarketData->LastPrice;
	double _curr_max = std::max(_prev_max, _curr_last);
	double _curr_min = std::min(_prev_min, _curr_last);
	double _curr_spread = pDepthMarketData->AskPrice1 - pDepthMarketData->BidPrice1;
	double _curr_vwap = pDepthMarketData->Turnover/pDepthMarketData->Volume;
	double _curr_slope = _curr_last - last_price1;
	double _curr_mid = (pDepthMarketData->AskPrice1*pDepthMarketData->BidVolume1+pDepthMarketData->BidPrice1*pDepthMarketData->AskVolume1)/(pDepthMarketData->AskVolume1+pDepthMarketData->BidVolume1);

	
	// LOG(INFO)<<"calculate factor:"<<_curr_max<<","<<_curr_mid<<","<<_curr_min;
	this->v_last_vector.push_back(_curr_last);
	this->v_last_vector.push_back(_curr_max);
	this->v_last_vector.push_back(_curr_min);
	this->v_last_vector.push_back(_curr_spread);
	this->v_last_vector.push_back(_curr_mid);
	this->v_last_vector.push_back(_curr_vwap);
	this->v_last_vector.push_back(_curr_slope);
	
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
	LOG(INFO)<<"CACHE MAIN INSTRUMENT";
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
		LOG(INFO)<<"BEFORE SORT";
		sort(t.second.begin(), t.second.end(), [](const std::pair<std::string, double>& x, const std::pair<std::string, double>& y) -> bool {return x.second<y.second;});
		LOG(INFO)<<"AFTER SORT";
		const auto it = t.second.rbegin();
		int cnt = 0;
		LOG(INFO)<<"BEFORE PUSH V_OPTION_ID";
		while(cnt<option_size){
			if(it+cnt != t.second.rend())
			{
				v_option_ids.push_back((*(it+cnt)).first);
				cnt ++;
			}
		}
		LOG(INFO)<<"AFTER PUSH V_OPTION_ID";
	}
	for(auto it=v_option_ids.begin(); it!=v_option_ids.end();++it)
	{
		LOG(INFO)<<"v_option_id"<<*it;
	}
	LOG(INFO)<<"CACHE target instruments";

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
