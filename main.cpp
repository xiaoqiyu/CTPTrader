#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
#include "include/INIReader.h"
#include "include/UserStruct.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include "TickToKlineHelper.h"
#include "TStrategy.h"
#include "DataStrategy.h"
#include "models/data_analysis.h"
#include <algorithm>
#include "draft.h"

int nRequestID = 0;
int DEBUG = 0;


//@param main mode instrument conf/trade_date
// bool cmp_max(std::pair<std::string, double> x, std::pair<std::string, double>y)
// {
//     return x.second < y.second;
// }

int main(int argc, char *argv[])
{

    // std::unordered_map<std::string, std::string> _m;
    // _m.insert(std::pair<std::string, std::string>("a","1"));
    // if(_m.find("b") == _m.end())
    // {
    //     std::cout<<"key not exist"<<std::endl;
    // }else{std::cout<<"key exist"<<std::endl;}
    // std::cout<<_m["a"]<<std::endl;
    // _m["a"] = "2";
    // std::cout<<_m["a"]<<std::endl;
    // return 0;
    // test_recordio();
    // return 0;
    // std::vector<std::pair<std::string, double>> v_tmp;
    // v_tmp.push_back(std::pair<std::string, double>("a", 4));
    // v_tmp.push_back(std::pair<std::string, double>("b", 3));
    // sort(v_tmp.begin(), v_tmp.end(), cmp_max);
    // for(const auto& t:v_tmp)
    // {
    //     std::cout<<t.first<<":"<<t.second<<std::endl;
    // }
    // return 0;
    std::string _conf_file_name;
    std::string _instrument_id;
    std::string mode = "0";
    std::string _strategy_name = "data_strategy";
    std::vector<std::string> v_instrumentID;
    if (argc <= 1)
    {
        std::cout << "Please enter a config name" << std::endl;
        _conf_file_name = "test";
        v_instrumentID.push_back("rb2110");
        _strategy_name = "data_strategy";
        // _instrument_id = "rb2110";
        // return 1;
    }
    else
    {
        _conf_file_name = argv[3];
        _instrument_id = argv[2];
        mode = argv[1];
        // _strategy_name = argv[4];
        std::stringstream sstr(_instrument_id);
        std::string token;
        int cnt = 0;
        while (getline(sstr, token, ','))
        {
            std::cout << "token:" << token << std::endl;
            v_instrumentID.push_back(token);
        }
    }
    if(mode == "1")
    {
        std::string _trade_date = argv[3];
        for(auto it=v_instrumentID.begin(); it != v_instrumentID.end(); ++it)
        {
            data_preprocessing(*it, _trade_date);
            // std::cout<<"data preprocessing"<<std::endl;
        }
        return 0;
    }
    std::cout << "check ins in main" << v_instrumentID.size() << std::endl;
    QTStrategyBase *p_strategy = nullptr;
    if (_strategy_name == "data_strategy")
    {
        p_strategy = new DataStrategy("data_strategy");
    }
    else if (_strategy_name == "t_strategy")
    {
        p_strategy = new TStrategy("t_strategy");
    }

    //TODO check this read
    // p_strategy->read_instruments();
    // return 0;
    int ret = p_strategy->init(v_instrumentID, _conf_file_name);


    std::string _str = "cu";
    std::string _user_id = "105600687";
    std::string _broker_id = "9040";
    // std::tuple<std::vector<std::string>, std::vector<std::string>> ret_instrument_id = p_strategy->get_instrument_by_product(_str);
    // std::vector<std::string> ret_future_id =std::get<0>(ret_instrument_id);
    // std::vector<std::string> ret_option_id =std::get<1>(ret_instrument_id);
    // for(auto it = ret_future_id.begin(); it!=ret_future_id.end();++it)
    // {
    //     std::cout<<*it<<std::endl;
    // }

    std::vector<std::string> _test_ins;
    std::string _str1 = "m";
    _test_ins.push_back(_str);
    _test_ins.push_back(_str1);
    // p_strategy->cache_main_instruments(_test_ins);

#if false
    std::vector<CThostFtdcInstrumentField*> ret_instruments = p_strategy->get_instruments(_test_ins);
    sleep(5);
    for(auto it = ret_instruments.begin(); it!=ret_instruments.end();++it)
    {
        CThostFtdcInstrumentField* p_instrument_field = reinterpret_cast<CThostFtdcInstrumentField*>(*it);
        std::cout<<p_instrument_field->InstrumentID<<","<<p_instrument_field->ProductID<<std::endl;
    }
    std::vector<CThostFtdcDepthMarketDataField*> ret_depth_market_data = p_strategy->get_market_datas(_test_ins);
    for (auto it = ret_depth_market_data.begin(); it != ret_depth_market_data.end(); ++it)
    {
        CThostFtdcDepthMarketDataField* p_depth_mkt_data = reinterpret_cast<CThostFtdcDepthMarketDataField*>(*it);
        std::cout<<p_depth_mkt_data->InstrumentID<<","<<p_depth_mkt_data->OpenInterest<<","<<p_depth_mkt_data->LastPrice<<","<<p_depth_mkt_data->PreOpenInterest<<","
        <<p_depth_mkt_data->PreDelta<<std::endl;
    }
    std::cout<<"ret depth mkt size:"<<ret_depth_market_data.size()<<std::endl;
    std::cout<<"ret ins size:"<<ret_instruments.size()<<std::endl;
#endif 
#if false

    sleep(5);

    int ret_pos = p_strategy->get_investor_position(_user_id, _broker_id);
    sleep(5);

    int ret_trades = p_strategy->req_trade(_user_id, _broker_id);
    sleep(5);

    int ret_account = p_strategy->get_account(_user_id, _broker_id);
    sleep(5);

    int ret_mkt = p_strategy->get_depth_mkt(v_instrumentID[0]);
    sleep(5);

    int ret_pos_detail = p_strategy->get_position_details(_user_id, _broker_id);
    sleep(5);
#endif

    //start strategy 
    p_strategy->start();
    p_strategy->stop();
    p_strategy->release();

    return 0;
}
