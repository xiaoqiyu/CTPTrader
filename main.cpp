#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
#include "include/INIReader.h"
#include "include/UserStruct.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "TickToKlineHelper.h"
#include "QTStrategyBase.h"
#include "helper.h"
#include "draft.h"

//ldd main
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib

int nRequestID = 0;
int DEBUG = 0;



int main(int argc, char *argv[])
{

#if false
    std::cout << "run draft" << std::endl;
#endif

    std::string _conf_file_name;
    std::string _instrument_id;
    if (argc <= 1)
    {
        std::cout << "Please enter a config name" << std::endl;
        _conf_file_name = "test";
        _instrument_id = "rb2110";
        // return 1;
    }else{

        _conf_file_name = argv[2];
        _instrument_id = argv[1];
    }
    QTStrategyBase*  p_strtegy = new QTStrategyBase("ctp_demo");
    int ret = p_strtegy->init(const_cast<char*>(_instrument_id.c_str()), _conf_file_name);
    p_strtegy->start();
    p_strtegy->stop();
    p_strtegy->release();

    return 0;
}
