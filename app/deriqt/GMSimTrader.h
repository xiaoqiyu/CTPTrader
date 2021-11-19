#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include "UserStruct.h"
#include "define.h"
#include "recordio.h"
#include "recordio_range.h"
#include "INIReader.h"
#include <glog/logging.h>
#include "gmtrade.h"


class SIMTrader:public gmtrade::Trade
{
    private:
        thread _task_thread;                 //工作线程指针
        TaskQueue _task_queue;               //任务队列
        bool _active = false;                //工作状态
        mutex mutex_;
        condition_variable cond_; //条件变量
        bool connected_ = false; //连接交易前置
        bool login_ = false; //验证和登录完成
        bool available_ = false; //用于交易查询的流控
    public:
    SIMTrader (const std::string& token)
        :Trade (token.c_str())
    {

    }

    void init()
    {
        this->_active = true;
        this->_task_thread = thread(&SIMTrader::processTask, this);
        
    }
    
    void exit();
    //关注委托状态变化
    void on_order_status(Order* order) override
    {
        cout << "symbol: " << order->symbol << endl;
        cout << "cl_ord_id" << order->cl_ord_id << endl;
        cout << "status: " << order->status << endl;
        cout << "volume: " << order->volume << endl;
        cout << "filled_amount: " << order->filled_amount << endl;
        cout << "filled_commission: " << order->filled_commission << endl;
        cout << "filled_volume: " << order->filled_volume << endl;
        cout << "filled_vwap: " << order->filled_vwap << endl;
        cout << "created_at: " << order->created_at << endl;

    }

    //关注执行回报, 如成交, 撤单拒绝等
    void on_execution_report(ExecRpt* rpt) override
    {
        cout << "price: " << rpt->price << endl;
        cout << "volume: " << rpt->volume << endl;
        cout << "amount: " << rpt->amount << endl;
        cout << "commission: " << rpt->commission << endl;
        cout << "cost: " << rpt->cost << endl;
        cout << "created_at: " << rpt->created_at<< endl;
    }

    void on_trade_data_connected () override
    {
        this->connected_ = true;
        cout << "连接上交易服务器 .........." << endl;
    }

    void on_trade_data_disconnected () override
    {
        this->connected_ = false;
        cout << "断开交易服务器 ........." << endl;
    }

    void on_account_status (AccountStatus *account_status) override
    {
        cout << "账户状态变化 : " <<
         account_status->state << endl;
    }

    void processTask();
};


} //namespace gmtrade