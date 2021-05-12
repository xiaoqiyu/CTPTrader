#pragma once
// ---- 派生的行情类 ---- //
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>

#include "include/ThostFtdcMdApi.h"
#include "include/INIReader.h"
#include "include/UserStruct.h"
#include "include/define.h"
#include "TickToKlineHelper.h"

// INIReader reader;
extern int nRequestID;

class CTPMdHandler : public CThostFtdcMdSpi
{
private:
	CThostFtdcMdApi *g_pMdUserApi = nullptr;
	//MktDataQueue _data_queue;
	// thread  _data_thread[DATATHREADNUM];
	// unordered_map<string, QTStrategyBase *> dict_mkthandler;
	//TODO to be added
	bool ready_ = false;
	bool login_ = false;
	bool active_ = false;
	//TODO check this
	// vector<thread> data_thread_lst;
	// vector<QTStrategyBase *> strtegy_handler_lst;
	// thread data_thread_lst[100];
	// MktDataHandler* handler_lst[100];
	//TODO 不用作为成员变量
	mutex mutex_;
	condition_variable cond_; //条件变量
	int instrumentNum = 1;	  //行情合约订阅数量
	FileName _conf_file_name = {'\0'};
	// char *pInstrumentID[]; // 行情合约代码列表，中、上、大、郑交易所各选一种
	// TThostFtdcInstrumentIDType	InstrumentID  = {'\0'};
	std::vector<std::string> v_instrumentID;
	// thread data_thread;
	data_queue_ptr p_mktdata_queue = nullptr;
	std::string broker_id;
	std::string user_id;

	// ---- 继承自CTP父类的回调接口并实现 ---- //
public:
	CTPMdHandler(){};
	~CTPMdHandler()
	{
		if (this->active_)
		{
			this->exit();
		}
	};

	//TODO check friend
	data_queue_ptr get_data_queue() { return this->p_mktdata_queue; }

	void set_config(FileName _config_file)
	{
		std::strcpy(this->_conf_file_name, _config_file);
	}
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

	void init(std::vector<std::string> &v_instrumentid)
	{
		std::cout << "CTPMdHandler Init..." << std::endl;
		std::cout << v_instrumentID.size();
		this->g_pMdUserApi->Init();
		this->active_ = true;
		this->p_mktdata_queue = new DataQueue();
		for (auto iter = v_instrumentid.begin(); iter != v_instrumentid.end(); ++iter)
		{
			std::cout << "push in instrument:" << *iter << std::endl;
			this->v_instrumentID.push_back(*iter);
		}
		// strcpy(this->InstrumentID, instrument_id);
		cond_.notify_one();
	};

	void SubscribeMarketData();

	int join();

	void release();

	int exit();

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

	// ///行情数据处理线程函数
	// void ProcessData(QTStrategyBase *pStrategyHandler);
};
