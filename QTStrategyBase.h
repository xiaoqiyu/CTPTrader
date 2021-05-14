#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <stdio.h>

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
typedef bool order_signal;
extern int nRequestID;

class Signal
{
public:
	Signal();
	~Signal();
	void update_signal(){};

private:
	order_signal _signal = LONGOPEN;
};

class QTStrategyBase
{
public: //strategy function
	int get_signal();
	void on_tick();

public: //stategy management
	QTStrategyBase(const std::string &name) : name(name){};
	virtual ~QTStrategyBase(){};
	int init(std::vector<std::string> &_v_ins, const std::string _conf_file_name);
	//start subscrible market data, and strategy
	void start();
	//stop datathread that subscribe market data and calculate signal, still login
	void stop();
	//release objects,logout and clean
	void release();

public: //order function
	//TThostFtdcDirectionType：char,'0':buy,'1':sell
	void insert_limit_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void insert_market_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcOrderPriceTypeType OrderPriceType, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void order(int stop_loss_percents = 0, int stop_profit_percent = 0);
	void process_order();
	bool verify_order_condition();

public: //qry for product/instrument/account
	int get_instrument_by_product(std::string product_id);
	int get_investor_position(std::string investor_id, std::string broker_id);
	void get_porfortlio();
	void get_account();

	std::vector<std::string> getInstrumentID();
	void setInstrumentID(std::vector<std::string> v_instrumentid);

protected:
	trader_util_ptr p_trader_handler = nullptr;
	md_ptr p_md_handler = nullptr;
	thread data_thread;
	thread order_thread;
	std::vector<std::vector<float>> v_factor; //cached factor list
	Signal *p_signal = nullptr;				  //derived in subclass
	virtual void calculate_signal(){std::cout<<"calbulate signal in base class"<<std::endl;};	  //overwrite in subclass
	void calculate_factors(CThostFtdcDepthMarketDataField *pDepthMarketData, int cache_len);
	void calculate_kline();

private:
	std::vector<std::string> v_instrummentID;
	unordered_map<std::string, int> m_filename_idx;
	unordered_map<std::string, std::string> m_depth_filename;
	unordered_map<std::string, std::string> m_kline_filename;
	vector<std::ofstream *> v_depth_outfile;
	vector<std::ofstream *> v_kline_outfile;
	vector<FILE*> v_depth_file_handler;
	vector<FILE*> v_kline_file_handler;
	vector<TickToKlineHelper *> v_t2k_helper;
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
};