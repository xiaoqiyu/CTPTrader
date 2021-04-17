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

extern INIReader reader;
extern MktDataQueue g_dataqueue;
class MktDataHandler
{
	public:
	MktDataHandler(){};
	~MktDataHandler(){};
	void init(const char *p_instrumentID)
	{
		//初始化
		std::strcpy(this->instrumentID, p_instrumentID);
		sprintf(mkt_depth_file_name, "cache/%s_depth_market_data.txt", p_instrumentID);
		sprintf(kline_file_name, "cache/%s_kline_market_data.txt", p_instrumentID);
		p_kline_helper = new TickToKlineHelper();
		p_dataqueue = new MktDataQueue();
		//std::ofstream outFile;
		mkt_depth_outfile.open(mkt_depth_file_name, std::ios::out); // 新开文件
		kline_outfile.open(kline_file_name,std::ios::out);
	};

	void push_mkt_depth_data(CThostFtdcDepthMarketDataField *pDepthMarketData);

	void process_mkt_depth_data();

	void calculate_kline();

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
};