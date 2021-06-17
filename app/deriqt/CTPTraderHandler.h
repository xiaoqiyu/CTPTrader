#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include "ThostFtdcTraderApi.h"
#include "UserStruct.h"
#include "ThostFtdcUserApiDataType.h"
#include "define.h"
#include "recordio.h"
#include "recordio_range.h"
#include "INIReader.h"
#include <glog/logging.h>

extern int nRequestID;

class CTPTraderHandler : public CThostFtdcTraderSpi
{
private:
    CThostFtdcTraderApi *_api = nullptr; //API对象
    thread _task_thread;                 //工作线程指针
    TaskQueue _task_queue;               //任务队列
    bool _active = false;                //工作状态
    mutex mutex_;
    condition_variable cond_; //条件变量
    bool ready_ = false;
    bool login_ = false;
    bool available_ = false; //用于交易查询的流控
    //TODO add account info, and trade status and trade summary(maintain trading status), after pocesss, this will be updated
    std::vector<std::string> future_instrumentID;
    std::vector<std::string> option_instrumentID;
    std::vector<std::string> main_future_instrumentID;
    DataQueue *p_order_data_queue = nullptr; //下单数据队列，数据类型为CThostFtdcInputOrderField
    std::string broker_id;
    std::string user_id;
    //HACK FOR TEST
    std::string _conf_file = "/home/kiki/projects/DERIQT_F/conf/ctp.ini";
    std::vector<CThostFtdcDepthMarketDataField*> v_depth_market_data;
    std::vector<CThostFtdcInstrumentField*> v_instruments;
    std::vector<CThostFtdcInvestorPositionField *> v_investor_position_fields;
    std::vector<CThostFtdcTradingAccountField*> v_trading_account;
    std::string task_tag;

public:
    CTPTraderHandler(){};

    ~CTPTraderHandler()
    {
        if (this->_active)
        {
            this->exit();
        }
        cout << "~CTPTradeHandler" << endl;
    };

    std::vector<CThostFtdcDepthMarketDataField*> get_depth_market_datas(std::vector<std::string> _v_instrument_id)
    {   
        for(auto it=v_depth_market_data.begin(); it!=v_depth_market_data.end(); ++it)
        {
            delete *it;
        }
        v_depth_market_data.clear();
        for(auto it = _v_instrument_id.begin(); it != _v_instrument_id.end(); ++it)
        {
            CThostFtdcQryDepthMarketDataField mkt_fields = {0};
	        std::strcpy(mkt_fields.InstrumentID, (*it).c_str());
            ReqQryDepthMarketData(&mkt_fields, nRequestID++);
            sleep(3);
        }
        return v_depth_market_data;
    }

    std::vector<CThostFtdcInstrumentField*> get_instruments(std::vector<std::string> _v_instrument_id)
    {
        for(auto it=v_instruments.begin(); it!=v_instruments.end(); ++it)
        {
            delete *it;
        }
        v_instruments.clear();
        for (auto it = _v_instrument_id.begin(); it!=_v_instrument_id.end();++it)
        {
            CThostFtdcQryInstrumentField pQryInstrument = {0};
            std::strcpy(pQryInstrument.InstrumentID, (*it).c_str());
            //TODO check return value of req
            int ret = ReqQryInstrument(&pQryInstrument, nRequestID++);
            LOG_IF(ERROR, ret!=0)<<"Error in ReqQryInstrument in get_instruments";
            sleep(3);
        }
        return v_instruments;
    }
    

    std::vector<std::string> GetFutureInstrumentID()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return login_ & available_;
        }); 
        return this->future_instrumentID;
    }

    std::vector<std::string> GetOptionInstrumentID()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return login_ & available_;
        }); 
        return this->option_instrumentID;
    }

    virtual void OnFrontConnected();

    virtual void OnFrontDisconnected(int nReason);

    virtual void OnHeartBeatWarning(int nTimeLapse);

    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    //TODO REMOVVE?
    //virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

    virtual void OnRtnBulletin(CThostFtdcBulletinField *pBulletin);

    virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

    virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

    virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

    virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

    virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

    virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);

    virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose);

    virtual void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction);

    virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);

    virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);

    virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);

    virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);

    virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

    virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);

    virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

    virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

    virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);

    virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);

    virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);

    virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);

    virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);

    virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);

    virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);

    void processFrontConnected(Task *task);

    void processFrontDisconnected(Task *task);

    void processHeartBeatWarning(Task *task);

    void processRspAuthenticate(Task *task);

    void processRspUserLogin(Task *task);

    void processRspUserLogout(Task *task);

    void processRspUserPasswordUpdate(Task *task);

    void processRspTradingAccountPasswordUpdate(Task *task);

    void processRspUserAuthMethod(Task *task);

    void processRspGenUserCaptcha(Task *task);

    void processRspGenUserText(Task *task);

    void processRspOrderInsert(Task *task);

    void processRspParkedOrderInsert(Task *task);

    void processRspParkedOrderAction(Task *task);

    void processRspOrderAction(Task *task);

    // void processRspQueryMaxOrderVolume(Task *task);

    void processRspSettlementInfoConfirm(Task *task);

    void processRspRemoveParkedOrder(Task *task);

    void processRspRemoveParkedOrderAction(Task *task);

    void processRspExecOrderInsert(Task *task);

    void processRspExecOrderAction(Task *task);

    void processRspForQuoteInsert(Task *task);

    void processRspQuoteInsert(Task *task);

    void processRspQuoteAction(Task *task);

    void processRspBatchOrderAction(Task *task);

    void processRspOptionSelfCloseInsert(Task *task);

    void processRspOptionSelfCloseAction(Task *task);

    void processRspCombActionInsert(Task *task);

    void processRspQryOrder(Task *task);

    void processRspQryTrade(Task *task);

    void processRspQryInvestorPosition(Task *task);

    void processRspQryTradingAccount(Task *task);

    void processRspQryInvestor(Task *task);

    void processRspQryTradingCode(Task *task);

    void processRspQryInstrumentMarginRate(Task *task);

    void processRspQryInstrumentCommissionRate(Task *task);

    void processRspQryExchange(Task *task);

    void processRspQryProduct(Task *task);

    void processRspQryInstrument(Task *task);

    void processRspQryDepthMarketData(Task *task);

    void processRspQrySettlementInfo(Task *task);

    void processRspQryTransferBank(Task *task);

    void processRspQryInvestorPositionDetail(Task *task);

    void processRspQryNotice(Task *task);

    void processRspQrySettlementInfoConfirm(Task *task);

    void processRspQryInvestorPositionCombineDetail(Task *task);

    void processRspQryCFMMCTradingAccountKey(Task *task);

    void processRspQryEWarrantOffset(Task *task);

    void processRspQryInvestorProductGroupMargin(Task *task);

    void processRspQryExchangeMarginRate(Task *task);

    void processRspQryExchangeMarginRateAdjust(Task *task);

    void processRspQryExchangeRate(Task *task);

    void processRspQrySecAgentACIDMap(Task *task);

    void processRspQryProductExchRate(Task *task);

    void processRspQryProductGroup(Task *task);

    void processRspQryMMInstrumentCommissionRate(Task *task);

    void processRspQryMMOptionInstrCommRate(Task *task);

    void processRspQryInstrumentOrderCommRate(Task *task);

    void processRspQrySecAgentTradingAccount(Task *task);

    void processRspQrySecAgentCheckMode(Task *task);

    void processRspQrySecAgentTradeInfo(Task *task);

    void processRspQryOptionInstrTradeCost(Task *task);

    void processRspQryOptionInstrCommRate(Task *task);

    void processRspQryExecOrder(Task *task);

    void processRspQryForQuote(Task *task);

    void processRspQryQuote(Task *task);

    void processRspQryOptionSelfClose(Task *task);

    void processRspQryInvestUnit(Task *task);

    void processRspQryCombInstrumentGuard(Task *task);

    void processRspQryCombAction(Task *task);

    void processRspQryTransferSerial(Task *task);

    void processRspQryAccountregister(Task *task);

    void processRspError(Task *task);

    void processRtnOrder(Task *task);

    void processRtnTrade(Task *task);

    void processErrRtnOrderInsert(Task *task);

    void processErrRtnOrderAction(Task *task);

    void processRtnInstrumentStatus(Task *task);

    void processRtnBulletin(Task *task);

    void processRtnTradingNotice(Task *task);

    void processRtnErrorConditionalOrder(Task *task);

    void processRtnExecOrder(Task *task);

    void processErrRtnExecOrderInsert(Task *task);

    void processErrRtnExecOrderAction(Task *task);

    void processErrRtnForQuoteInsert(Task *task);

    void processRtnQuote(Task *task);

    void processErrRtnQuoteInsert(Task *task);

    void processErrRtnQuoteAction(Task *task);

    void processRtnForQuoteRsp(Task *task);

    void processRtnCFMMCTradingAccountToken(Task *task);

    void processErrRtnBatchOrderAction(Task *task);

    void processRtnOptionSelfClose(Task *task);

    void processErrRtnOptionSelfCloseInsert(Task *task);

    void processErrRtnOptionSelfCloseAction(Task *task);

    void processRtnCombAction(Task *task);

    void processErrRtnCombActionInsert(Task *task);

    void processRspQryContractBank(Task *task);

    void processRspQryParkedOrder(Task *task);

    void processRspQryParkedOrderAction(Task *task);

    void processRspQryTradingNotice(Task *task);

    void processRspQryBrokerTradingParams(Task *task);

    void processRspQryBrokerTradingAlgos(Task *task);

    void processRspQueryCFMMCTradingAccountToken(Task *task);

    void processRtnFromBankToFutureByBank(Task *task);

    void processRtnFromFutureToBankByBank(Task *task);

    void processRtnRepealFromBankToFutureByBank(Task *task);

    void processRtnRepealFromFutureToBankByBank(Task *task);

    void processRtnFromBankToFutureByFuture(Task *task);

    void processRtnFromFutureToBankByFuture(Task *task);

    void processRtnRepealFromBankToFutureByFutureManual(Task *task);

    void processRtnRepealFromFutureToBankByFutureManual(Task *task);

    void processRtnQueryBankBalanceByFuture(Task *task);

    void processErrRtnBankToFutureByFuture(Task *task);

    void processErrRtnFutureToBankByFuture(Task *task);

    void processErrRtnRepealBankToFutureByFutureManual(Task *task);

    void processErrRtnRepealFutureToBankByFutureManual(Task *task);

    void processErrRtnQueryBankBalanceByFuture(Task *task);

    void processRtnRepealFromBankToFutureByFuture(Task *task);

    void processRtnRepealFromFutureToBankByFuture(Task *task);

    void processRspFromBankToFutureByFuture(Task *task);

    void processRspFromFutureToBankByFuture(Task *task);

    void processRspQueryBankAccountMoneyByFuture(Task *task);

    void processRtnOpenAccountByBank(Task *task);

    void processRtnCancelAccountByBank(Task *task);

    void processRtnChangeAccountByBank(Task *task);

    void processTask();

    bool CreateFtdcTraderApi(const char *pszFlowPath = "");

    void release();

    void init(const std::string& task_tag);

    int join();

    int exit();

    string getTradingDay();

    void RegisterFront(char *pszFrontAddress);

    void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType);

    void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType);

    int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID);

    int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID);

    int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);

    int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID);

    //请求查询产品
    int ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID);

    //请求查询合约
    int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);

    //请求查询深度行情
    int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID);

    //请求录入报单
    int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID);

    //请求查询主力合约
    void ReqQryMainContract(std::vector<std::string> productID, int nRequestID);

    ///请求查询报单
    int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID);

    ///请求查询成交
    int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID);

    ///请求查询投资者持仓
    int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);

    ///请求查询资金账户
    int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID);

    ///请求查询投资者持仓明细
	int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID);

    std::vector<CThostFtdcInvestorPositionField *> get_investor_position(std::string investor_id, std::string broker_id);

    std::vector<CThostFtdcTradingAccountField*> get_account(std::string investor_id, std::string broker_id);

    int req_trade(std::string investor_id, std::string broker_id);

    int get_position_details(std::string investor_id, std::string broker_id);

};
