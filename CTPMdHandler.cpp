#include <iostream>
#include <fstream>
#include <unordered_map>
#include  "CTPMdHandler.h"
#include "TickToKlineHelper.h"

// extern std::unordered_map<std::string, TickToKlineHelper> g_KlineHash; // k线存储表

// ---- ctp_api回调函数 ---- //
// 连接成功应答
void CTPMdHandler::OnFrontConnected()
{
	std::cout << "=====建立网络连接成功=====" << std::endl;
	// 开始登录
	INIReader reader(this->conf_file);
    CThostFtdcReqUserLoginField reqUserLogin = { 0 };
    strcpy(reqUserLogin.BrokerID,reader.Get("user","BrokerID","9999").c_str());
    strcpy(reqUserLogin.UserID,reader.Get("user","UserID","123456").c_str());
    strcpy(reqUserLogin.Password,reader.Get("user","Password","123456").c_str());
    strcpy(reqUserLogin.MacAddress,reader.Get("user","MacAddress","123456").c_str());
    strcpy(reqUserLogin.UserProductInfo,reader.Get("user","UserProductInfo","123456").c_str());
	static int requestID = 0; // 请求编号
	int rt = this->g_pMdUserApi->ReqUserLogin(&reqUserLogin, requestID);
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
    std::cout<<"Start CreateFtdcMdApi in Handler"<<std::endl;
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
		std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;;
		// 开始订阅行情
		int rt = this->g_pMdUserApi->SubscribeMarketData(this->pInstrumentID, this->instrumentNum);
		if (!rt)
			std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
		else
			std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	std::cout<<"end of on rspuserlogin"<<std::endl;
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
		// 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储
		// char filePath[100] = {'\0'};
		// sprintf(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
		// std::ofstream outFile;
		// outFile.open(filePath, std::ios::out); // 新开文件
		// outFile << "合约代码" << ","
		// 	<< "更新时间" << ","
		// 	<< "最新价" << ","
		// 	<< "成交量" << ","
		// 	<< "买价一" << ","
		// 	<< "买量一" << ","
		// 	<< "卖价一" << ","
		// 	<< "卖量一" << ","
		// 	<< "持仓量" << ","
		// 	<< "换手率"
		// 	<< std::endl;
		// outFile.close();
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
	this->dict_mkthandler[pDepthMarketData->InstrumentID]->on_tick(pDepthMarketData);

	// 取消订阅行情
	//int rt = g_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, instrumentNum);
	//if (!rt)
	//	std::cout << ">>>>>>发送取消订阅行情请求成功" << std::endl;
	//else
	//	std::cerr << "--->>>发送取消订阅行情请求失败" << std::endl;
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

void CTPMdHandler::ProcessData(StrategyHandler* p_strategy)
{
	char * p_instrument = new char[11];
	p_instrument = p_strategy->getInstrumentID();
	// std::cout<<"============================Start Process Data for Instrument: "<<p_instrument<<std::endl;
	p_strategy->process_tick();
};



