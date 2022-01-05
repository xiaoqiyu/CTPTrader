#pragma once
#include<boost/circular_buffer.hpp>
#include<vector>
#include<iostream>
#include "ThostFtdcUserApiStruct.h"
#include <glog/logging.h>


class Factor
{
public:
	Factor(int long_windows, int short_windows):long_windows(long_windows), short_windows(short_windows){
        last_price_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
    };
	~Factor();
    int update_factor(CThostFtdcDepthMarketDataField* pDepthMarketData,char* str_factor)
    {
        int offset = 0;
        if (NULL != pDepthMarketData){
            double _curr_last = pDepthMarketData->LastPrice;
            double _prev_max = _curr_last;
            double _prev_min = _curr_last;
            double _prev_vwap = _curr_last;
            double _prev_slope = 0;
            if (this->v_last_factor.size()>0){ // not the first tick, has factor cached 
                // last, max, min, spread, mid_price,vwap, slope
                _prev_max = this->v_last_factor[1];
                _prev_min = this->v_last_factor[2];
                _prev_vwap = this->v_last_factor[5];
                _prev_slope = this->v_last_factor[6];
            }


            // current factor calculate
            int cir_size = last_price_circular_ptr->size();
            double _curr_max = std::max(_prev_max, _curr_last);
            double _curr_min = std::min(_prev_min, _curr_last);
            double _curr_spread = pDepthMarketData->AskPrice1 - pDepthMarketData->BidPrice1;
            double _curr_vwap = pDepthMarketData->Turnover/pDepthMarketData->Volume;
            double _curr_mid = (pDepthMarketData->AskPrice1*pDepthMarketData->BidVolume1+pDepthMarketData->BidPrice1*pDepthMarketData->AskVolume1)/(pDepthMarketData->AskVolume1+pDepthMarketData->BidVolume1);
            double _curr_slope_long = 0.0;
            double _curr_slope_short = 0.0;
            if(cir_size>=long_windows){
                _curr_slope_long = (_curr_last - last_price_circular_ptr->front())/long_windows;
                // _curr_slope_short = (_curr_last - *last_price_circular_ptr[long_windows-short_windows])/short_windows; //TODO to 
            }

            //time series cached factor
            last_price_circular_ptr->push_back(_curr_last);
            
            //current factor update
            v_curr_factor.clear();
            this->v_curr_factor.push_back(_curr_last);
	        this->v_curr_factor.push_back(_curr_max);
	        this->v_curr_factor.push_back(_curr_min);
	        this->v_curr_factor.push_back(_curr_spread);
	        this->v_curr_factor.push_back(_curr_mid);
	        this->v_curr_factor.push_back(_curr_vwap);
	        this->v_curr_factor.push_back(_curr_slope_long);
            this->v_curr_factor.push_back(_curr_slope_short);


            //generate the factor shared  string
	        offset += sprintf(str_factor+offset, "%s,", pDepthMarketData->InstrumentID);
	        offset += sprintf(str_factor+offset, "%s,", pDepthMarketData->UpdateTime);
	        offset += sprintf(str_factor+offset, "%d,", pDepthMarketData->UpdateMillisec);
	        offset += sprintf(str_factor+offset, "%d,", pDepthMarketData->Volume);
	        for (auto it = this->v_curr_factor.begin(); it!=this->v_curr_factor.end();++it){
	        	offset += sprintf(str_factor+offset, "%f,", *it);
	        }

            //update the last cached factor to the current factor
            v_last_factor.clear();
            v_last_factor.assign(v_curr_factor.begin(), v_curr_factor.end());
        }
        return offset;
    }


private:
	int long_windows;
    int short_windows;
    // char str_factor [FACTORLEN];
    std::vector<double> v_curr_factor;
    std::vector<double> v_last_factor;
    std::unique_ptr<boost::circular_buffer<double>> last_price_circular_ptr;
};

