#pragma once
#include <vector>
#include <string>
#include <glog/logging.h>
#include "define.h"
#include "gmtrade_def.h"
#include "UserStruct.h"
#include "INIReader.h"


class OrderSignal
{
public:
	OrderSignal(const std::string& name):strategy_name(name){
		FileName _strategy_file = {'\0'};
		// std::string _str_file_name = "/home/kiki/projects/DERIQT_F/conf/strategy.ini"; //FIXME remove hardcode

		std::string _str_file_name = "/home/kiki/workspace/CTPTrader/conf/"+name+".ini"; //FIXME remove hardcode
		strcpy(_strategy_file, _str_file_name.c_str());
		config_ptr.reset(new INIReader(_strategy_file));
		if (config_ptr->ParseError() != 0)
		{
			LOG(FATAL)<< "[init] Fail to load config file in current directory:"<< _str_file_name;
		}
		std::vector<std::string> v_rev;
		char c = ',';
		std::stringstream sstr(config_ptr->Get("strategy","strategy_name","ma"));
		std::string token;
		while(getline(sstr, token, c)){
			v_strategy_name.push_back(token);
		}
		this->strategy_num = v_strategy_name.size();
		this->long_score_benchmark = std::stod(config_ptr->Get("strategy","long_score_ratio","0.0")) * strategy_num;
		this->short_score_benchmark = std::stod(config_ptr->Get("strategy","short_score_ratio","0.0")) * strategy_num;
	};
	~OrderSignal();
	OrderData* get_signal(const std::vector<std::string>&v_rev, ptr_daily_cache p_daily);
	int get_com_signal(const std::vector<std::string>&v_rev, double _range);
	int _ma_rules(double _ma_diff_last, double _ma_diff_curr);
	int _reg_rules(double _log_return, double _mid_log_return);
	int _dual_thrust(double last_price, double _range, double open_price);

private:
	int _order_volume; 
	int order_side; 
	int order_type; //market, limit
	double order_price;
	double open_price = 0.0;
	std::string sec_id;
	std::unique_ptr<INIReader> config_ptr;
	std::vector<std::string> v_strategy_name;//substrategy/signal name list
	float long_score_benchmark; //final score ratio of sum of sub strategy score 
	float short_score_benchmark; //final score ratio of sum of sub strategy score 
	int strategy_num;
	std::string strategy_name;
	// FIXME: for test only 
	int test_order_num =0;
};

