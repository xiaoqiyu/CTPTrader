#pragma once
#include<boost/circular_buffer.hpp>
#include<vector>
#include<iostream>
#include<cmath>
#include "helper.h"
#include "ThostFtdcUserApiStruct.h"
#include <glog/logging.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "UserStruct.h"



class Factor
{
public:
	Factor(int long_windows, int short_windows):long_windows(long_windows), short_windows(short_windows){
        last_price_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
        mid_price_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
        spread_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
        buy_vol_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
        sell_vol_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
        turnover_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
        vol_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
    };
	~Factor(){
        last_price_circular_ptr.reset();
        mid_price_circular_ptr.reset();
        spread_circular_ptr.reset();
        buy_vol_circular_ptr.reset();
        sell_vol_circular_ptr.reset();
        turnover_circular_ptr.reset();
        vol_circular_ptr.reset();
    };
    int update_factor(CThostFtdcDepthMarketDataField* pDepthMarketData,char* str_factor, int signal_flag)
    {
        // std::cout<<"mkt:"<<pDepthMarketData->LastPrice<<std::endl;
        long offset = 0;
        if (NULL != pDepthMarketData){
            double _curr_last = pDepthMarketData->LastPrice;
            double _curr_vol = 0;
            double _curr_interest = 0;
            double _prev_max = _curr_last;
            double _prev_min = _curr_last;
            double _prev_vwap = _curr_last;
            double _log_return  = 0.0;
            double _mid_log_return = 0.0;
            double _log_return_long = 0.0;
            double _log_return_short = 0.0;
            double _mid_log_return_short = 0.0;
            double _mid_log_return_long = 0.0;
            double _ma_short = 0.0;
            double _ma_long = 0.0;
            double _ma_ls_diff_last = 0.0;
            double _ma_ls_diff_curr =  0.0;
            TickType tick_type = DualOPen; 
            TickDirection tick_direction = Buy; 
            double _vol_buy = 0.0;
            double _vol_sell = 0.0;
            double _interest_open = 0.0;
            double _interest_close = 0.0;
            double _turnover_long = 0.0;
            double _turnover_short =0.0;
            double _vol_long = 0.0;
            double _vol_short = 0.0;
            
            // double _prev_slope = 0;

            double _curr_spread = pDepthMarketData->AskPrice1 - pDepthMarketData->BidPrice1;
            double _curr_vwap = pDepthMarketData->Turnover/pDepthMarketData->Volume;
            double _curr_mid = (pDepthMarketData->AskPrice1*pDepthMarketData->BidVolume1+pDepthMarketData->BidPrice1*pDepthMarketData->AskVolume1)/(pDepthMarketData->AskVolume1+pDepthMarketData->BidVolume1);
            if (this->v_last_factor.size()>0){ // not the first tick, has factor cached 
                // last, max, min, spread, mid_price,vwap, slope
                _prev_max = this->v_last_factor[1];
                _prev_min = this->v_last_factor[2];
                _prev_vwap = this->v_last_factor[5];
                _log_return = std::log(_curr_last) - std::log(this->v_last_factor[0]);
                _mid_log_return = std::log(_curr_mid) - std::log(this->v_last_factor[4]);
                // _prev_slope = this->v_last_factor[6];
            }
             
            // current factor calculate
            //snap factor calculate, order type,buy/sell type,etc
            int cir_size = last_price_circular_ptr->size();

            double _curr_max = std::max(_prev_max, _curr_last);
            double _curr_min = std::min(_prev_min, _curr_last);
            // std::cout<<"before direction"<<std::endl;
            if (v_last_mkt.size()>0){
                _curr_vol = pDepthMarketData->Volume - v_last_mkt[2];
                _curr_interest = pDepthMarketData->OpenInterest - v_last_mkt[3];
                if(pDepthMarketData->LastPrice >= v_last_mkt[0]){//现价大于前卖一价，主动买
                    tick_direction = Buy;
                    _vol_buy = _curr_vol;
                }else if(pDepthMarketData->LastPrice <= v_last_mkt[1]){ //现价小于前买一价，主动卖
                    tick_direction = Sell;
                    _vol_sell = _curr_vol;
                }else{//其他，无法判断方向
                    tick_direction = Unknown;
                }
            
                if(_curr_interest >0 && _curr_vol == _curr_interest){
                    tick_type = DualOPen;
                }else if (_curr_interest >0 && _curr_vol > _curr_interest){
                    tick_type = Open;
                }else if (_curr_vol >0 && _curr_interest<0 && _curr_vol > -_curr_interest){
                    tick_type = Close;
                }else if (_curr_vol>0 && _curr_interest == 0){
                    tick_type = Transfer;
                }else if (_curr_vol + _curr_interest == 0){
                    tick_type = DualClose;
                }else{
                    tick_type = OtherType;
                }
            }

            //lag time series factor calculation
            if(cir_size>=long_windows){ //window length >= long
                // _curr_slope_long = (_curr_last - last_price_circular_ptr->front())/long_windows;
                // _curr_slope_short = (_curr_last - *last_price_circular_ptr[long_windows-short_windows])/short_windows; //TODO to 
                //update long windows lag factor
                // std::cout<<"long windows"<<std::endl;
                //FIXME for short window, not substract the first element in the cir buffer, should be the (long-short)th element
                _log_return_long = this->v_last_factor[8] + _log_return - (std::log(last_price_circular_ptr->at(1))-std::log(last_price_circular_ptr->at(0)));
                _mid_log_return_long = this->v_last_factor[10] + _mid_log_return - (std::log(mid_price_circular_ptr->at(1))-std::log(mid_price_circular_ptr->at(0)));
                _log_return_short = this->v_last_factor[7] + _log_return - (std::log(last_price_circular_ptr->at(1))-std::log(last_price_circular_ptr->at(0)));
                _mid_log_return_short = this->v_last_factor[9] + _mid_log_return - (std::log(mid_price_circular_ptr->at(1))-std::log(mid_price_circular_ptr->at(0)));
                _turnover_long = pDepthMarketData->Turnover - turnover_circular_ptr->at(0);
                _turnover_short = pDepthMarketData->Turnover - turnover_circular_ptr->at(long_windows-short_windows);
                _vol_long = pDepthMarketData->Volume - vol_circular_ptr->at(0);
                _vol_short = pDepthMarketData->Volume - vol_circular_ptr->at(long_windows - short_windows);
                _ma_long = _turnover_long/_vol_long;
                _ma_short = _turnover_short/_vol_short;
                _ma_ls_diff_curr = _ma_short - _ma_long;
                _ma_ls_diff_last = v_last_factor[11] - v_last_factor[12]; //at this tick, last factor should be valid
                // std::cout<<"curr mid:"<<_curr_mid<<",mid log return:"<<_mid_log_return<<",curr last:"<<_curr_last<<",curr log return:"<<_log_return<<",ma long:"<<_ma_long<<",ma short:"<<_ma_short<< std::endl;
                // std::cout<<"last 0"<<last_price_circular_ptr->at(1)<<","<<last_price_circular_ptr->at(0)<<std::endl;
                // std::cout<<"mid 0"<<mid_price_circular_ptr->at(1)<<","<<mid_price_circular_ptr->at(0)<<std::endl;
                // std::cout<<"log return long:"<<_log_return_long<<",log return short:"<<_log_return_short<<",mid log return long:"<<_mid_log_return_long<<",mid log return short:"<<_mid_log_return_short<<",ma long:"<<_ma_long<<",ma short:"<<_ma_short<<",ma diff last:"<<_ma_ls_diff_last<<",ma diff curr:"<<_ma_ls_diff_curr<< std::endl;
                
            }else if(cir_size >= short_windows){ //window length>short and window length<long
                //update short windows lag factor
                // _log_return_short = this->v_last_factor[8] + _log_return - (std::log(last_price_circular_ptr[1])-std::log(last_price_circular_ptr[0]));
                // _mid_log_return_short = this->v_last_factor[10] + _mid_log_return_long - (std::log(mid_price_circular_ptr[1])-std::log(mid_price_circular_ptr[0]));
                // _log_return_long = INFINITY;
                // std::cout<<"short windows"<<std::endl;
                _ma_long = _curr_vwap;
                _log_return_short = this->v_last_factor[7] + _log_return - (std::log(last_price_circular_ptr->at(1))-std::log(last_price_circular_ptr->at(0)));
                _mid_log_return_short = this->v_last_factor[9] + _mid_log_return - (std::log(mid_price_circular_ptr->at(1))-std::log(mid_price_circular_ptr->at(0)));
                _ma_short = _curr_vwap;             
            }else{
                //no lag facotr update
                // std::cout<<"less than short windows"<<std::endl;
                // _log_return_long = 0.0;
                // _mid_log_return_long = 0.0;
                // _log_return_short = 0.0;
                // _mid_log_return_short = 0.0;
                _ma_long = _curr_vwap;
                _ma_short = _curr_vwap;
            }


            //time series cached factor
            last_price_circular_ptr->push_back(_curr_last);
            spread_circular_ptr->push_back(_curr_spread);
            mid_price_circular_ptr->push_back(_curr_mid);
            turnover_circular_ptr->push_back(pDepthMarketData->Turnover);
            vol_circular_ptr->push_back(pDepthMarketData->Volume);
            
            //current factor update
            v_curr_factor.clear();
            this->v_curr_factor.push_back(_curr_last); //vector:0;factor:4
	        this->v_curr_factor.push_back(_curr_max); //vector:1;factor:5
	        this->v_curr_factor.push_back(_curr_min); //vector:2;factor:6
	        this->v_curr_factor.push_back(_curr_spread); //vector:3;factor:7
	        this->v_curr_factor.push_back(_curr_mid); //vector:4;factor:8
	        this->v_curr_factor.push_back(_curr_vwap);//vector:5;factor:9
            this->v_curr_factor.push_back(_log_return);//vector:6;factor:10
            this->v_curr_factor.push_back(_log_return_short);//vector:7;factor:11
            this->v_curr_factor.push_back(_log_return_long);//vector:8;factor:12
            this->v_curr_factor.push_back(_mid_log_return_short);//vector:9;factor:13
            this->v_curr_factor.push_back(_mid_log_return_long);//vector:10;factor:14
            this->v_curr_factor.push_back(_ma_short);//vector:11;factor:15
            this->v_curr_factor.push_back(_ma_long);//vector:12;factor:16
            this->v_curr_factor.push_back(_curr_vol);//vector:13; factor:17
            this->v_curr_factor.push_back(_curr_interest);//vector 14; factor:18
            //REMARK get the deri factor insead: buy_vol/sell_vol in the windows
            // this->v_curr_factor.push_back(_vol_buy);//vector 15; factor 19
            // this->v_curr_factor.push_back(_vol_sell);//vector 16; factor 20


            if (signal_flag == 0){
                //generate the factor shared  string
	            offset += sprintf(str_factor+offset, "%s,", pDepthMarketData->InstrumentID); //factor:0
	            offset += sprintf(str_factor+offset, "%s,", pDepthMarketData->UpdateTime); //factor:1
	            offset += sprintf(str_factor+offset, "%d,", pDepthMarketData->UpdateMillisec);//facotor:2
	            offset += sprintf(str_factor+offset, "%d,", pDepthMarketData->Volume);//factor:3
	            for (auto it = this->v_curr_factor.begin(); it!=this->v_curr_factor.end();++it){
	            	offset += sprintf(str_factor+offset, "%f,", *it);
	            }
                offset += sprintf(str_factor+offset, "%f,", _ma_ls_diff_last);//factor:19
                offset += sprintf(str_factor+offset, "%f,", _ma_ls_diff_curr);//factor:20
                offset += sprintf(str_factor+offset, "%d,", tick_direction);//factor:21
            }
            
            // std::cout<<"after push afctor,len:"<<this->v_curr_factor.size()<<std::endl;
            //update the last cached factor to the current factor
            v_last_factor.clear();
            v_last_factor.assign(v_curr_factor.begin(), v_curr_factor.end()); //FIXME move up the start of the update 

            v_last_mkt.clear();
            v_last_mkt.push_back(pDepthMarketData->AskPrice1); //0:ask price 1
            v_last_mkt.push_back(pDepthMarketData->BidPrice1);// 1:bid price 1
            v_last_mkt.push_back(pDepthMarketData->Volume);//2:vol
            v_last_mkt.push_back(pDepthMarketData->OpenInterest);//3:open interest
            v_last_mkt.push_back(_vol_buy);//4. buy vol
            v_last_mkt.push_back(_vol_sell); //5. sell vol
            v_last_mkt.push_back(pDepthMarketData->Turnover); 

        }
        return offset;
    }


private:
	int long_windows;
    int short_windows;
    // char str_factor [FACTORLEN];
    std::vector<double> v_curr_factor; //当前因子
    std::vector<double> v_last_factor; //因子上个tick cache
    std::vector<double> v_last_mkt; //行情上个tick cache
    std::unique_ptr<boost::circular_buffer<double>> last_price_circular_ptr; //成交价格long windows 时序cache
    std::unique_ptr<boost::circular_buffer<double>> mid_price_circular_ptr; //mid price long windows 时序 cache 
    std::unique_ptr<boost::circular_buffer<double>> spread_circular_ptr; //spread long windows 时序 cache
    std::unique_ptr<boost::circular_buffer<double>> buy_vol_circular_ptr; //buy vol 时序 cache
    std::unique_ptr<boost::circular_buffer<double>> sell_vol_circular_ptr; // sell vol 时序 cache
    std::unique_ptr<boost::circular_buffer<double>> turnover_circular_ptr; //turnover 时序cache
    std::unique_ptr<boost::circular_buffer<double>> vol_circular_ptr; //volume time series 
};

