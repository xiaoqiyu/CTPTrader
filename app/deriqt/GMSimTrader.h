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
#include <unordered_map>
#include "gmtrade.h"
#include "UserStruct.h"
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcUserApiDataType.h"

typedef Position* ptr_position;
typedef Order* ptr_order;


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
        bool order_available_ =true; //用于委托查询控制
        bool order_complete_ = true; //用于控制订单流，同时只有一个order,
        gmtrade::DataArray<Position> *p_pos;
        std::vector<ptr_position> all_positions;
        std::vector<ptr_order> all_orders;
        double total_cost;
        std::string account_id;
        unordered_map<std::string, long> order_vol_map;
        unordered_map<std::string, long> execute_vol_map;

        
        
public:
    SimTrader (const std::string& token)
        :Trade (token.c_str())
    {
        LOG(INFO)<<"Constructor in Simtrader";    
        account_id = "a1a91403-2fc2-11ec-bd15-00163e0a4100";//FIXME remove hardcode
        // this->cancel_all_orders();
        this->_task_thread = thread(&SimTrader::processTask, this);
    }

    void init_positions(std::string account_id)
    {
        LOG(INFO)<<"Connected: Init positions with account id=>"<<account_id;
	    this->available_ = false;
        unique_lock<mutex> mlock(mutex_);
        gmtrade::DataArray<Position> *ps = this->get_position(account_id.c_str());


        if(ps->status()==0)
        {
            //TODO CHECK wheather no need lock, called before start, and no callback event yet
            LOG(INFO)<<"Init positions with existing positions,before size:"<<all_positions.size();
            LOG(INFO)<<"*************************Init Positions*******************************";
            int _total_vol = 0;
            for (int i = 0; i<ps->count(); i++)
            {
                ptr_position _curr_pos= &(ps->at(i));
                if (_curr_pos->volume>0){ //only get the positions that has volumes
                    LOG(INFO)<<_curr_pos->symbol<<",vol:"<<_curr_pos->volume<<",available:"<<_curr_pos->available<<",vwap:"<<_curr_pos->vwap<<",side:"<<_curr_pos->side;
                    this->all_positions.push_back(_curr_pos);
                    _total_vol += _curr_pos->volume;
                }
                
            }
            ps->release();
            LOG(INFO)<<"********Complte init positions, size=>"<<all_positions.size()<<"total vol=>"<<_total_vol<<"************";
            
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
    void update_orders(ptr_order p_order);
    std::vector<ptr_position> get_positions();
    std::vector<ptr_position> get_positions(const std::string& instrument_id);
    int get_position_details(const std::string& account_id);
    std::vector<ptr_order> get_all_orders();
    std::vector<ptr_position> get_position_details(const std::string& account_id, const std::string& instrument_id);
    Order* insert_order(CThostFtdcInputOrderField *p_order_field_);
    Order* insert_order(OrderData * p_orderdata);
    int cancel_all_orders();
    int risk_monitor(RiskInputData* p_risk_input, StrategyConfig* p_strategy_conf);
};



