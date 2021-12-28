#pragma once
#include <vector>
#include <string>
#include <glog/logging.h>
#include "define.h"



class OrderSignal
{
public:
	OrderSignal(){};
	~OrderSignal();
	void get_signal(const std::vector<std::string>&v_factor, int trading_mode);

private:
	int _order_volume; 
	int order_side; 
	int order_type; //market, limit
	double order_price;
	std::string sec_id;
};

