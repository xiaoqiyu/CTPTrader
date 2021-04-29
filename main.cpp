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
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

int nRequestID = 0;
int DEBUG = 0;

//TODO hack for testing, should be member of CTPMdHandler.
// MktDataQueue g_dataqueue;
// std::unordered_map<std::string, TickToKlineHelper> g_KlineHash; // k线存储表
std::string _conf_file_name = "ctp";

int main(int argc, char *argv[])
{

#if true
    std::cout << "run draft" << std::endl;
    // test_ptr();
    return 0;
#endif

    //HACK for debug
    if (argc <= 1)
    {
        std::cout << "Please enter a config name" << std::endl;
        // return 1;
    }

    char _conf_file[100] = {'\0'};
    // snprintf(_conf_file, 100, "conf/%s.ini", argv[1]);

    snprintf(_conf_file, 100, "conf/%s.ini", _conf_file_name.c_str());

    INIReader reader(_conf_file);
    if (reader.ParseError() != 0)
    {
        std::cout << "Can't load config file in current directory:" << _conf_file << std::endl;
        return 1;
    }

    char mdAddr[40];

    char ch[40];

    CTPTraderHandler ctp;
    ctp.CreateFtdcTraderApi();
    ctp.RegisterFront(strcpy(ch, reader.Get("td", "FrontAddr", "127.0.0.1:1234").c_str()));
    ctp.init();
    sleep(5);

    std::cout << "Start Authenticate----------------------------" << std::endl;
    CThostFtdcReqAuthenticateField reqAuth = {0};
    strcpy(reqAuth.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqAuth.UserID, reader.Get("user", "UserID", "123456").c_str());
    strcpy(reqAuth.AuthCode, reader.Get("user", "AuthCode", "!@#$%^&*").c_str());
    strcpy(reqAuth.AppID, reader.Get("user", "AppID", "MyProgram").c_str());

    ctp.ReqAuthenticate(&reqAuth, nRequestID++);
    sleep(5);

    std::cout << "Start ----------------------------" << std::endl;
    CThostFtdcReqUserLoginField reqUserLogin = {0};
    strcpy(reqUserLogin.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqUserLogin.UserID, reader.Get("user", "UserID", "123456").c_str());
    strcpy(reqUserLogin.Password, reader.Get("user", "Password", "123456").c_str());
    strcpy(reqUserLogin.MacAddress, reader.Get("user", "MacAddress", "123456").c_str());
    strcpy(reqUserLogin.UserProductInfo, reader.Get("user", "UserProductInfo", "123456").c_str());

    ctp.ReqUserLogin(&reqUserLogin, nRequestID++);
    sleep(5);

    std::string trading_date = ctp.getTradingDay();
    std::cout << "Trading date is: " << trading_date << endl;

    /*
    std::string ss = reader.Get("md", "ProductID", "rb,m");
    std::vector<std::string> vv = split_str(ss, ',');
    ctp.GetMainInstrumentID(vv, nRequestID++);

    sleep(60);
    std::cout<<"check instrument results---------------------------"<<std::endl;
    std::vector<std::string> vv_instr = ctp.GetFutureInstrumentID();
    std::cout<<vv_instr.size()<<std::endl;
	for(std::vector<std::string>::iterator iter=vv_instr.begin(); iter!=vv_instr.end();iter++)
	{
		std::cout<<(*iter)<<std::endl;
	}
    */

#if false
   CThostFtdcQryOrderField qry_order = {0};
   strcpy(qry_order.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
   strcpy(qry_order.InvestorID, reader.Get("user", "UserID", "123456").c_str());
   std::string _str = "rb2110";
   strcpy(qry_order.InstrumentID, _str.c_str());
   ctp.ReqQryOrder(&qry_order, nRequestID++);

#endif

#if true
    //create strategy handler and subscribe market data
    vector<QTStrategyBase *> vStrategyHandler;
    //init strategyhandler
    std::string strInstruments = reader.Get("md", "InstrumentID", "rb2110,m2109");
    std::stringstream sstr(strInstruments);
    std::string token;
    int cnt = 0;
    while (getline(sstr, token, ','))
    {
        QTStrategyBase *_p_instrategy = new QTStrategyBase("ctp_test");
        _p_instrategy->init(token.c_str(), &ctp, trading_date.c_str());
        vStrategyHandler.push_back(_p_instrategy);
    }

    CTPMdHandler ctpMd(_conf_file);
    ctpMd.CreateFtdcMdApi();
    ctpMd.RegisterFront(strcpy(mdAddr, reader.Get("md", "FrontMdAddr", "127.0.0.1:1234").c_str()));
    ctpMd.init(vStrategyHandler);

    sleep(3600);

    // vector<StrategyHandler *>::iterator iter = vStrategyHandler.begin();
    for (auto iter = vStrategyHandler.begin(); iter != vStrategyHandler.end(); iter++)
    {
        (*iter)->release();
    }

#endif

    //unsubscribe market data
    CThostFtdcUserLogoutField reqUserLogout = {0};
    strcpy(reqUserLogout.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqUserLogout.UserID, reader.Get("user", "UserID", "123456").c_str());
    ctp.ReqUserLogout(&reqUserLogout, nRequestID++);
    sleep(5);

    ctp.exit();
    return 0;
}
