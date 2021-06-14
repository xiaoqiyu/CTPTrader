#pragma once
#include <glog/logging.h>
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
    DataStrategy(const std::string &name) : QTStrategyBase(name){
        LOG(INFO)<<"DataStrategy Constructor";
    };
    ~DataStrategy(){};

    void calculate_signal(){};
};