#pragma once
// ---- 派生的行情类 ---- //
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>

#include "include/ThostFtdcMdApi.h"
#include "include/INIReader.h"
#include "include/ctp_queue.h"
#include "include/define.h"
#include "TickToKlineHelper.h"
#include "MktDataHandler.h"

extern INIReader reader;
extern MktDataQueue g_dataqueue;



class CTPMdHandler: public CThostFtdcMdSpi
{
private:
	CThostFtdcMdApi *g_pMdUserApi = nullptr;
	//MktDataQueue _data_queue; 
	// thread  _data_thread[DATATHREADNUM];
	unordered_map<string,MktDataHandler*> dict_mkthandler;
	//TODO to be added
	bool _ready = false;
	//TODO check this
	// vector<thread> data_thread_lst;
	vector<MktDataHandler*> data_handler_lst;
	thread data_thread_lst [100];
	// MktDataHandler* handler_lst[100];
	//TODO 不用作为成员变量
	int instrumentNum = 0; //行情合约订阅数量
	char *pInstrumentID[]; // 行情合约代码列表，中、上、大、郑交易所各选一种



	// ---- 继承自CTP父类的回调接口并实现 ---- //
public:
	CTPMdHandler(){
	
		// std::cout<<instrumentNum<<std::endl;
		// std::cout<<"finish constructor"<<std::endl;
	};
	~CTPMdHandler(){
		for(vector<MktDataHandler*>::iterator iter = this->data_handler_lst.begin();  iter!=this->data_handler_lst.end();++iter)
		{
			(*iter)->release();
		}
		this->g_pMdUserApi->Release();
		this->g_pMdUserApi=NULL;
	};
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	void OnFrontDisconnected(int nReason);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	void OnHeartBeatWarning(int nTimeLapse);

	//TODO PARAM?
	bool CreateFtdcMdApi();

	//TODO check param
	void RegisterFront(char *pszFrontAddress)
	{
    	return this->g_pMdUserApi->RegisterFront(pszFrontAddress);
	}

	void init()
	{
	std::cout<<"CTPMdHandler Init..."<<std::endl;
	this->g_pMdUserApi->Init();
	this->_ready = true;

	// for(int i = 0; i < DATATHREADNUM; ++i)
	// {
	// 	std::cout<<"Data Thread: "<<i<<"  start"<<std::endl;
	// 	this->_data_thread[i] = thread(&CTPMdHandler::ProcessData, this);
	// }
	//从conf 初始化合约代码
	std::string strInstruments = reader.Get("md","InstrumentID","rb2110,m2109");
	std::stringstream sstr(strInstruments);
	std::string token;
	int cnt = 0;
	// std::cout<<"Subscribe Instruments are: "<<std::endl;
	while(getline(sstr, token, ','))
	{
		pInstrumentID[cnt] = new char[token.length()+1];
		strcpy(pInstrumentID[cnt], token.c_str());
		std::cout<<"Market Data Handler "<<cnt<<" created for instrument: "<<token<<endl;
		MktDataHandler *_p_tmp = new MktDataHandler();
		_p_tmp->init(token.c_str());
		dict_mkthandler.insert(pair<string,MktDataHandler*>(token,_p_tmp));
		std::cout<<"Thread  "<<cnt<<" created for instrument: "<<token<<endl;
		this->data_handler_lst.push_back(_p_tmp);
		// std::thread t = std::thread(&CTPMdHandler::ProcessData, this, _p_tmp); 
		// this->data_thread_lst.push_back(t);
		this->data_thread_lst[cnt] = thread(&CTPMdHandler::ProcessData, this, _p_tmp); 
		cnt++;
	}
	instrumentNum = cnt;

	//TODO check the thread
    // this->_active = true;
    // this->_task_thread = thread(&CTPTraderHandler::processTask, this);
    // SubscribePrivateTopic(THOST_TERT_QUICK);
    // SubscribePublicTopic(THOST_TERT_QUICK);
	// std::cout<<"API version:\t";
    // std::cout << this->_api->GetApiVersion() << std::endl;
    // this->_api->Init();
	// //TODO check 
	// unique_lock<mutex> mlock(mutex_);
	// cond_.wait(mlock, [&]() {
	// 	return ready_;
	// }); //�ȴ���������֪ͨ
	};


	///登录请求响应
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅询价应答
	void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅询价应答
	void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	///询价通知
	void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	///行情数据处理线程函数
	void ProcessData(MktDataHandler *pMktDataHandler);
};

