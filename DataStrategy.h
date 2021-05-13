#pragma once

#include "QTStrategyBase.h"

class DataSignal : public Signal
{
public:
    DataSignal();
    ~DataSignal();
    
};

class DataStrategy : public QTStrategyBase
{
public:
    DataStrategy(const std::string &name) : QTStrategyBase(name){};
    ~DataStrategy(){};

    void calculate_signal(){};
};