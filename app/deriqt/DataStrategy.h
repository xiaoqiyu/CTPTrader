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
    DataStrategy(const std::string &name, int mode, const char* shared_memory_name, uint32_t size) : QTStrategyBase(name, mode, shared_memory_name, size){
        LOG(INFO)<<"DataStrategy Constructor";
    };
    ~DataStrategy(){};

    void calculate_signal(){};
};