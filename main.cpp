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
#include "QTStrategyBase.h"
#include "draft.h"

//ldd main
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib

int nRequestID = 0;
int DEBUG = 0;



int main(int argc, char *argv[])
{
    std::string _conf_file_name;
    std::string _instrument_id;
    std::vector<std::string> v_instrumentID;
    if (argc <= 1)
    {
        std::cout << "Please enter a config name" << std::endl;
        _conf_file_name = "test";
        v_instrumentID.push_back("rb2110");
        // _instrument_id = "rb2110";
        // return 1;
    }else{

        _conf_file_name = argv[2];
        _instrument_id = argv[1];
        std::stringstream sstr(_instrument_id);
        std::string token;
        int cnt = 0;
        while (getline(sstr, token, ','))
        {
            std::cout<<"token:"<<token<<std::endl;
            v_instrumentID.push_back(token);
        }
        // v_instrumentID = split_str1(_instrument_id, ',');
    }
    std::cout<<"check ins in main"<<v_instrumentID.size()<< std::endl;

    QTStrategyBase*  p_strtegy = new QTStrategyBase("ctp_demo");
    
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
