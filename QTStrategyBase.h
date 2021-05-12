#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>

#include "include/ThostFtdcMdApi.h"
#include "include/INIReader.h"
#include "include/UserStruct.h"
#include "include/define.h"
#include "TickToKlineHelper.h"
#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
#include "helper.h"

typedef CTPTraderHandler *trader_util_ptr;
typedef CTPMdHandler *md_ptr;

extern int nRequestID;

class QTStrategyBase
{
public: //strategy function
	int get_signal();
	void on_tick();

public:
	QTStrategyBase(const string &name) { this->name = name; };
	~QTStrategyBase(){};
	int init(std::vector<std::string>&  _v_ins, const std::string _conf_file_name)
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

		//data thread init
		this->data_thread = thread(&QTStrategyBase::on_tick, this);

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
		p_order_queue = new DataQueue();

		this->active_ = true;
		return 0;
	};

	//start subscrible market data, and strategy
	void start();
	void stop();
	void release();

public: //order function
	//TThostFtdcDirectionType：char,'0':buy,'1':sell
	void insert_limit_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void insert_market_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcOrderPriceTypeType OrderPriceType, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void order(int stop_loss_percents = 0, int stop_profit_percent = 0);

	void calculate_kline();
	std::vector<std::string> getInstrumentID()
	{
		return this->v_instrummentID;
	}

	void setInstrumentID(std::vector<std::string> v_instrumentid)
	{
		if (!v_instrummentID.empty())
		{
			for(auto iter=v_instrummentID.begin(); iter!=v_instrummentID.end(); ++iter)
			{
				this->v_instrummentID.push_back(*iter);
			}
		}
	}

private:
	// TThostFtdcInstrumentIDType instrumentID = {'\0'};
	std::vector<std::string> v_instrummentID;
	unordered_map<std::string, int> m_filename_idx;
	unordered_map<std::string, std::string> m_depth_filename;
	unordered_map<std::string, std::string> m_kline_filename;
	vector<std::ofstream*> v_depth_outfile;
	vector<std::ofstream*> v_kline_outfile;
	vector<TickToKlineHelper*> v_t2k_helper;
	// FileName mkt_depth_file_name = {'\0'};
	// FileName kline_file_name = {'\0'};
	// std::ofstream mkt_depth_outfile;
	// std::ofstream kline_outfile;
	// TickToKlineHelper *p_kline_helper = nullptr;
	// data_queue_ptr p_mktdata_queue = nullptr;
	// DataQueue mktdata_queue = DataQueue();
	data_queue_ptr p_order_queue = nullptr;
	bool start_ = false; 
	bool active_ = false;
	std::string broker_id;
	std::string user_id;
	std::string name;

public: //qry for product/instrument/account
	int get_instrument_by_product(std::string product_id);
	int get_investor_position(std::string investor_id, std::string broker_id);
	void get_porfortlio();
	void get_account();

protected:
	trader_util_ptr p_trader_handler = nullptr;
	md_ptr p_md_handler = nullptr;
	thread data_thread;
};