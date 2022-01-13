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
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcUserApiDataType.h"

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
        bool available_ = true; //用于持仓查询控制
        bool order_complete_ = true; //用于控制订单流，同时只有一个order,
        int stop_profit = 5; 
        int stop_loss = 10; 
        int fee_open = 2; 
        int fee_close_today = 2;
        int fee_close_yesterday = 2;
        int multiplier  = 10; //FIXME remove hardcode, remove to config
        gmtrade::DataArray<Position> *p_pos;
        std::vector<ptr_position> all_positions;
        double total_cost;
        std::string account_id;

        
        
public:
    SimTrader (const std::string& token)
        :Trade (token.c_str())
    {
        LOG(INFO)<<"Constructor in Simtrader";    
        account_id = "a1a91403-2fc2-11ec-bd15-00163e0a4100";//FIXME remove hardcode
        this->_task_thread = thread(&SimTrader::processTask, this);
    }

    void init_positions(std::string account_id)
    {
        LOG(INFO)<<"simtrade init with account id:"<<account_id<<" Init positions";
	    this->available_ = false;
        unique_lock<mutex> mlock(mutex_);
        gmtrade::DataArray<Position> *ps = this->get_position(account_id.c_str());

        if(ps->status()==0)
        {
            //TODO CHECK wheather no need lock, called before start, and no callback event yet
            LOG(INFO)<<"Init positions with existing positions,before size:"<<all_positions.size();
            for (int i = 0; i<ps->count(); i++)
            {
            
                ptr_position _curr_pos= &(ps->at(i));
                if (_curr_pos->volume>0){ //only get the positions that has volumes
                    this->all_positions.push_back(_curr_pos);
                }
                LOG(INFO)<<_curr_pos->symbol<<",vol:"<<_curr_pos->volume<<",available:"<<_curr_pos->available<<",vwap:"<<_curr_pos->vwap<<",side:"<<_curr_pos->side;
            }
            ps->release();
            LOG(INFO)<<"Complte init positions with existing positions, size:"<<all_positions.size();
            
        }
        this->available_ = true;
        mlock.unlock();     //释放锁
        cond_.notify_one(); //通知正在阻塞等待的线程
    }
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
    void update_positions(Order* order);
    void update_positions(ExecRpt*p_exe);
    std::vector<ptr_position> get_positions();
    std::vector<ptr_position> get_positions(const std::string& instrument_id);
    int get_position_details(const std::string& account_id);
    std::vector<ptr_position> get_position_details(const std::string& account_id, const std::string& instrument_id);
    Order* insert_order(CThostFtdcInputOrderField *p_order_field_);
    Order* insert_order(OrderData * p_orderdata);
};



