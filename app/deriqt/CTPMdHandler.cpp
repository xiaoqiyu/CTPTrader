#include <iostream>
#include <fstream>
#include <unordered_map>
#include "CTPMdHandler.h"
#include "TickToKlineHelper.h"

// extern std::unordered_map<std::string, TickToKlineHelper> g_KlineHash; // k线存储表

// ---- ctp_api回调函数 ---- //
// 连接成功应答
void CTPMdHandler::OnFrontConnected()
{
	LOG(INFO) << "Success in OnFrontConnected ";
	ready_ = true;
	// 开始登录
	INIReader reader(this->_conf_file_name);
	CThostFtdcReqUserLoginField reqUserLogin = {0};
	strcpy(reqUserLogin.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
	strcpy(reqUserLogin.UserID, reader.Get("user", "UserID", "123456").c_str());
	strcpy(reqUserLogin.Password, reader.Get("user", "Password", "123456").c_str());
	strcpy(reqUserLogin.MacAddress, reader.Get("user", "MacAddress", "123456").c_str());
	strcpy(reqUserLogin.UserProductInfo, reader.Get("user", "UserProductInfo", "123456").c_str());
	this->broker_id = reader.Get("user", "BrokerID", "9999");
	this->user_id = reader.Get("user", "UserID", "123456");
	int rt = this->g_pMdUserApi->ReqUserLogin(&reqUserLogin, nRequestID);
	if (!rt)
		LOG(INFO)<< "Success in ReqUserLogin";
	else
		LOG(ERROR)<< "Error in ReqUserLogin";
}

// 断开连接通知
void CTPMdHandler::OnFrontDisconnected(int nReason)
{
	LOG(INFO)<<"OnFrontDisconnected with "<<nReason;
}

// 心跳超时警告
void CTPMdHandler::OnHeartBeatWarning(int nTimeLapse)
{
	LOG(WARNING)<< "OnHeartBeatWarning: " <<nTimeLapse;
}

bool CTPMdHandler::CreateFtdcMdApi()
{
	LOG(INFO)<< "Start CreateFtdcMdApi in Handler";
	this->g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
	if (nullptr == this->g_pMdUserApi)
		return false;
	this->g_pMdUserApi->RegisterSpi(this);
	return true;
}
// 登录应答
void CTPMdHandler::OnRspUserLogin(
	CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{

		LOG(INFO) << "Success for CTPMD login";
		LOG(INFO) << "Trading Date:" << pRspUserLogin->TradingDay;
		LOG(INFO) << "Login Time： " << pRspUserLogin->LoginTime;
		LOG(INFO) << "Broker ID： " << pRspUserLogin->BrokerID;
		LOG(INFO) << "User ID： " << pRspUserLogin->UserID;

		login_ = true;
		cond_.notify_one();
		// this->SubscribeMarketData();
	}
	else
		LOG(ERROR) << "Err in CTPMD Login->ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
}

void CTPMdHandler::SubscribeMarketData()
{
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]()
			   { return this->login_; });
	//Start Subscribe Depth Market data
	int instrument_len = this->v_instrumentID.size();
	char *p_InstrumentID[instrument_len];
	int cnt = 0;
	for (auto iter = this->v_instrumentID.begin(); iter != this->v_instrumentID.end(); ++iter)
	{
		std::string _ins = *iter;
		LOG(INFO) << "Subscribe Instrument ID:" << *iter;
		p_InstrumentID[cnt] = new TThostFtdcInstrumentIDType;
		strcpy(p_InstrumentID[cnt], _ins.c_str());
		cnt++;
	}
	int rt = this->g_pMdUserApi->SubscribeMarketData(p_InstrumentID, cnt);
	if (!rt)
		LOG(INFO) << "Sucess Send Request for Subscribe Depth Market";
	else
		LOG(ERROR) << "Fail Send Request for Subscribe Depth Market" << std::endl;
}
int CTPMdHandler::join()
{
	return this->g_pMdUserApi->Join();
}

void CTPMdHandler::release()
{
	this->g_pMdUserApi->Release();
	this->g_pMdUserApi = NULL;
	this->ready_ = false;
}

int CTPMdHandler::exit()
{
	this->active_ = false;
	// 取消订阅行情
	int instrument_len = this->v_instrumentID.size();
	char *p_InstrumentID[instrument_len];
	int cnt = 0;
	for (auto iter = this->v_instrumentID.begin(); iter != this->v_instrumentID.end(); ++iter)
	{
		std::string _ins = *iter;
		p_InstrumentID[cnt] = new TThostFtdcInstrumentIDType;
		strcpy(p_InstrumentID[cnt], _ins.c_str());
		cnt++;
	}
	int rt = g_pMdUserApi->UnSubscribeMarketData(p_InstrumentID, cnt);
	if (!rt)
		LOG(INFO) << ">>>>>>发送取消订阅行情请求成功";
	else
		LOG(ERROR) << "--->>>发送取消订阅行情请求失败";
	this->p_mktdata_cache_queue->terminate();

	//logout
	CThostFtdcUserLogoutField user_logout_fields = {0};
	std::strcpy(user_logout_fields.BrokerID, this->broker_id.c_str());
	std::strcpy(user_logout_fields.UserID, this->user_id.c_str());
	this->g_pMdUserApi->ReqUserLogout(&user_logout_fields, ++nRequestID);

	this->join();
	this->release();
	this->g_pMdUserApi->RegisterSpi(NULL);
	this->g_pMdUserApi = NULL;
	return 0;
}

// 登出应答
void CTPMdHandler::OnRspUserLogout(
	CThostFtdcUserLogoutField *pUserLogout,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		LOG(INFO) << "LogOut Success"
				  << "BrokerID: " << pUserLogout->BrokerID << ",UserID:" << pUserLogout->UserID;
	}
	else
		LOG(ERROR) << "LogOut Error-->>> ErrorID:" << pRspInfo->ErrorID << ", ErrorMsg:" << pRspInfo->ErrorMsg;
}

// 错误通知
void CTPMdHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		LOG(ERROR) << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
}

// 订阅行情应答
void CTPMdHandler::OnRspSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		LOG(INFO) << "Success in OnRspSubMarketData:" << pSpecificInstrument->InstrumentID;
	}
	else
		LOG(ERROR) << "Error in OnRspSubMarketData:" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
}

// 取消订阅行情应答
void CTPMdHandler::OnRspUnSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		LOG(INFO) << "Success in OnRspUnSubMarketData: " << pSpecificInstrument->InstrumentID;
	}
	else
		LOG(ERROR) << "Error in OnRspUnSubMarketData: ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
}

// 订阅询价应答
void CTPMdHandler::OnRspSubForQuoteRsp(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		LOG(INFO) << "Success in OnRspSubForQuoteRsp" << pSpecificInstrument->InstrumentID;
	}
	else
		LOG(ERROR) << "Error in OnRspSubForQuoteRsp--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
}

// 取消订阅询价应答
void CTPMdHandler::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		LOG(INFO) << "Success in OnRspUnSubForQuoteRsp" << pSpecificInstrument->InstrumentID;
	}
	else
		LOG(ERROR) << "Error in OnRspUnSubForQuoteRsp--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg;
}

// 行情详情通知
void CTPMdHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	// LOG(INFO)<<"return in dept market data";
	DataField data = DataField();
	data.data_type = FDEPTHMKT;
	CThostFtdcDepthMarketDataField *mkt_data = new CThostFtdcDepthMarketDataField();
	*mkt_data = *pDepthMarketData;
	data._data = mkt_data;
	this->p_mktdata_cache_queue->push(data);
}

// 询价详情通知
void CTPMdHandler::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	// 部分询价结果
	LOG(INFO) << "OnRtnForQuoteRsp: "<< ",Trading Date:" << pForQuoteRsp->TradingDay;
	LOG(INFO)<<"ExchangeID :" << pForQuoteRsp->ExchangeID << ",InstrumentID：" << pForQuoteRsp->InstrumentID << ",ForQuoteSysID：" << pForQuoteRsp->ForQuoteSysID;
}
