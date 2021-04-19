#pragma once
#include "StrategyHandler.h"

class TStrategy:public StrategyHandler
{
    public:
    TStrategy();
    ~TStrategy();
    
    bool cal_order_signal();
	bool prepared_order_field();
	void order(){};

    void add_new_func(){};

    private:
    bool ordered = false;
}