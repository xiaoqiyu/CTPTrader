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
	std::cout << "=====建立网络连接成功=====" << std::endl;
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
		std::cout << ">>>>>>发送登录请求成功" << std::endl;
	else
		std::cerr << "--->>>发送登录请求失败" << std::endl;
}

// 断开连接通知
void CTPMdHandler::OnFrontDisconnected(int nReason)
{
	std::cerr << "=====网络连接断开=====" << std::endl;
	std::cerr << "错误码： " << nReason << std::endl;
}

// 心跳超时警告
void CTPMdHandler::OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "=====网络心跳超时=====" << std::endl;
	std::cerr << "距上次连接时间： " << nTimeLapse << std::endl;
}

bool CTPMdHandler::CreateFtdcMdApi()
{
	std::cout << "Start CreateFtdcMdApi in Handler" << std::endl;
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
		std::cout << "=====账户登录成功=====" << std::endl;
		std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;

		login_ = true;
		cond_.notify_one();
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	std::cout << "end of on rspuserlogin" << std::endl;
}

void CTPMdHandler::SubscribeMarketData()
{
	std::cout << "start sub market data==========" << std::endl;
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]()
			   { return this->login_; });
	// 开始订阅行情
	std::cout << "insrument size" << this->v_instrumentID.size() << std::endl;
	int instrument_len = this->v_instrumentID.size();
	char *p_InstrumentID[instrument_len];
	int cnt = 0;
	std::cout << "sub instruments-----------" << std::endl;
	for (auto iter = this->v_instrumentID.begin(); iter != this->v_instrumentID.end(); ++iter)
	{
		std::string _ins = *iter;
		std::cout << _ins << std::endl;
		p_InstrumentID[cnt] = new TThostFtdcInstrumentIDType;
		strcpy(p_InstrumentID[cnt], _ins.c_str());
		cnt++;
	}
	for (int i = 0; i < instrument_len; ++i)
	{
		std::cout << p_InstrumentID[i] << std::endl;
	}
	int rt = this->g_pMdUserApi->SubscribeMarketData(p_InstrumentID, cnt);
	if (!rt)
		std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
	else
		std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
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
		std::cout << ">>>>>>发送取消订阅行情请求成功" << std::endl;
	else
		std::cerr << "--->>>发送取消订阅行情请求失败" << std::endl;
	this->p_mktdata_queue->terminate();

	//logout
	CThostFtdcUserLogoutField user_logout_fields = {0};
	std::strcpy(user_logout_fields.BrokerID, this->broker_id.c_str());
	std::strcpy(user_logout_fields.UserID, this->user_id.c_str());
	this->g_pMdUserApi->ReqUserLogout(&user_logout_fields, ++nRequestID);

	//todo join here?
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
		std::cout << "=====账户登出成功=====" << std::endl;
		std::cout << "经纪商： " << pUserLogout->BrokerID << std::endl;
		std::cout << "帐户名： " << pUserLogout->UserID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 错误通知
void CTPMdHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
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
		std::cout << "=====订阅行情成功=====" << std::endl;
		std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
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
		std::cout << "=====取消订阅行情成功=====" << std::endl;
		std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
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
		std::cout << "=====订阅询价成功=====" << std::endl;
		std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 取消订阅询价应答
void CTPMdHandler::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====取消订阅询价成功=====" << std::endl;
		std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 行情详情通知
void CTPMdHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	// std::cout<<"Push data to queue: "<<pDepthMarketData->InstrumentID<<std::endl;
	// this->dict_mkthandler[pDepthMarketData->InstrumentID]->on_tick(pDepthMarketData);
	// std::cout<<"on return depth market data:"<<pDepthMarketData->InstrumentID<<std::endl;
	DataField data = DataField();
	data.data_type = FDEPTHMKT;
	CThostFtdcDepthMarketDataField *mkt_data = new CThostFtdcDepthMarketDataField();
	*mkt_data = *pDepthMarketData;
	data._data = mkt_data;
	// std::cout<<mkt_data->InstrumentID<<","<<endl;
	// std::cout<<p_mktdata_queue<<std::endl;
	this->p_mktdata_queue->push(data);
}

// 询价详情通知
void CTPMdHandler::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	// 部分询价结果
	std::cout << "=====获得询价结果=====" << std::endl;
	std::cout << "交易日： " << pForQuoteRsp->TradingDay << std::endl;
	std::cout << "交易所代码： " << pForQuoteRsp->ExchangeID << std::endl;
	std::cout << "合约代码： " << pForQuoteRsp->InstrumentID << std::endl;
	std::cout << "询价编号： " << pForQuoteRsp->ForQuoteSysID << std::endl;
}

// void CTPMdHandler::ProcessData(QTStrategyBase* p_strategy)
// {
// 	char * p_instrument = new char[11];
// 	p_instrument = p_strategy->getInstrumentID();
// 	// std::cout<<"============================Start Process Data for Instrument: "<<p_instrument<<std::endl;
// 	p_strategy->process_tick();
// };
