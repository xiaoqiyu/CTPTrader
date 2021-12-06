#pragma once
#include "QTStrategyBase.h"


class TSignal:public Signal
{
public:
    TSignal();
    ~TSignal();
    void update_signal(){};
};

class TStrategy: public QTStrategyBase
{
    public:
    TStrategy(const std::string &name, int mode):QTStrategyBase(name,mode ){};
    ~TStrategy(){};
    
    void calculate_signal(){
        std::cout<<"calculate signal in tstrategy"<<std::endl;
    };

};