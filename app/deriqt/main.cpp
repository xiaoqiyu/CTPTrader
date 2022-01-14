#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
#include "INIReader.h"
#include "UserStruct.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <sys/types.h>
#include "TickToKlineHelper.h"
#include "DataStrategy.h"
#include "TStrategy.h"
#include <algorithm>
#include <glog/logging.h>

int nRequestID = 0;
int DEBUG = 0;


int main(int argc, char *argv[])
{

    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = std::string("./log/");
    std::string _conf_file_name;
    std::string _instrument_id;
    std::string mode = "0";
    std::string _strategy_name = "data_strategy";
    std::vector<std::string> v_instrumentID;

    
    if (argc <= 1)
    {
        LOG(ERROR) << "Please enter a config name" ;
        _conf_file_name = "/home/kiki/projects/DERIQT/test.ini";
        v_instrumentID.push_back("rb2110");
        _strategy_name = "data_strategy";
    }
    else
    {
        _conf_file_name = argv[3];
        _instrument_id = argv[2];
        mode = argv[1];
        std::stringstream sstr(_instrument_id);
        std::string token;
        while (getline(sstr, token, ','))
        {
            v_instrumentID.push_back(token);
        }
    }

    
    QTStrategyBase *p_strategy = nullptr;
    std::string _shm_name = _strategy_name+_instrument_id;
    if (_strategy_name == "data_strategy")
    {
        p_strategy = new DataStrategy("data_strategy", std::stoi(mode),_shm_name.c_str(), 65536);
    }
    else if (_strategy_name == "t_strategy")
    {
        p_strategy = new TStrategy("t_strategy", std::stoi(mode), _strategy_name.c_str(), 65536);
    }
    p_strategy->init(v_instrumentID, _conf_file_name);
    

    sleep(5);
    std::string _user_id = "105600687";
    std::string _broker_id = "9040";
     
    LOG(INFO)<< "Before query investor position";

    std::vector<CThostFtdcInvestorPositionField *>  ret_pos = p_strategy->get_investor_position(_user_id, _broker_id);
    sleep(5);

    LOG(INFO)<< "After query investor position";

    // int ret_trades = p_strategy->req_trade(_user_id, _broker_id);
    // sleep(5);

    std::vector<CThostFtdcTradingAccountField*>  ret_account = p_strategy->get_account(_user_id, _broker_id);
    sleep(5);

    // int ret_pos_detail = p_strategy->get_position_details(_user_id, _broker_id);
    sleep(5);
    LOG(INFO)<< "After query investor account";
    

    p_strategy->start();
    p_strategy->stop();
    p_strategy->release();


    return 0;
}
