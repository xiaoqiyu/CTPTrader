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
#include "draft.h"



int nRequestID = 0;
int DEBUG = 0;

int main(int argc, char *argv[])
{
    std::string _conf_file_name;
    std::string _instrument_id;
    std::string _strategy_name;
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
        _conf_file_name = argv[2];
        _instrument_id = argv[1];
        _strategy_name = argv[3];
        std::stringstream sstr(_instrument_id);
        std::string token;
        int cnt = 0;
        while (getline(sstr, token, ','))
        {
            std::cout << "token:" << token << std::endl;
            v_instrumentID.push_back(token);
        }
    }
    std::cout << "check ins in main" << v_instrumentID.size() << std::endl;
    QTStrategyBase *p_strtegy = nullptr;
    if (_strategy_name == "data_strategy")
    {
        DataStrategy _data_strategy(_strategy_name);
        p_strtegy = &_data_strategy;
    }
    else if (_strategy_name == "t_strategy")
    {
        TStrategy _t_strategy(_strategy_name);
        p_strtegy = &_t_strategy;
    }

    int ret = p_strtegy->init(v_instrumentID, _conf_file_name);
    std::string _str = "cu";
    // int ret_ins = p_strtegy->get_instrument_by_product(_str);
    std::string _user_id = "105600687";
    std::string _broker_id = "9040";
    // int ret_pos = p_strtegy->get_investor_position(_user_id, _broker_id);
    p_strtegy->start();
    p_strtegy->stop();
    p_strtegy->release();

    return 0;
}
