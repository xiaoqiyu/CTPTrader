#pragma once
#include <glog/logging.h>
#include "QTStrategyBase.h"


class DataStrategy : public QTStrategyBase
{
public:
    DataStrategy(const std::string &name, int mode, const char* shared_memory_name, uint32_t size, int strategy_class) : QTStrategyBase(name, mode, shared_memory_name, size, strategy_class){
        LOG(INFO)<<"DataStrategy Constructor";
    };
    ~DataStrategy(){};

};