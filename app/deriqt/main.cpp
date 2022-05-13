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
#include "QTStrategyBase.h"
#include <algorithm>
#include <glog/logging.h>
#include <sys/wait.h>
#include <cstdlib>

int nRequestID = 0;
int DEBUG = 0;


int main(int argc, char *argv[])
{

    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = std::string("./log/");
    //TODO remove hardcode of the path, with relative path
    system("cp /mnt/c/projects/pycharm/option_future_research/research/daily_models/daily_cache.ini ~/projects/DERIQT_F/conf/");
    system("cp /mnt/c/projects/pycharm/option_future_research/conf/strategy.ini ~/projects/DERIQT_F/conf/");

#ifdef true
    pid_t c_pid = fork();

    if (c_pid == -1) {
        perror("[main] Error of Fork subprocess,exit......");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) {
        LOG(INFO) << "[main] Start Parent/Market Subscribe Process (Subscribe Market data, and Calculate factor),with pid=>" << getpid();
        std::string _conf_file_name;
        std::string _instrument_id;
        std::string mode = "0";
        std::string strategy_class = "0";//FIXME hardcode for future first, 0 for future, 1 for options(TBD)
        std::string _strategy_name = "future_trend";
        std::vector<std::string> v_instrumentID;
        if (argc <= 1)
        {
            LOG(ERROR) << "[main] Please enter a config name!!!!!" ;
            _conf_file_name = "/home/kiki/projects/DERIQT/test.ini";
            v_instrumentID.push_back("rb2110");
            _strategy_name = "future_trend";
        }
        else
        {
            _conf_file_name = argv[3];
            _instrument_id = argv[2];
            // mode = argv[1];//the market process is set to mode 0
            std::stringstream sstr(_instrument_id);
            std::string token;
            while (getline(sstr, token, ','))
            {
                v_instrumentID.push_back(token);
            }
        }
        std::string _shm_name = _strategy_name+"_"+ v_instrumentID[0];
        QTStrategyBase *p_strategy = new QTStrategyBase(_shm_name, std::stoi(mode),_shm_name.c_str(), 65536,std::stoi(strategy_class));
        p_strategy->init(v_instrumentID, _conf_file_name);
        sleep(5);
        LOG(INFO)<<"[main] start strategy for Market Handler.......";
        p_strategy->start();
        p_strategy->stop();
        p_strategy->release();
        wait(nullptr);
    }else{
        LOG(INFO) << "[main] Start Child/Trader Process (handle signal, place order),with pid=>" << getpid();
        std::string _conf_file_name;
        std::string _instrument_id;
        std::string mode = "0";
        std::string strategy_class = "0";//FIXME hardcode for future first, 0 for future, 1 for options(TBD)
        std::string _strategy_name = "future_trend";
        std::vector<std::string> v_instrumentID;
        if (argc <= 1)
        {
            LOG(ERROR) << "[main] Please enter a config name!!!!!" ;
            _conf_file_name = "/home/kiki/projects/DERIQT/test.ini";
            v_instrumentID.push_back("rb2110");
            _strategy_name = "future_trend";
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

        std::string _shm_name = _strategy_name+"_"+ v_instrumentID[0];
        QTStrategyBase *p_strategy = new QTStrategyBase(_shm_name, std::stoi(mode),_shm_name.c_str(), 65536,std::stoi(strategy_class));
        p_strategy->init(v_instrumentID, _conf_file_name);
        sleep(5);
        LOG(INFO)<<"[main] start strategy for Trade Handler.......";
        p_strategy->start();
        p_strategy->stop();
        p_strategy->release();
        exit(EXIT_SUCCESS);
    }
    return EXIT_SUCCESS;

#endif

// #ifdef false

        std::string _conf_file_name;
        std::string _instrument_id;
        std::string mode = "0";
        std::string strategy_class = "0";//FIXME hardcode for future first, 0 for future, 1 for options(TBD)
        std::string _strategy_name = "future_trend";
        std::vector<std::string> v_instrumentID;
        if (argc <= 1)
        {
            LOG(ERROR) << "[main] Please enter a config name!!!!!" ;
            _conf_file_name = "/home/kiki/projects/DERIQT/test.ini";
            v_instrumentID.push_back("rb2110");
            _strategy_name = "future_trend";
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

        std::string _shm_name = _strategy_name+"_"+ v_instrumentID[0];
        QTStrategyBase *p_strategy = new QTStrategyBase(_shm_name, std::stoi(mode),_shm_name.c_str(), 65536,std::stoi(strategy_class));
        p_strategy->init(v_instrumentID, _conf_file_name);
        sleep(5);
        LOG(INFO)<<"[main] start strategy for Strategy Trader.......";
        p_strategy->start();
        p_strategy->stop();
        p_strategy->release();
    
// #endif
    return 0;
}
