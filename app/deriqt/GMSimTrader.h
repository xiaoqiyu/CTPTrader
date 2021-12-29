#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include "define.h"
#include "recordio.h"
#include "recordio_range.h"
// #include "INIReader.h"
#include <glog/logging.h>
#include "gmtrade.h"
#include "UserStruct.h"

typedef Position* ptr_position;


class SimTrader:public gmtrade::Trade
{
private:
        std::thread _task_thread;                 //工作线程指针
        TaskQueue _task_queue;               //任务队列
        // bool _active = false;                //工作状态
        mutex mutex_;
        condition_variable cond_; //条件变量
        bool connected_ = false; //连接交易前置
        bool login_ = false; //验证和登录完成
        bool available_ = false; //用于交易查询的流控
        int stop_profit = 5; 
        int stop_loss = 10; 
        int fee_open = 2; 
        int fee_close_today = 2;
        int fee_close_yesterday = 2;
        int multiplier  = 10; //FIXME remove hardcode, remove to config
        gmtrade::DataArray<Position> *p_pos;
        
public:
    SimTrader (const std::string& token)
        :Trade (token.c_str())
    {
        LOG(INFO)<<"Constructor in Simtrader";    
        this->_task_thread = thread(&SimTrader::processTask, this);
    }

    void init();
    void exit();
    void processTask();
    //关注委托状态变化
    void on_order_status(Order* order) override;

    //关注执行回报, 如成交, 撤单拒绝等
    void on_execution_report(ExecRpt* rpt) override;

    void on_trade_data_connected () override;

    void on_trade_data_disconnected () override;

    void on_account_status (AccountStatus *account_status) override;

    void process_order_status(Task *task);

    void process_execution_report(Task *task);

    int get_position_details(const std::string& account_id)
    {
        gmtrade::DataArray<Position> *ps = this->get_position(account_id.c_str());
        if (ps->status()==0){
            this->p_pos = ps;
            return 0;
        }
        return -1; // not get correct results
    }

    std::vector<ptr_position> get_position_details(const std::string& account_id, const std::string& instrument_id){
        std::vector<ptr_position> ret_pos;
        if (this->get_position_details(account_id))
        {
            for (int i = 0; i<this->p_pos->count(); i++)
            {
                Position &p = this->p_pos->at(i);
                if(p.symbol == instrument_id){
                     ret_pos.push_back(&p);
                }
            }
        }
        return ret_pos;
        }
};

