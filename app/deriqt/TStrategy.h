#pragma once
#include "QTStrategyBase.h"

class TStrategy: public QTStrategyBase
{
    public:
    TStrategy(const std::string &name, int mode, const char* shared_memory_name, uint32_t size):QTStrategyBase(name,mode,shared_memory_name, size){};
    ~TStrategy(){};
    

};