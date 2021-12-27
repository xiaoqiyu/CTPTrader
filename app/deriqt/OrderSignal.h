#pragma once
#include <vector>
#include <string>
#include "define.h"



class OrderSignal
{
public:
	OrderSignal();
	~OrderSignal();
	void get_signal(const std::vector<double>&v_factor){};

private:
	int _order_volume; 
	int order_side; 
	int order_type; //market, limit
	double order_price;
	std::string sec_id;
};

