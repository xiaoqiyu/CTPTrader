#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <set>

#include <boost/lockfree/spsc_queue.hpp> // ring buffer

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <cassert>
#include <utility>
#include <string.h>
#include <algorithm>
#include "ThostFtdcMdApi.h"
#include "INIReader.h"
#include "UserStruct.h"
#include "define.h"
#include "TickToKlineHelper.h"
#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
// #include "helper.h"
#include "recordio.h"
#include "recordio_range.h"
#include "GMSimTrader.h"
#include "OrderSignal.h"
#include "Factor.h"
#include <glog/logging.h>

typedef CTPTraderHandler *trader_util_ptr;
typedef CTPMdHandler *md_ptr;
typedef bool order_signal;
extern int nRequestID;


namespace bip = boost::interprocess;
namespace shm
{
    typedef bip::allocator<char, bip::managed_shared_memory::segment_manager> char_alloc;
    typedef bip::basic_string<char, std::char_traits<char>, char_alloc >      shared_string;

    typedef boost::lockfree::spsc_queue<
        shared_string, 
        boost::lockfree::capacity<200> 
    > ring_buffer;
}


class QTStrategyBase
{
public: //strategy function
	void on_tick(); 
	void on_event();
	void on_risk();


public: //stategy management
	QTStrategyBase(const std::string &name,  int mode, const char* shared_memory_name, uint32_t size, int strategy_class):name(name), mode(mode),strategy_class(strategy_class){

		LOG(INFO)<<"[QTStrategyBase] name=>"<<name<<",mode=>"<<mode<<",shared_memory_name=>"<<shared_memory_name<<",size=>"<<size<<",strategy class=>"<<strategy_class;		
		segmet_ptr.reset(new bip::managed_shared_memory(bip::open_or_create, shared_memory_name, size));
		char_alloc_ptr.reset(new shm::char_alloc(segmet_ptr->get_segment_manager()));
		p_queue = segmet_ptr->find_or_construct<shm::ring_buffer>("queue")();		
		
	};
	~QTStrategyBase(){};
	
	int init(std::vector<std::string> &_v_ins, const std::string _conf_file_name);
	//start subscrible market data, and strategy
	void start();
	//stop datathread that subscribe market data and calculate signal, still login
	void stop();
	//release objects,logout and clean
	void release();

public: //order function
	//TThostFtdcDirectionType：char,'0':buy,'1':sell
	void place_order(OrderData* p_order_data);//order main entrance, will insert order to the order data queue,with p_OrderData as parameter
	int cancel_all_orders();//cancel all unfinished orders
	int close_all_orders();//close all current positions
	// std::vector<ptr_position> get_local_positions(const std::string& instrument_id);// return positions by instrument id that are locally updated  
	// std::vector<ptr_position> get_local_positions();// return all positions that are locally updated   
	
	//following order funcs not used now
	void insert_limit_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void insert_market_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcOrderPriceTypeType OrderPriceType, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void insert_limit_order_gfd(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	void insert_limit_order_fok(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType OrderRef, TThostFtdcDirectionType Direction, TThostFtdcInstrumentIDType InstrumentID);
	
	// void insert_order_sim(OrderData* p_order_data);
	void process_order();
	int verify_order_condition_ctp(OrderData* p_orderdata);//check whether to place order(ctp mode), including check cur pos/live risk;if it should be closed, then order_field will be updated accordingly
	int verify_order_condition(OrderData* p_orderdata);//check whether to place  order(gm mode), including check cur pos/live risk;if it should be closed, then order_field will be updated accordingly

	int risk_monitor(RiskInputData* p_risk_input, StrategyConfig* p_strategy_conf);
	
public: //qry for product/instrument/account
    std::tuple<std::vector<std::string>, std::vector<std::string>> get_instrument_by_product(std::string product_id);
	std::vector<CThostFtdcInvestorPositionField *> get_investor_position(std::string investor_id, std::string broker_id);
	// void get_porfortlio();
	std::vector<CThostFtdcTradingAccountField*> get_account(std::string investor_id, std::string broker_id);
	int req_trade(std::string investor_id, std::string broker_id);
	std::vector<std::string> getInstrumentID();
	int get_depth_mkt(std::string instrument_id);
	int get_position_details(std::string investor_id, std::string broker_id);
	void setInstrumentID(std::vector<std::string> v_instrumentid);
	std::vector<CThostFtdcDepthMarketDataField*> get_market_datas(std::vector<std::string> _v_instrument_id)
	{

		return p_trader_handler->get_depth_market_datas(_v_instrument_id);
	}

	std::vector<CThostFtdcInstrumentField*> get_instruments(std::vector<std::string> _v_instrument_id)
	{
		LOG(INFO)<<"[get_instruments] product id=>"<<_v_instrument_id[0];
		return p_trader_handler->get_instruments(_v_instrument_id);
	}

	void read_instruments()
	{
		std::ifstream ifs("instruments.recordio", std::ios::binary);
		recordio::RecordReader reader(&ifs);
		std::string buffer;
		while (reader.ReadBuffer(buffer)) {
			CThostFtdcInstrumentField instrument_fields={0};
			assert(buffer.size() == sizeof(instrument_fields));
			memcpy(&instrument_fields, buffer.data(), buffer.size());
		}
		reader.Close();
	}

	void read_trading_account()
	{
		std::ifstream ifs("trading_account.recordio", std::ios::binary);
		recordio::RecordReader reader(&ifs);
		std::string buffer;
		while (reader.ReadBuffer(buffer)) {
			CThostFtdcTradingAccountField account_fields={0};
			assert(buffer.size() == sizeof(account_fields));
			memcpy(&account_fields, buffer.data(), buffer.size());
		}
		reader.Close();
	}
	void cache_main_instruments(std::vector<std::string> _v_instrument_id);



protected:
	trader_util_ptr p_trader_handler = nullptr;
	md_ptr p_md_handler = nullptr;
	thread data_thread;
	thread order_thread;
	thread signal_thread;
	thread risk_monitor_thread;
	std::vector<std::vector<double>> v_factor; //cached factor list
	void calculate_kline();

private:
	std::vector<std::string> v_instrummentID;
	unordered_map<std::string, int> m_filename_idx;
	unordered_map<std::string, std::string> m_depth_filename;
	unordered_map<std::string, std::string> m_kline_filename;
	unordered_map<std::string, ptr_daily_cache> m_daily_cache;

	vector<std::ofstream *> v_depth_outfile;
	vector<std::ofstream *> v_kline_outfile;
	vector<recordio::RecordWriter> v_depth_writer;
	vector<recordio::RecordWriter> v_kline_writer;
	vector<TickToKlineHelper *> v_t2k_helper;
	data_queue_ptr p_order_queue = nullptr;
	data_queue_ptr p_risk_queue = nullptr;
	bool start_ = false; //when start is called, strategy starts, this will be set to true, when stop is called, this will be reset
	bool active_ = false; //when init is callced(market and trade handler is called), the strategy is activem, when release is called, it will be reset
	std::string broker_id;
	std::string user_id;
	std::string name; //strategy name
	int mode; //0 for market subscribe only; 1 for gm simulation; 2 for ctp simulatation(conf is test.ini) and live trade(conf is ctp.ini)
	std::string task_tag; //will be the first product id, e.g. when passed in rb,hc to the strategy, market will suscribe both rb and hc,but trade rb, and task_tag is set as rb
	std::unordered_map<std::string, std::string> m_main_futures;
	std::unordered_map<std::string, std::string> m_product_exchangeid;
	int option_size = 10;
	std::vector<std::string> v_main_contract_ids;
	std::vector<std::string> v_option_ids;
	std::unordered_map<std::string,CThostFtdcInstrumentField*> m_target_instruments;
	recordio::RecordWriter * p_depth_mkt_writer;
	std::ofstream * cache_ptr;
	std::unique_ptr<bip::managed_shared_memory> segmet_ptr;
    std::unique_ptr<shm::char_alloc> char_alloc_ptr;
	std::unique_ptr<SimTrader> simtrade_ptr;
    shm::ring_buffer* p_queue;
	std::string simtrade_account_id;
	OrderSignal * p_sig;
	Factor *p_factor;
	std::vector<Order> v_order;
	long factor_len = 1024;
	long signal_delay;
	std::time_t  last_order_time = std::time(nullptr);
	std::string simtrade_token;
	StrategyConfig * p_strategy_config;
	int strategy_class; //0 for future, 1 for option
	double up_limit_price = 0.0;//TODO replace this with info from CTP query
	double down_limit_price = 0.0;//TODO replace this with info from CTP query
	long conf_signal_delay;
};
