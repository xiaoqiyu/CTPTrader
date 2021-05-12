#pragma once

#include "QTStrategyBase.h"

class DataSignal : public Signal
{
public:
    DataSignal();
    ~DataSignal();
    void update_signal() = 0;
};

class DataStrategy : public QTStrategyBase
{
public:
    DataStrategy(const std::string &name) : QTStrategyBase(name){};
    ~DataStrategy(){};

    void calculate_signal(){};
    void calculate_factors(CThostFtdcDepthMarketDataField *pDepthMarketData, int cache_len);
};