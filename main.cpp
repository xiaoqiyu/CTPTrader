#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
#include "include/INIReader.h"
#include "include/ctp_queue.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "TickToKlineHelper.h"
#include "StrategyHandler.h"
//ldd main
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.


//TODO hack for testing, should be member of CTPMdHandler.
// MktDataQueue g_dataqueue;
// std::unordered_map<std::string, TickToKlineHelper> g_KlineHash; // k线存储表
std::string _conf_file_name = "ctp";

int main(int argc, char *argv[])
{

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
        std::cout << "Can't load config file in current directory:"<<_conf_file<<std::endl;
        return 1;
    }

    char mdAddr[40];
    int nRequestID = 0;
    char ch[40];

    CTPTraderHandler ctp;
    ctp.CreateFtdcTraderApi();
    ctp.RegisterFront(strcpy(ch, reader.Get("td", "FrontAddr", "127.0.0.1:1234").c_str()));
    ctp.init();
    sleep(5);

    CThostFtdcReqAuthenticateField reqAuth = {0};
    strcpy(reqAuth.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqAuth.UserID, reader.Get("user", "UserID", "123456").c_str());
    strcpy(reqAuth.AuthCode, reader.Get("user", "AuthCode", "!@#$%^&*").c_str());
    strcpy(reqAuth.AppID, reader.Get("user", "AppID", "MyProgram").c_str());

    ctp.ReqAuthenticate(&reqAuth, nRequestID++);
    sleep(5);

    CThostFtdcReqUserLoginField reqUserLogin = {0};
    strcpy(reqUserLogin.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqUserLogin.UserID, reader.Get("user", "UserID", "123456").c_str());
    strcpy(reqUserLogin.Password, reader.Get("user", "Password", "123456").c_str());
    strcpy(reqUserLogin.MacAddress, reader.Get("user", "MacAddress", "123456").c_str());
    strcpy(reqUserLogin.UserProductInfo, reader.Get("user", "UserProductInfo", "123456").c_str());

    ctp.ReqUserLogin(&reqUserLogin, nRequestID++);
    sleep(5);

    std::cout << "Trading date is: " << ctp.getTradingDay() << endl;

    vector<StrategyHandler* > vStrategyHandler;
    //init strategyhandler

	std::string strInstruments = reader.Get("md", "InstrumentID", "rb2110,m2109");
	std::stringstream sstr(strInstruments);
	std::string token;
	int cnt = 0;
    while (getline(sstr, token, ','))
    {
        StrategyHandler *_p_instrategy = new StrategyHandler();
        _p_instrategy->init(token.c_str(), &ctp);
        vStrategyHandler.push_back(_p_instrategy);
    }

    CTPMdHandler ctpMd(_conf_file);
    ctpMd.CreateFtdcMdApi();
    ctpMd.RegisterFront(strcpy(mdAddr, reader.Get("md", "FrontMdAddr", "127.0.0.1:1234").c_str()));
    ctpMd.init(vStrategyHandler);



    //cout << reader.Get("td", "FrontAddr", "127.0.0.1:1234") << endl;


    // CThostFtdcUserPasswordUpdateField reqUserPasswordUpdate = { 0 };
    // strcpy(reqUserPasswordUpdate.BrokerID, reader.Get("user","BrokerID","9999").c_str());
    // strcpy(reqUserPasswordUpdate.UserID, reader.Get("user","UserID","123456").c_str());
    // strcpy(reqUserPasswordUpdate.OldPassword, reader.Get("user","Password","123456").c_str());
    // strcpy(reqUserPasswordUpdate.NewPassword, reader.Get("user","SetPasswd","").c_str());

    // ctp.ReqUserPasswordUpdate(&reqUserPasswordUpdate, nRequestID++);
    // sleep(5);

    sleep(3600);

    vector<StrategyHandler *>::iterator iter = vStrategyHandler.begin();
    for (;iter!=vStrategyHandler.end(); iter++)
    {
        (*iter)->release();
    }

    CThostFtdcUserLogoutField reqUserLogout = {0};
    strcpy(reqUserLogout.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqUserLogout.UserID, reader.Get("user", "UserID", "123456").c_str());
    ctp.ReqUserLogout(&reqUserLogout, nRequestID++);
    sleep(5);

    ctp.exit();
    return 0;
}
