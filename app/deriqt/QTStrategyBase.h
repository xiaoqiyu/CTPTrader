#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

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



//TODO check multiple definition errors
// std::vector<std::string> split_str(std::string s, char c)
// {
    // std::string strInstruments = reader.Get("md", "InstrumentID", "rb2110,m2109");
    // std::vector<std::string> v;
	// std::stringstream sstr(s);
	// std::string token;
	// int cnt = 0;
    // while (getline(sstr, token, c))
    // {
    //    v.push_back(token);
    // }
    // return v;
// }
// 

// std::string get_exchange_id_order11(int mode=1, std::string product_id="eg"){
    // if(mode == 1){
        //  if(product_id == "eg"){
            //  return "DCE";
        //  }
        // 
    // }else if(mode == 2){
        // return "mode 2";
    // }else{
        // return "invalid mode";
    // }
    // return "invalid mode";
    // 
// }

class QTStrategyBase
{
public: //strategy function
	int get_signal(); // TODO: check how to signal, maybe replace, and push to order Q
	void on_tick(); 
	void on_event();
	

public: //stategy management
	QTStrategyBase(const std::string &name,  int mode, const char* shared_memory_name, uint32_t size):name(name), mode(mode){

		LOG(INFO)<<"constructor in base";		
		segmet_ptr.reset(new bip::managed_shared_memory(bip::open_or_create, shared_memory_name, size));
		char_alloc_ptr.reset(new shm::char_alloc(segmet_ptr->get_segment_manager()));
		p_queue = segmet_ptr->find_or_construct<shm::ring_buffer>("queue")();		
		// if(mode==0){
			// this->p_shm_queue
		// }
	};
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
		LOG(INFO)<<"GET INSTRUMENTS:"<<_v_instrument_id[0];
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
	std::vector<std::vector<double>> v_factor; //cached factor list
	//FIXME remove hard code of the size
	// std::vector<double> v_last_vector(7, 0.0); // last, max, min, spread, mid_price,avg, slope
	std::vector<double> v_last_vector;
	double last_price1 = 0.0; //last price in prev timestamp
	double last_price2 = 0.0; //last price in prev 2 timesstamp
	
	// OrderSignal  *p_signal = nullptr;				  //derived in subclass
	virtual void calculate_signal(){};	  //overwrite in subclass TODO add the signal update in process 2
	void calculate_factors(CThostFtdcDepthMarketDataField *pDepthMarketData, int cache_len);
	void calculate_kline();

private:
	std::vector<std::string> v_instrummentID;
	unordered_map<std::string, int> m_filename_idx;
	unordered_map<std::string, std::string> m_depth_filename;
	unordered_map<std::string, std::string> m_kline_filename;
	vector<std::ofstream *> v_depth_outfile;
	vector<std::ofstream *> v_kline_outfile;
	// vector<FILE*> v_depth_file_handler;
	// vector<FILE*> v_kline_file_handler;
	vector<recordio::RecordWriter> v_depth_writer;
	vector<recordio::RecordWriter> v_kline_writer;
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
	int mode;
	std::string task_tag;
	std::unordered_map<std::string, std::string> m_main_futures;
	int option_size = 10;
	std::vector<std::string> v_main_contract_ids;
	std::vector<std::string> v_option_ids;
	std::unordered_map<std::string,CThostFtdcInstrumentField*> m_target_instruments;
	recordio::RecordWriter * p_depth_mkt_writer;
	// shm::ring_buffer* p_queue;
    // shm::char_alloc acc;
	std::unique_ptr<bip::managed_shared_memory> segmet_ptr;
    std::unique_ptr<shm::char_alloc> char_alloc_ptr;
	std::unique_ptr<SimTrader> simtrade_ptr;
    shm::ring_buffer* p_queue;
	// TODO: FOR SIMTRADE TESTING
	int position_limit; 
	std::string simtrade_account_id;
};
