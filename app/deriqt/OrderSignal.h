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
	OrderSignal(){
		FileName _strategy_file = {'\0'};
		std::string _str_file_name = "/home/kiki/projects/DERIQT_F/conf/strategy.ini";
		strcpy(_strategy_file, _str_file_name.c_str());
		INIReader reader_str(_strategy_file);
		if (reader_str.ParseError() != 0)
		{
			LOG(FATAL)<< "[init] Fail to load config file in current directory:"<< _str_file_name;
		}
		
	};
	~OrderSignal();
	OrderData* get_signal_v0(const std::vector<std::string>&v_factor, int trading_mode,std::vector<Position *> v_positions,StrategyConfig *p_strategy_config, int order_limit);
	OrderData* get_signal(const std::vector<std::string>&v_rev);
	int get_com_signal(const std::vector<std::string>&v_rev);
	int _ma_rules(double _ma_diff_last, double _ma_diff_curr);
	int _reg_rules(double _log_return, double _mid_log_return);

private:
	int _order_volume; 
	int order_side; 
	int order_type; //market, limit
	double order_price;
	std::string sec_id;
};

