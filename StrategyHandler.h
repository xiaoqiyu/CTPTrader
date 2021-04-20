#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>

#include "include/ThostFtdcMdApi.h"
#include "include/INIReader.h"
#include "include/ctp_queue.h"
#include "include/define.h"
#include "TickToKlineHelper.h"
#include "CTPTraderHandler.h"

class StrategyHandler
{
	public:
	StrategyHandler(){};
	~StrategyHandler(){};
	void init(const char *p_instrumentID, CTPTraderHandler* p_ctp_handler, const char *p_trading_date)
	{
		//初始化
		this->p_CTP_trader_handler = p_ctp_handler;
		std::strcpy(this->instrumentID, p_instrumentID);
		//HACK 
		sprintf(mkt_depth_file_name, "cache/%s_depth_market_data_%s.txt", p_instrumentID, p_trading_date);
		sprintf(kline_file_name, "cache/%s_kline_market_data_%s.txt", p_instrumentID, p_trading_date);
		p_kline_helper = new TickToKlineHelper();
		p_dataqueue = new MktDataQueue();
		//std::ofstream outFile;
		mkt_depth_outfile.open(mkt_depth_file_name, std::ios::app); // 追加
		kline_outfile.open(kline_file_name,std::ios::app);
	};

	void on_tick(CThostFtdcDepthMarketDataField *pDepthMarketData);

	void process_tick();

	void calculate_kline();
	
	char *getInstrumentID()
	{
		return this->instrumentID;
	}

	void setInstrumentID(const char* _instrumentID)
	{
		if (NULL != _instrumentID)
		{
			std::strcpy(this->instrumentID, _instrumentID);
		}
	}


	void order(){};
	
	void release()
	{
		mkt_depth_outfile.close();
		kline_outfile.close();
		delete p_kline_helper;
		delete p_dataqueue;
	}
	
    private:
    char instrumentID[10] = {'\0'};
    char mkt_depth_file_name [100] = {'\0'};
	char kline_file_name[100] = {'\0'};
	std::ofstream mkt_depth_outfile; 
	std::ofstream kline_outfile;
	TickToKlineHelper *p_kline_helper = nullptr;
	MktDataQueue *p_dataqueue = nullptr;
	CTPTraderHandler * p_CTP_trader_handler = nullptr;
	bool _order = false;
};