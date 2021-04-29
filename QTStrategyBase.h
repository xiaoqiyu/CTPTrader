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

class QTStrategyBase
{
public:
	QTStrategyBase(const string &name){this->name=name;};
	~QTStrategyBase(){};
	void init(const char *p_instrumentID, CTPTraderHandler *p_ctp_handler, const char *p_trading_date)
	{
		//初始化
		this->p_CTP_trader_handler = p_ctp_handler;
		std::strcpy(this->instrumentID, p_instrumentID);
		sprintf(mkt_depth_file_name, "cache/%s_depth_market_data_%s.txt", p_instrumentID, p_trading_date);
		sprintf(kline_file_name, "cache/%s_kline_market_data_%s.txt", p_instrumentID, p_trading_date);
		p_kline_helper = new TickToKlineHelper();
		p_mktdata_queue = new DataQueue();
		p_order_queue = new DataQueue();
		//std::ofstream outFile;
		mkt_depth_outfile.open(mkt_depth_file_name, std::ios::app); // 追加
		kline_outfile.open(kline_file_name, std::ios::app);
	};

	void on_tick(CThostFtdcDepthMarketDataField *pDepthMarketData);

	void process_tick();

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

	int get_signal()
	{
		//首先支持策略形式为long/short的开仓信号，平仓还没支持
		//TODO 支持平仓信号
		if (this->_long)
		{
			return LONGOPEN;
		}
		else if (this->_short)
		{
			return SHORTOPEN;
		}
		return -1;
	}

	//下单的主要逻辑，
	void order(int stop_loss_percents=0, int stop_profit_percent=0);

	void release()
	{
		mkt_depth_outfile.close();
		kline_outfile.close();
		delete p_kline_helper;
		delete p_mktdata_queue;
	}

private:
	char instrumentID[10] = {'\0'};
	char mkt_depth_file_name[100] = {'\0'};
	char kline_file_name[100] = {'\0'};
	std::ofstream mkt_depth_outfile;
	std::ofstream kline_outfile;
	TickToKlineHelper *p_kline_helper = nullptr;
	DataQueue *p_mktdata_queue = nullptr;
	DataQueue *p_order_queue = nullptr;	
	CTPTraderHandler *p_CTP_trader_handler = nullptr;
	bool _long = false;
	bool _short = false;
	bool _order = false;
	std::string  name;
};