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

typedef CTPTraderHandler *trader_util_ptr;
typedef CTPMdHandler *md_ptr;

class QTStrategyBase
{
public: //strategy function
		// void on_tick(CThostFtdcDepthMarketDataField *pDepthMarketData);
	int get_signal();
	void process_tick();

public:
	QTStrategyBase(const string &name) { this->name = name; };
	~QTStrategyBase(){};
	int init(TThostFtdcInstrumentIDType instrumentID, const std::string _conf_file_name)
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

		std::cout << "Start Authenticate----------------------------" << std::endl;
		CThostFtdcReqAuthenticateField reqAuth = {0};
		strcpy(reqAuth.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
		strcpy(reqAuth.UserID, reader.Get("user", "UserID", "123456").c_str());
		strcpy(reqAuth.AuthCode, reader.Get("user", "AuthCode", "!@#$%^&*").c_str());
		strcpy(reqAuth.AppID, reader.Get("user", "AppID", "MyProgram").c_str());

		this->p_trader_handler->ReqAuthenticate(&reqAuth, nRequestID++);
		sleep(5);

		std::cout << "Start ----------------------------" << std::endl;
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
		this->p_md_handler->init(instrumentID);

		//data thread init
		this->data_thread = thread(&QTStrategyBase::process_tick, this);

		//private varilbe init
		std::strcpy(this->instrumentID, instrumentID);
		sprintf(mkt_depth_file_name, "cache/%s_depth_market_data_%s.txt", instrumentID, trading_date.c_str());
		sprintf(kline_file_name, "cache/%s_kline_market_data_%s.txt", instrumentID, trading_date.c_str());
		p_kline_helper = new TickToKlineHelper();
		// p_mktdata_queue = new DataQueue();
		p_order_queue = new DataQueue();
		mkt_depth_outfile.open(mkt_depth_file_name, std::ios::app); // 追加
		kline_outfile.open(kline_file_name, std::ios::app);
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
	char *getInstrumentID()
	{
		return this->instrumentID;
	}

	void setInstrumentID(const char *_instrumentID)
	{
		if (NULL != _instrumentID)
		{
			std::strcpy(this->instrumentID, _instrumentID);
		}
	}

private:
	// char instrumentID[10] = {'\0'};
	TThostFtdcInstrumentIDType instrumentID = {'\0'};
	// char mkt_depth_file_name[100] = {'\0'};
	// char kline_file_name[100] = {'\0'};
	FileName mkt_depth_file_name = {'\0'};
	FileName kline_file_name = {'\0'};
	std::ofstream mkt_depth_outfile;
	std::ofstream kline_outfile;
	TickToKlineHelper *p_kline_helper = nullptr;
	// data_queue_ptr p_mktdata_queue = nullptr;
	// DataQueue mktdata_queue = DataQueue();
	data_queue_ptr p_order_queue = nullptr;
	bool _long = false;
	bool _short = false;
	bool _order = false;
	std::string broker_id;
	std::string user_id;
	std::string name;

protected:
	trader_util_ptr p_trader_handler = nullptr;
	md_ptr p_md_handler = nullptr;
	thread data_thread;
};