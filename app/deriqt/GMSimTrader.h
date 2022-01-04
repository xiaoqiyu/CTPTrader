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
        bool available_ = true; //用于持仓查询控制
        int stop_profit = 5; 
        int stop_loss = 10; 
        int fee_open = 2; 
        int fee_close_today = 2;
        int fee_close_yesterday = 2;
        int multiplier  = 10; //FIXME remove hardcode, remove to config
        gmtrade::DataArray<Position> *p_pos;
        std::vector<ptr_position> all_positions;

        
        
public:
    SimTrader (const std::string& token)
        :Trade (token.c_str())
    {
        LOG(INFO)<<"Constructor in Simtrader";    
        this->_task_thread = thread(&SimTrader::processTask, this);
    }

    void init_positions(std::string account_id)
    {
        LOG(INFO)<<"simtrade init with account id:"<<account_id<<" Init positions";
        // this->_task_thread = thread(&SimTrader::processTask, this);
        gmtrade::DataArray<Position> *ps = this->get_position(account_id.c_str());

        if(ps->status()==0)
        {
            //TODO CHECK wheather no need lock, called before start, and no callback event yet
            LOG(INFO)<<"Init positions with existing positions,before size:"<<all_positions.size();
            for (int i = 0; i<ps->count(); i++)
            {
                ptr_position _curr_pos= &(ps->at(i));
                this->all_positions.push_back(_curr_pos);
            }
            ps->release();
            LOG(INFO)<<"Complte init positions with existing positions, size:"<<all_positions.size();
        }

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

    void update_positions(ExecRpt*p_exe){
        this->available_ = false;
        std::string exe_symbol = p_exe->symbol;
        float exe_price = p_exe->price;
        
        long exe_vol = p_exe->volume;//open 
        if(p_exe->position_effect == PositionEffect_Close) exe_vol = -exe_vol;

        LOG(INFO)<<"Start update positions,curr pos size:"<<all_positions.size();
        unique_lock<mutex> mlock(mutex_);
        bool flag = false;
        if (this->all_positions.size()>0){//have positions now
            for(auto it=all_positions.begin(); it!=all_positions.end(); ++it){
                ptr_position p_curr_pos = *it;
                LOG(INFO)<<"current positions:"<<p_curr_pos->symbol<<","<<p_curr_pos->vwap<<","<<p_curr_pos->volume<<","<<p_curr_pos->side;
                LOG(INFO)<<"to be added exe,check cond---------------------:"<<p_exe->symbol<<","<<p_exe->side<<","<<p_curr_pos->symbol<<","<<p_curr_pos->side;
                //代码一样，同时多空方向一致且为开或者多空方向相反且为平
                bool _is_pos_exist = strcmp(p_curr_pos->symbol, p_exe->symbol)==0 && (p_curr_pos->side == p_exe->side && p_exe->position_effect==PositionEffect_Open || p_curr_pos->side != p_exe->side && p_exe->position_effect==PositionEffect_Close);
                LOG(INFO)<<"check whether to merge position----------------:"<<_is_pos_exist;
                if(_is_pos_exist){ //position exists 
                    LOG(INFO)<<"pos exist, and update position"<<"exe type:"<<p_exe->exec_type<<",pos vol:"<<p_curr_pos->volume<<",exe vol:"<<exe_vol;
                    flag = true;
                    if (p_curr_pos->volume+exe_vol == 0){
                        p_curr_pos->vwap = 0.0;
                    }else{
                        p_curr_pos->vwap = (p_curr_pos->vwap*p_curr_pos->volume + exe_price*exe_vol)/(p_curr_pos->volume+exe_vol);
                    }
                    p_curr_pos->volume += exe_vol;
                    //TODO add other value updates
                    LOG(INFO)<<"After update position,vol:"<<p_curr_pos->volume;
                }
            }
        }
        
        if(!flag){
            LOG(INFO)<<"symbol not exist, start create new position for open order,flag:"<<flag<<"pos size:"<<all_positions.size();
            ptr_position p_pos = new Position();
            strcpy(p_pos->symbol, exe_symbol.c_str());
            p_pos->vwap = exe_price;
            p_pos->volume = p_exe->volume;
            p_pos->volume_today = p_exe->volume;
            p_pos->side = p_exe->side;
            //TODO add other value updates 
            all_positions.push_back(p_pos);
            LOG(INFO)<<"after add new transaction,size:"<<all_positions.size()<<",P VOL:"<<p_pos->volume<< std::endl;
        }
        this->available_ = true;
        mlock.unlock();     //释放锁
        cond_.notify_one(); //通知正在阻塞等待的线程
        
    }

    std::vector<ptr_position> get_positions(){
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return this->available_; //FIXME double check
        }); //等待条件变量通知
        return this->all_positions;
    }

    std::vector<ptr_position> get_positions(const std::string& instrument_id){
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return this->available_;//FIXME double check
        }); //等待条件变量通知
        // return this->all_positions;
        
        std::vector<ptr_position> ret_pos;
        for(auto it = all_positions.begin(); it!=all_positions.end();++it){
            ptr_position _tmp = *it;
            if(_tmp->symbol == instrument_id) ret_pos.push_back(_tmp);
        }
        return ret_pos;
    }

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

