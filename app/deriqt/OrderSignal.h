#pragma once
#include <vector>
#include <string>
#include <glog/logging.h>
#include "define.h"
#include "gmtrade_def.h"
#include "UserStruct.h"

class OrderSignal
{
public:
	OrderSignal(){};
	~OrderSignal();
	OrderData* get_signal(const std::vector<std::string>&v_factor, int trading_mode,std::vector<Position *> v_positions,StrategyConfig *p_strategy_config, int order_limit);

private:
	int _order_volume; 
	int order_side; 
	int order_type; //market, limit
	double order_price;
	std::string sec_id;
};

