#include "CTPTraderHandler.h"

void CTPTraderHandler::OnFrontConnected()
{
    Task task = Task();
    task.task_name = ONFRONTCONNECTED;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnFrontDisconnected(int nReason)
{
    Task task = Task();
    task.task_name = ONFRONTDISCONNECTED;
    task.task_id = nReason;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnHeartBeatWarning(int nTimeLapse)
{
    Task task = Task();
    task.task_name = ONHEARTBEATWARNING;
    task.task_id = nTimeLapse;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOG(INFO)<<"OnRspUserAhtnticate";
    Task task = Task();
    task.task_name = ONRSPAUTHENTICATE;
    if (pRspAuthenticateField)
    {
        CThostFtdcRspAuthenticateField *task_data = new CThostFtdcRspAuthenticateField();
        *task_data = *pRspAuthenticateField;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    LOG(INFO) << "OnRspUserLogin";
    Task task = Task();
    task.task_name = ONRSPUSERLOGIN;
    if (pRspUserLogin)
    {
        CThostFtdcRspUserLoginField *task_data = new CThostFtdcRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGOUT;
    if (pUserLogout)
    {
        CThostFtdcUserLogoutField *task_data = new CThostFtdcUserLogoutField();
        *task_data = *pUserLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERPASSWORDUPDATE;
    if (pUserPasswordUpdate)
    {
        CThostFtdcUserPasswordUpdateField *task_data = new CThostFtdcUserPasswordUpdateField();
        *task_data = *pUserPasswordUpdate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPTRADINGACCOUNTPASSWORDUPDATE;
    if (pTradingAccountPasswordUpdate)
    {
        CThostFtdcTradingAccountPasswordUpdateField *task_data = new CThostFtdcTradingAccountPasswordUpdateField();
        *task_data = *pTradingAccountPasswordUpdate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERAUTHMETHOD;
    if (pRspUserAuthMethod)
    {
        CThostFtdcRspUserAuthMethodField *task_data = new CThostFtdcRspUserAuthMethodField();
        *task_data = *pRspUserAuthMethod;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPGENUSERCAPTCHA;
    if (pRspGenUserCaptcha)
    {
        CThostFtdcRspGenUserCaptchaField *task_data = new CThostFtdcRspGenUserCaptchaField();
        *task_data = *pRspGenUserCaptcha;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPGENUSERTEXT;
    if (pRspGenUserText)
    {
        CThostFtdcRspGenUserTextField *task_data = new CThostFtdcRspGenUserTextField();
        *task_data = *pRspGenUserText;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    // std::cout<<"OnRspOrderInsert"<<std::endl;
    Task task = Task();
    task.task_name = ONRSPORDERINSERT;
    if (pInputOrder)
    {
        CThostFtdcInputOrderField *task_data = new CThostFtdcInputOrderField();
        *task_data = *pInputOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPPARKEDORDERINSERT;
    if (pParkedOrder)
    {
        CThostFtdcParkedOrderField *task_data = new CThostFtdcParkedOrderField();
        *task_data = *pParkedOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPPARKEDORDERACTION;
    if (pParkedOrderAction)
    {
        CThostFtdcParkedOrderActionField *task_data = new CThostFtdcParkedOrderActionField();
        *task_data = *pParkedOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPORDERACTION;
    if (pInputOrderAction)
    {
        LOG(INFO)<<"OnRspOrderAction for symbol=>"<<pInputOrderAction->InstrumentID<<",order ref=>"<<pInputOrderAction->OrderRef<<",order sys ref=>"<<pInputOrderAction->OrderSysID;
        CThostFtdcInputOrderActionField *task_data = new CThostFtdcInputOrderActionField();
        *task_data = *pInputOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        LOG(INFO)<<"OnRspOrderAction Error Info=>"<<task_error<<",symbol=>"<<pInputOrderAction->InstrumentID<<",order ref=>"<<pInputOrderAction->OrderRef<<",order sys ref=>"<<pInputOrderAction->OrderSysID;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

//TODO REMOVE?
// void CTPTraderHandler::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
//     Task task = Task();
//     task.task_name = ONRSPQUERYMAXORDERVOLUME;
//     if (pQueryMaxOrderVolume)
//     {
//         CThostFtdcQueryMaxOrderVolumeField *task_data = new CThostFtdcQueryMaxOrderVolumeField();
//         *task_data = *pQueryMaxOrderVolume;
//         task.task_data = task_data;
//     }
//     if (pRspInfo)
//     {
//         CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
//         *task_error = *pRspInfo;
//         task.task_error = task_error;
//     }
//     task.task_id = nRequestID;
//     task.task_last = bIsLast;
//     this->_task_queue.push(task);
// };

void CTPTraderHandler::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPSETTLEMENTINFOCONFIRM;
    if (pSettlementInfoConfirm)
    {
        CThostFtdcSettlementInfoConfirmField *task_data = new CThostFtdcSettlementInfoConfirmField();
        *task_data = *pSettlementInfoConfirm;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPREMOVEPARKEDORDER;
    if (pRemoveParkedOrder)
    {
        CThostFtdcRemoveParkedOrderField *task_data = new CThostFtdcRemoveParkedOrderField();
        *task_data = *pRemoveParkedOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPREMOVEPARKEDORDERACTION;
    if (pRemoveParkedOrderAction)
    {
        CThostFtdcRemoveParkedOrderActionField *task_data = new CThostFtdcRemoveParkedOrderActionField();
        *task_data = *pRemoveParkedOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPEXECORDERINSERT;
    if (pInputExecOrder)
    {
        CThostFtdcInputExecOrderField *task_data = new CThostFtdcInputExecOrderField();
        *task_data = *pInputExecOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPEXECORDERACTION;
    if (pInputExecOrderAction)
    {
        CThostFtdcInputExecOrderActionField *task_data = new CThostFtdcInputExecOrderActionField();
        *task_data = *pInputExecOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPFORQUOTEINSERT;
    if (pInputForQuote)
    {
        CThostFtdcInputForQuoteField *task_data = new CThostFtdcInputForQuoteField();
        *task_data = *pInputForQuote;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUOTEINSERT;
    if (pInputQuote)
    {
        CThostFtdcInputQuoteField *task_data = new CThostFtdcInputQuoteField();
        *task_data = *pInputQuote;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUOTEACTION;
    if (pInputQuoteAction)
    {
        CThostFtdcInputQuoteActionField *task_data = new CThostFtdcInputQuoteActionField();
        *task_data = *pInputQuoteAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPBATCHORDERACTION;
    if (pInputBatchOrderAction)
    {
        CThostFtdcInputBatchOrderActionField *task_data = new CThostFtdcInputBatchOrderActionField();
        *task_data = *pInputBatchOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPOPTIONSELFCLOSEINSERT;
    if (pInputOptionSelfClose)
    {
        CThostFtdcInputOptionSelfCloseField *task_data = new CThostFtdcInputOptionSelfCloseField();
        *task_data = *pInputOptionSelfClose;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPOPTIONSELFCLOSEACTION;
    if (pInputOptionSelfCloseAction)
    {
        CThostFtdcInputOptionSelfCloseActionField *task_data = new CThostFtdcInputOptionSelfCloseActionField();
        *task_data = *pInputOptionSelfCloseAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPCOMBACTIONINSERT;
    if (pInputCombAction)
    {
        CThostFtdcInputCombActionField *task_data = new CThostFtdcInputCombActionField();
        *task_data = *pInputCombAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOG(INFO)<<"OnRspQryOrder";
    Task task = Task();
    task.task_name = ONRSPQRYORDER;
    if (pOrder)
    {
        CThostFtdcOrderField *task_data = new CThostFtdcOrderField();
        *task_data = *pOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {

        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error in OnRspQryOrder";
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOG(INFO)<<"OnRspQryTrade";
    Task task = Task();
    task.task_name = ONRSPQRYTRADE;
    if (pTrade)
    {
        CThostFtdcTradeField *task_data = new CThostFtdcTradeField();
        *task_data = *pTrade;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOG(INFO)<<"OnRspQryInvestorPosition";
    Task task = Task();
    task.task_name = ONRSPQRYINVESTORPOSITION;
    if (pInvestorPosition)
    {
        CThostFtdcInvestorPositionField *task_data = new CThostFtdcInvestorPositionField();
        *task_data = *pInvestorPosition;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOG(INFO)<<"OnRspQryTradingAccount";
    Task task = Task();
    task.task_name = ONRSPQRYTRADINGACCOUNT;
    if (pTradingAccount)
    {
        CThostFtdcTradingAccountField *task_data = new CThostFtdcTradingAccountField();
        *task_data = *pTradingAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTOR;
    if (pInvestor)
    {
        CThostFtdcInvestorField *task_data = new CThostFtdcInvestorField();
        *task_data = *pInvestor;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRADINGCODE;
    if (pTradingCode)
    {
        CThostFtdcTradingCodeField *task_data = new CThostFtdcTradingCodeField();
        *task_data = *pTradingCode;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    LOG(INFO)<<"ONRSPQRYINSTRUMENT";
    Task task = Task();
    task.task_name = ONRSPQRYINSTRUMENTMARGINRATE;
    if (pInstrumentMarginRate)
    {
        CThostFtdcInstrumentMarginRateField *task_data = new CThostFtdcInstrumentMarginRateField();
        *task_data = *pInstrumentMarginRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINSTRUMENTCOMMISSIONRATE;
    if (pInstrumentCommissionRate)
    {
        CThostFtdcInstrumentCommissionRateField *task_data = new CThostFtdcInstrumentCommissionRateField();
        *task_data = *pInstrumentCommissionRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXCHANGE;
    if (pExchange)
    {
        CThostFtdcExchangeField *task_data = new CThostFtdcExchangeField();
        *task_data = *pExchange;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPRODUCT;
    if (pProduct)
    {
        CThostFtdcProductField *task_data = new CThostFtdcProductField();
        *task_data = *pProduct;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINSTRUMENT;
    if (pInstrument)
    {
        CThostFtdcInstrumentField *task_data = new CThostFtdcInstrumentField();
        *task_data = *pInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYDEPTHMARKETDATA;
    if (pDepthMarketData)
    {
        CThostFtdcDepthMarketDataField *task_data = new CThostFtdcDepthMarketDataField();
        *task_data = *pDepthMarketData;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSETTLEMENTINFO;
    if (pSettlementInfo)
    {
        CThostFtdcSettlementInfoField *task_data = new CThostFtdcSettlementInfoField();
        *task_data = *pSettlementInfo;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRANSFERBANK;
    if (pTransferBank)
    {
        CThostFtdcTransferBankField *task_data = new CThostFtdcTransferBankField();
        *task_data = *pTransferBank;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;
    if (pInvestorPositionDetail)
    {
        CThostFtdcInvestorPositionDetailField *task_data = new CThostFtdcInvestorPositionDetailField();
        *task_data = *pInvestorPositionDetail;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYNOTICE;
    if (pNotice)
    {
        CThostFtdcNoticeField *task_data = new CThostFtdcNoticeField();
        *task_data = *pNotice;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSETTLEMENTINFOCONFIRM;
    if (pSettlementInfoConfirm)
    {
        CThostFtdcSettlementInfoConfirmField *task_data = new CThostFtdcSettlementInfoConfirmField();
        *task_data = *pSettlementInfoConfirm;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL;
    if (pInvestorPositionCombineDetail)
    {
        CThostFtdcInvestorPositionCombineDetailField *task_data = new CThostFtdcInvestorPositionCombineDetailField();
        *task_data = *pInvestorPositionCombineDetail;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCFMMCTRADINGACCOUNTKEY;
    if (pCFMMCTradingAccountKey)
    {
        CThostFtdcCFMMCTradingAccountKeyField *task_data = new CThostFtdcCFMMCTradingAccountKeyField();
        *task_data = *pCFMMCTradingAccountKey;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEWARRANTOFFSET;
    if (pEWarrantOffset)
    {
        CThostFtdcEWarrantOffsetField *task_data = new CThostFtdcEWarrantOffsetField();
        *task_data = *pEWarrantOffset;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTORPRODUCTGROUPMARGIN;
    if (pInvestorProductGroupMargin)
    {
        CThostFtdcInvestorProductGroupMarginField *task_data = new CThostFtdcInvestorProductGroupMarginField();
        *task_data = *pInvestorProductGroupMargin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXCHANGEMARGINRATE;
    if (pExchangeMarginRate)
    {
        CThostFtdcExchangeMarginRateField *task_data = new CThostFtdcExchangeMarginRateField();
        *task_data = *pExchangeMarginRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXCHANGEMARGINRATEADJUST;
    if (pExchangeMarginRateAdjust)
    {
        CThostFtdcExchangeMarginRateAdjustField *task_data = new CThostFtdcExchangeMarginRateAdjustField();
        *task_data = *pExchangeMarginRateAdjust;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXCHANGERATE;
    if (pExchangeRate)
    {
        CThostFtdcExchangeRateField *task_data = new CThostFtdcExchangeRateField();
        *task_data = *pExchangeRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSECAGENTACIDMAP;
    if (pSecAgentACIDMap)
    {
        CThostFtdcSecAgentACIDMapField *task_data = new CThostFtdcSecAgentACIDMapField();
        *task_data = *pSecAgentACIDMap;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPRODUCTEXCHRATE;
    if (pProductExchRate)
    {
        CThostFtdcProductExchRateField *task_data = new CThostFtdcProductExchRateField();
        *task_data = *pProductExchRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPRODUCTGROUP;
    if (pProductGroup)
    {
        CThostFtdcProductGroupField *task_data = new CThostFtdcProductGroupField();
        *task_data = *pProductGroup;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYMMINSTRUMENTCOMMISSIONRATE;
    if (pMMInstrumentCommissionRate)
    {
        CThostFtdcMMInstrumentCommissionRateField *task_data = new CThostFtdcMMInstrumentCommissionRateField();
        *task_data = *pMMInstrumentCommissionRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYMMOPTIONINSTRCOMMRATE;
    if (pMMOptionInstrCommRate)
    {
        CThostFtdcMMOptionInstrCommRateField *task_data = new CThostFtdcMMOptionInstrCommRateField();
        *task_data = *pMMOptionInstrCommRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINSTRUMENTORDERCOMMRATE;
    if (pInstrumentOrderCommRate)
    {
        CThostFtdcInstrumentOrderCommRateField *task_data = new CThostFtdcInstrumentOrderCommRateField();
        *task_data = *pInstrumentOrderCommRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSECAGENTTRADINGACCOUNT;
    if (pTradingAccount)
    {
        CThostFtdcTradingAccountField *task_data = new CThostFtdcTradingAccountField();
        *task_data = *pTradingAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSECAGENTCHECKMODE;
    if (pSecAgentCheckMode)
    {
        CThostFtdcSecAgentCheckModeField *task_data = new CThostFtdcSecAgentCheckModeField();
        *task_data = *pSecAgentCheckMode;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYSECAGENTTRADEINFO;
    if (pSecAgentTradeInfo)
    {
        CThostFtdcSecAgentTradeInfoField *task_data = new CThostFtdcSecAgentTradeInfoField();
        *task_data = *pSecAgentTradeInfo;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYOPTIONINSTRTRADECOST;
    if (pOptionInstrTradeCost)
    {
        CThostFtdcOptionInstrTradeCostField *task_data = new CThostFtdcOptionInstrTradeCostField();
        *task_data = *pOptionInstrTradeCost;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYOPTIONINSTRCOMMRATE;
    if (pOptionInstrCommRate)
    {
        CThostFtdcOptionInstrCommRateField *task_data = new CThostFtdcOptionInstrCommRateField();
        *task_data = *pOptionInstrCommRate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYEXECORDER;
    if (pExecOrder)
    {
        CThostFtdcExecOrderField *task_data = new CThostFtdcExecOrderField();
        *task_data = *pExecOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYFORQUOTE;
    if (pForQuote)
    {
        CThostFtdcForQuoteField *task_data = new CThostFtdcForQuoteField();
        *task_data = *pForQuote;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYQUOTE;
    if (pQuote)
    {
        CThostFtdcQuoteField *task_data = new CThostFtdcQuoteField();
        *task_data = *pQuote;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYOPTIONSELFCLOSE;
    if (pOptionSelfClose)
    {
        CThostFtdcOptionSelfCloseField *task_data = new CThostFtdcOptionSelfCloseField();
        *task_data = *pOptionSelfClose;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTUNIT;
    if (pInvestUnit)
    {
        CThostFtdcInvestUnitField *task_data = new CThostFtdcInvestUnitField();
        *task_data = *pInvestUnit;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCOMBINSTRUMENTGUARD;
    if (pCombInstrumentGuard)
    {
        CThostFtdcCombInstrumentGuardField *task_data = new CThostFtdcCombInstrumentGuardField();
        *task_data = *pCombInstrumentGuard;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCOMBACTION;
    if (pCombAction)
    {
        CThostFtdcCombActionField *task_data = new CThostFtdcCombActionField();
        *task_data = *pCombAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRANSFERSERIAL;
    if (pTransferSerial)
    {
        CThostFtdcTransferSerialField *task_data = new CThostFtdcTransferSerialField();
        *task_data = *pTransferSerial;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYACCOUNTREGISTER;
    if (pAccountregister)
    {
        CThostFtdcAccountregisterField *task_data = new CThostFtdcAccountregisterField();
        *task_data = *pAccountregister;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERROR;
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    std::cout<<"on rtn order:"<<std::endl;
    Task task = Task();
    task.task_name = ONRTNORDER;
    if (pOrder)
    {
        CThostFtdcOrderField *task_data = new CThostFtdcOrderField();
        *task_data = *pOrder;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    std::cout<<"on rtn trade"<<std::endl;
    Task task = Task();
    task.task_name = ONRTNTRADE;
    if (pTrade)
    {
        CThostFtdcTradeField *task_data = new CThostFtdcTradeField();
        *task_data = *pTrade;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    std::cout<<"OnErrRtn order insert"<<std::endl;
    Task task = Task();
    task.task_name = ONERRRTNORDERINSERT;
    if (pInputOrder)
    {
        CThostFtdcInputOrderField *task_data = new CThostFtdcInputOrderField();
        *task_data = *pInputOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNORDERACTION;
    if (pOrderAction)
    {
        CThostFtdcOrderActionField *task_data = new CThostFtdcOrderActionField();
        *task_data = *pOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
    Task task = Task();
    task.task_name = ONRTNINSTRUMENTSTATUS;
    if (pInstrumentStatus)
    {
        CThostFtdcInstrumentStatusField *task_data = new CThostFtdcInstrumentStatusField();
        *task_data = *pInstrumentStatus;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnBulletin(CThostFtdcBulletinField *pBulletin)
{
    Task task = Task();
    task.task_name = ONRTNBULLETIN;
    if (pBulletin)
    {
        CThostFtdcBulletinField *task_data = new CThostFtdcBulletinField();
        *task_data = *pBulletin;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    Task task = Task();
    task.task_name = ONRTNTRADINGNOTICE;
    if (pTradingNoticeInfo)
    {
        CThostFtdcTradingNoticeInfoField *task_data = new CThostFtdcTradingNoticeInfoField();
        *task_data = *pTradingNoticeInfo;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)
{
    Task task = Task();
    task.task_name = ONRTNERRORCONDITIONALORDER;
    if (pErrorConditionalOrder)
    {
        CThostFtdcErrorConditionalOrderField *task_data = new CThostFtdcErrorConditionalOrderField();
        *task_data = *pErrorConditionalOrder;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
    Task task = Task();
    task.task_name = ONRTNEXECORDER;
    if (pExecOrder)
    {
        CThostFtdcExecOrderField *task_data = new CThostFtdcExecOrderField();
        *task_data = *pExecOrder;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNEXECORDERINSERT;
    if (pInputExecOrder)
    {
        CThostFtdcInputExecOrderField *task_data = new CThostFtdcInputExecOrderField();
        *task_data = *pInputExecOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNEXECORDERACTION;
    if (pExecOrderAction)
    {
        CThostFtdcExecOrderActionField *task_data = new CThostFtdcExecOrderActionField();
        *task_data = *pExecOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNFORQUOTEINSERT;
    if (pInputForQuote)
    {
        CThostFtdcInputForQuoteField *task_data = new CThostFtdcInputForQuoteField();
        *task_data = *pInputForQuote;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
    Task task = Task();
    task.task_name = ONRTNQUOTE;
    if (pQuote)
    {
        CThostFtdcQuoteField *task_data = new CThostFtdcQuoteField();
        *task_data = *pQuote;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNQUOTEINSERT;
    if (pInputQuote)
    {
        CThostFtdcInputQuoteField *task_data = new CThostFtdcInputQuoteField();
        *task_data = *pInputQuote;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNQUOTEACTION;
    if (pQuoteAction)
    {
        CThostFtdcQuoteActionField *task_data = new CThostFtdcQuoteActionField();
        *task_data = *pQuoteAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    Task task = Task();
    task.task_name = ONRTNFORQUOTERSP;
    if (pForQuoteRsp)
    {
        CThostFtdcForQuoteRspField *task_data = new CThostFtdcForQuoteRspField();
        *task_data = *pForQuoteRsp;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)
{
    Task task = Task();
    task.task_name = ONRTNCFMMCTRADINGACCOUNTTOKEN;
    if (pCFMMCTradingAccountToken)
    {
        CThostFtdcCFMMCTradingAccountTokenField *task_data = new CThostFtdcCFMMCTradingAccountTokenField();
        *task_data = *pCFMMCTradingAccountToken;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNBATCHORDERACTION;
    if (pBatchOrderAction)
    {
        CThostFtdcBatchOrderActionField *task_data = new CThostFtdcBatchOrderActionField();
        *task_data = *pBatchOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose)
{
    Task task = Task();
    task.task_name = ONRTNOPTIONSELFCLOSE;
    if (pOptionSelfClose)
    {
        CThostFtdcOptionSelfCloseField *task_data = new CThostFtdcOptionSelfCloseField();
        *task_data = *pOptionSelfClose;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNOPTIONSELFCLOSEINSERT;
    if (pInputOptionSelfClose)
    {
        CThostFtdcInputOptionSelfCloseField *task_data = new CThostFtdcInputOptionSelfCloseField();
        *task_data = *pInputOptionSelfClose;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNOPTIONSELFCLOSEACTION;
    if (pOptionSelfCloseAction)
    {
        CThostFtdcOptionSelfCloseActionField *task_data = new CThostFtdcOptionSelfCloseActionField();
        *task_data = *pOptionSelfCloseAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnCombAction(CThostFtdcCombActionField *pCombAction)
{
    Task task = Task();
    task.task_name = ONRTNCOMBACTION;
    if (pCombAction)
    {
        CThostFtdcCombActionField *task_data = new CThostFtdcCombActionField();
        *task_data = *pCombAction;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNCOMBACTIONINSERT;
    if (pInputCombAction)
    {
        CThostFtdcInputCombActionField *task_data = new CThostFtdcInputCombActionField();
        *task_data = *pInputCombAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYCONTRACTBANK;
    if (pContractBank)
    {
        CThostFtdcContractBankField *task_data = new CThostFtdcContractBankField();
        *task_data = *pContractBank;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPARKEDORDER;
    if (pParkedOrder)
    {
        CThostFtdcParkedOrderField *task_data = new CThostFtdcParkedOrderField();
        *task_data = *pParkedOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYPARKEDORDERACTION;
    if (pParkedOrderAction)
    {
        CThostFtdcParkedOrderActionField *task_data = new CThostFtdcParkedOrderActionField();
        *task_data = *pParkedOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRADINGNOTICE;
    if (pTradingNotice)
    {
        CThostFtdcTradingNoticeField *task_data = new CThostFtdcTradingNoticeField();
        *task_data = *pTradingNotice;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYBROKERTRADINGPARAMS;
    if (pBrokerTradingParams)
    {
        CThostFtdcBrokerTradingParamsField *task_data = new CThostFtdcBrokerTradingParamsField();
        *task_data = *pBrokerTradingParams;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYBROKERTRADINGALGOS;
    if (pBrokerTradingAlgos)
    {
        CThostFtdcBrokerTradingAlgosField *task_data = new CThostFtdcBrokerTradingAlgosField();
        *task_data = *pBrokerTradingAlgos;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN;
    if (pQueryCFMMCTradingAccountToken)
    {
        CThostFtdcQueryCFMMCTradingAccountTokenField *task_data = new CThostFtdcQueryCFMMCTradingAccountTokenField();
        *task_data = *pQueryCFMMCTradingAccountToken;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)
{
    Task task = Task();
    task.task_name = ONRTNFROMBANKTOFUTUREBYBANK;
    if (pRspTransfer)
    {
        CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
        *task_data = *pRspTransfer;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)
{
    Task task = Task();
    task.task_name = ONRTNFROMFUTURETOBANKBYBANK;
    if (pRspTransfer)
    {
        CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
        *task_data = *pRspTransfer;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)
{
    Task task = Task();
    task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYBANK;
    if (pRspRepeal)
    {
        CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
        *task_data = *pRspRepeal;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)
{
    Task task = Task();
    task.task_name = ONRTNREPEALFROMFUTURETOBANKBYBANK;
    if (pRspRepeal)
    {
        CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
        *task_data = *pRspRepeal;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
    Task task = Task();
    task.task_name = ONRTNFROMBANKTOFUTUREBYFUTURE;
    if (pRspTransfer)
    {
        CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
        *task_data = *pRspTransfer;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
    Task task = Task();
    task.task_name = ONRTNFROMFUTURETOBANKBYFUTURE;
    if (pRspTransfer)
    {
        CThostFtdcRspTransferField *task_data = new CThostFtdcRspTransferField();
        *task_data = *pRspTransfer;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
    Task task = Task();
    task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL;
    if (pRspRepeal)
    {
        CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
        *task_data = *pRspRepeal;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
    Task task = Task();
    task.task_name = ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL;
    if (pRspRepeal)
    {
        CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
        *task_data = *pRspRepeal;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
    Task task = Task();
    task.task_name = ONRTNQUERYBANKBALANCEBYFUTURE;
    if (pNotifyQueryAccount)
    {
        CThostFtdcNotifyQueryAccountField *task_data = new CThostFtdcNotifyQueryAccountField();
        *task_data = *pNotifyQueryAccount;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNBANKTOFUTUREBYFUTURE;
    if (pReqTransfer)
    {
        CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
        *task_data = *pReqTransfer;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNFUTURETOBANKBYFUTURE;
    if (pReqTransfer)
    {
        CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
        *task_data = *pReqTransfer;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL;
    if (pReqRepeal)
    {
        CThostFtdcReqRepealField *task_data = new CThostFtdcReqRepealField();
        *task_data = *pReqRepeal;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL;
    if (pReqRepeal)
    {
        CThostFtdcReqRepealField *task_data = new CThostFtdcReqRepealField();
        *task_data = *pReqRepeal;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNQUERYBANKBALANCEBYFUTURE;
    if (pReqQueryAccount)
    {
        CThostFtdcReqQueryAccountField *task_data = new CThostFtdcReqQueryAccountField();
        *task_data = *pReqQueryAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
    Task task = Task();
    task.task_name = ONRTNREPEALFROMBANKTOFUTUREBYFUTURE;
    if (pRspRepeal)
    {
        CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
        *task_data = *pRspRepeal;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
    Task task = Task();
    task.task_name = ONRTNREPEALFROMFUTURETOBANKBYFUTURE;
    if (pRspRepeal)
    {
        CThostFtdcRspRepealField *task_data = new CThostFtdcRspRepealField();
        *task_data = *pRspRepeal;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPFROMBANKTOFUTUREBYFUTURE;
    if (pReqTransfer)
    {
        CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
        *task_data = *pReqTransfer;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPFROMFUTURETOBANKBYFUTURE;
    if (pReqTransfer)
    {
        CThostFtdcReqTransferField *task_data = new CThostFtdcReqTransferField();
        *task_data = *pReqTransfer;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQUERYBANKACCOUNTMONEYBYFUTURE;
    if (pReqQueryAccount)
    {
        CThostFtdcReqQueryAccountField *task_data = new CThostFtdcReqQueryAccountField();
        *task_data = *pReqQueryAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)
{
    Task task = Task();
    task.task_name = ONRTNOPENACCOUNTBYBANK;
    if (pOpenAccount)
    {
        CThostFtdcOpenAccountField *task_data = new CThostFtdcOpenAccountField();
        *task_data = *pOpenAccount;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)
{
    Task task = Task();
    task.task_name = ONRTNCANCELACCOUNTBYBANK;
    if (pCancelAccount)
    {
        CThostFtdcCancelAccountField *task_data = new CThostFtdcCancelAccountField();
        *task_data = *pCancelAccount;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};

void CTPTraderHandler::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)
{
    Task task = Task();
    task.task_name = ONRTNCHANGEACCOUNTBYBANK;
    if (pChangeAccount)
    {
        CThostFtdcChangeAccountField *task_data = new CThostFtdcChangeAccountField();
        *task_data = *pChangeAccount;
        task.task_data = task_data;
    }
    this->_task_queue.push(task);
};
void CTPTraderHandler::processFrontConnected(Task* task)
{
    LOG(INFO)<<"CTP TD Front Connected, API VERSION:"<<this->_api->GetApiVersion();
    connected_ = true;
    cond_.notify_all();
};

void CTPTraderHandler::processFrontDisconnected(Task* task)
{
    connected_=false;
    LOG(INFO)<<"Disconnect and Reconnect......";
};

void CTPTraderHandler::processHeartBeatWarning(Task* task)
{
    LOG(INFO)<<"Heart beat response......";
};

void CTPTraderHandler::processRspAuthenticate(Task* task)
{
    
	if (task->task_data)
	{
		CThostFtdcRspAuthenticateField* task_data = reinterpret_cast<CThostFtdcRspAuthenticateField*>(task->task_data);
		LOG(INFO)<<"processRspAuthenticate->BrokerID: "<<task_data->BrokerID<<", UserID:"<<task_data->UserID<<",AppID:"<<task_data->AppID;
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(FATAL, task_error->ErrorID!=0)<<"Error processRspAuthenticate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspUserLogin(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspUserLoginField* task_data = reinterpret_cast<CThostFtdcRspUserLoginField*>(task->task_data);
		LOG(INFO)<<"[processRspUserLogin]"<<task_data->TradingDay<<",FrontID=>"<<task_data->FrontID<<",SessionID=>"<<task_data->SessionID;
        std::time_t now_time = std::time(nullptr);
        tm *ltm = localtime(&now_time);
        strcpy(this->_login_time, task_data->LoginTime);
        LOG(INFO)<<"Login Success,login_time=>"<<task_data->LoginTime<<",上期所=>"<<task_data->SHFETime<<",大商所=>"<<task_data->DCETime<<"郑商所=>"<<task_data->CZCETime<<",中金所=>"<<task_data->FFEXTime<<",上期能源=>"<<task_data->INETime<<",local time=>"<<ltm->tm_min<<":"<<ltm->tm_sec;
        this->front_id = task_data->FrontID;
        this->sessision_id = task_data->SessionID;
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG(INFO)<<"Error MSG User Login:"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
        LOG_IF(FATAL, task_error->ErrorID!=0)<<"LOG IN FAIL";
		delete task_error;
	}
	login_ = true;
	available_ = true;
	cond_.notify_one(); 
};

void CTPTraderHandler::processRspUserLogout(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcUserLogoutField* task_data = reinterpret_cast<CThostFtdcUserLogoutField*>(task->task_data);
        LOG(INFO)<<"processRspUserLogout->"<<"BrokerID:"<<task_data->BrokerID<<",UserID:"<<task_data->UserID;
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG(INFO)<<"Error MSG User Logout->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
        LOG_IF(FATAL, task_error->ErrorID!=0)<<"LOG OUT FAIL";
		delete task_error;
	}
};

void CTPTraderHandler::processRspUserPasswordUpdate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcUserPasswordUpdateField* task_data = reinterpret_cast<CThostFtdcUserPasswordUpdateField*>(task->task_data);
		LOG(INFO)<<"processRspUserPasswordUpdate->"<<"BrokerID:"<<task_data->BrokerID<<",UserID:"<<task_data->UserID<<"OldPwd:"<<task_data->OldPassword<<",NewPwd:"<<task_data->NewPassword;
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspUserPasswordUpdate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspTradingAccountPasswordUpdate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradingAccountPasswordUpdateField* task_data = reinterpret_cast<CThostFtdcTradingAccountPasswordUpdateField*>(task->task_data);
        LOG(INFO)<<"processRspTradingAccountPasswordUpdate->"<<"BrokerID:"<<task_data->BrokerID<<",AccountID:"<<task_data->AccountID;
        LOG(INFO)<<"OldPassword:"<<task_data->OldPassword<<",NewPassword:"<<task_data->NewPassword<<",CurrencyID:"<<task_data->CurrencyID;
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspTradingAccountPasswordUpdate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspUserAuthMethod(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspUserAuthMethodField* task_data = reinterpret_cast<CThostFtdcRspUserAuthMethodField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspUserAuthMethod->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspGenUserCaptcha(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspGenUserCaptchaField* task_data = reinterpret_cast<CThostFtdcRspGenUserCaptchaField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspGenUserCaptcha->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspGenUserText(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspGenUserTextField* task_data = reinterpret_cast<CThostFtdcRspGenUserTextField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspGenUserText->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspOrderInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputOrderField* task_data = reinterpret_cast<CThostFtdcInputOrderField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        if (task_error->ErrorID != 0){ //order insert failed, will not receive order callback, so reset order_complete_
            order_complete_ = true;
            cond_.notify_all();
            LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspOrderInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
        }
        delete task_error;
	}
};

void CTPTraderHandler::processRspParkedOrderInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcParkedOrderField* task_data = reinterpret_cast<CThostFtdcParkedOrderField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspParkedOrderInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspParkedOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcParkedOrderActionField* task_data = reinterpret_cast<CThostFtdcParkedOrderActionField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspParkedOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputOrderActionField* task_data = reinterpret_cast<CThostFtdcInputOrderActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

//TODO remove maxorder volume?
// void CTPTraderHandler::processRspQueryMaxOrderVolume(Task* task)
// {
// 	if (task->task_data)
// 	{
// 		CThostFtdcQueryMaxOrderVolumeField* task_data = (CThostFtdcQueryMaxOrderVolumeField*)task->task_data;
// 		printf("BrokerID = %s\n", (task_data->BrokerID));
// 		printf("InvestorID = %s\n", (task_data->InvestorID));
// 		printf("InstrumentID = %s\n", (task_data->InstrumentID));
// 		printf("Direction = %d\n", task_data->Direction);
// 		printf("OffsetFlag = %d\n", task_data->OffsetFlag);
// 		printf("HedgeFlag = %d\n", task_data->HedgeFlag);
// 		printf("MaxVolume = %d\n", task_data->MaxVolume);
// 		printf("ExchangeID = %s\n", (task_data->ExchangeID));
// 		printf("InvestUnitID = %s\n", (task_data->InvestUnitID));
// 		delete task_data;
// 	}
// 	if (task->task_error)
// 	{
// 		CThostFtdcRspInfoField* task_error = (CThostFtdcRspInfoField*)task->task_error;
// 		printf("ErrorID = %d\n", task_error->ErrorID);
// 		printf("ErrorMsg = %s\n", (task_error->ErrorMsg));
// 		delete task_error;
// 	}
// };

void CTPTraderHandler::processRspSettlementInfoConfirm(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcSettlementInfoConfirmField* task_data = reinterpret_cast<CThostFtdcSettlementInfoConfirmField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspSettlementInfoConfirm->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspRemoveParkedOrder(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRemoveParkedOrderField* task_data = reinterpret_cast<CThostFtdcRemoveParkedOrderField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspRemoveParkedOrder->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspRemoveParkedOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRemoveParkedOrderActionField* task_data = reinterpret_cast<CThostFtdcRemoveParkedOrderActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspRemoveParkedOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspExecOrderInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputExecOrderField* task_data = reinterpret_cast<CThostFtdcInputExecOrderField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspExecOrderInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspExecOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputExecOrderActionField* task_data = reinterpret_cast<CThostFtdcInputExecOrderActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspExecOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspForQuoteInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputForQuoteField* task_data = reinterpret_cast<CThostFtdcInputForQuoteField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspForQuoteInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQuoteInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputQuoteField* task_data = reinterpret_cast<CThostFtdcInputQuoteField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQuoteInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQuoteAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputQuoteActionField* task_data = reinterpret_cast<CThostFtdcInputQuoteActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQuoteAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspBatchOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputBatchOrderActionField* task_data = reinterpret_cast<CThostFtdcInputBatchOrderActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspBatchOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspOptionSelfCloseInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputOptionSelfCloseField* task_data = reinterpret_cast<CThostFtdcInputOptionSelfCloseField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspOptionSelfCloseInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspOptionSelfCloseAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputOptionSelfCloseActionField* task_data = reinterpret_cast<CThostFtdcInputOptionSelfCloseActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspOptionSelfCloseAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspCombActionInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputCombActionField* task_data = reinterpret_cast<CThostFtdcInputCombActionField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspCombActionInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryOrder(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOrderField* task_data = reinterpret_cast<CThostFtdcOrderField*>(task->task_data);
		// FILE *fp = fopen("orders.txt", "a");
		// fwrite(task_data, 1, sizeof(CThostFtdcOrderField), fp);
		// fclose(fp);
		// 
        //FIXME init orders
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryOrder->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
	if(task->task_last)
	{
		LOG(INFO)<<"complete query order";
		this->available_ = true;
		cond_.notify_one();
	}

};

void CTPTraderHandler::processRspQryTrade(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradeField* task_data = reinterpret_cast<CThostFtdcTradeField*>(task->task_data);
		FILE *fp = fopen("trades.txt", "a");
		fwrite(task_data, 1, sizeof(CThostFtdcTradeField), fp);
		fclose(fp);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryTrade->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
    	delete task_error;
	}
	if(task->task_last)
	{
		LOG(INFO)<<"complete query trade";
		this->available_ = true;
		cond_.notify_one();
	}
	
};

void CTPTraderHandler::processRspQryInvestorPosition(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInvestorPositionField* task_data = reinterpret_cast<CThostFtdcInvestorPositionField*>(task->task_data);
		ofstream ofs;
		FileName _position_file_name;
		sprintf(_position_file_name, "cache/%s_position_%s.recordio", this->task_tag.c_str(), getTradingDay().c_str());
		ofs.open(_position_file_name, std::ios::binary);
        recordio::RecordWriter writer(&ofs);
        writer.WriteBuffer(reinterpret_cast<const char*>(task_data), sizeof(CThostFtdcInvestorPositionField));
        writer.Close();
        std::cout<<"????pos,direction=>"<<task_data->InstrumentID<<",direction=>"<<task_data->PosiDirection<<"open vol=>"<<task_data->OpenVolume<<"close vol=>"<<task_data->CloseVolume<<"today position=>"<<task_data->TodayPosition<<"addr=>"<<task_data<<std::endl;
		v_investor_position_fields.push_back(task_data);
		// delete task->task_data; //FIXME new a obj or not delete this
        for (auto it = v_investor_position_fields.begin(); it != v_investor_position_fields.end(); it++){
            std::cout<<(*it)->InstrumentID<<","<<(*it)->OpenVolume<<","<<(*it)->CloseVolume<<std::endl;
        }
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInvestorPosition->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
	if(task->task_last)
	{
		LOG(INFO)<<"complete query position";
		this->available_ = true;
		cond_.notify_one();
	}
};

void CTPTraderHandler::processRspQryTradingAccount(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradingAccountField* task_data = reinterpret_cast<CThostFtdcTradingAccountField*>(task->task_data);
		ofstream ofs;
		FileName _trading_account_file_name;
		sprintf(_trading_account_file_name, "cache/%s_trading_account_%s.recordio", this->task_tag.c_str(), this->getTradingDay().c_str());

		ofs.open(_trading_account_file_name, std::ios::binary);
		recordio::RecordWriter writer(&ofs);
		writer.WriteBuffer(reinterpret_cast<const char*>(task_data), sizeof(CThostFtdcTradingAccountField));
		writer.Close();
		
		// ofs<<task_data->BrokerID <<","
		// << task_data->AccountID <<","
		// << task_data->PreMortgage <<","
		// << task_data->PreCredit <<","
		// << task_data->PreDeposit <<","
		// << task_data->PreBalance <<","
		// << task_data->PreMargin <<","
		// << task_data->InterestBase <<","
		// << task_data->Interest <<","
		// << task_data->Deposit <<","
		// << task_data->Withdraw <<","
		// << task_data->FrozenMargin <<","
		// << task_data->FrozenCash <<","
		// << task_data->FrozenCommission <<","
		// << task_data->CurrMargin <<","
		// << task_data->CashIn <<","
		// << task_data->Commission <<","
		// << task_data->CloseProfit <<","
		// << task_data->PositionProfit <<","
		// << task_data->Balance <<","
		// << task_data->Available <<","
		// << task_data->WithdrawQuota <<","
		// << task_data->Reserve <<","
		// << task_data->TradingDay <<","
		// << task_data->SettlementID <<","
		// << task_data->Credit <<","
		// << task_data->Mortgage <<","
		// << task_data->ExchangeMargin <<","
		// << task_data->DeliveryMargin <<","
		// << task_data->ExchangeDeliveryMargin <<","
		// << task_data->ReserveBalance <<","
		// << task_data->CurrencyID <<","
		// << task_data->PreFundMortgageIn <<","
		// << task_data->PreFundMortgageOut <<","
		// << task_data->FundMortgageIn <<","
		// << task_data->FundMortgageOut <<","
		// << task_data->FundMortgageAvailable <<","
		// << task_data->MortgageableFund <<","
		// << task_data->SpecProductMargin <<","
		// << task_data->SpecProductFrozenMargin <<","
		// << task_data->SpecProductCommission <<","
		// << task_data->SpecProductFrozenCommission <<","
		// << task_data->SpecProductPositionProfit <<","
		// << task_data->SpecProductCloseProfit <<","
		// << task_data->SpecProductPositionProfitByAlg <<","
		// << task_data->SpecProductExchangeMargin <<","
		// << task_data->BizType <<","
		// << task_data->FrozenSwap <<","
		// << task_data->RemainSwap <<std::endl;
		// ofs.close();
		v_trading_account.push_back(task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryTradingAccount->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
	if(task->task_last)
	{
		this->available_ = true;
		cond_.notify_one();
	}
};

void CTPTraderHandler::processRspQryInvestor(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInvestorField* task_data = reinterpret_cast<CThostFtdcInvestorField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInvestor->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryTradingCode(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradingCodeField* task_data = reinterpret_cast<CThostFtdcTradingCodeField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryTradingCode->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInstrumentMarginRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInstrumentMarginRateField* task_data = reinterpret_cast<CThostFtdcInstrumentMarginRateField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInstrumentMarginRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInstrumentCommissionRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInstrumentCommissionRateField* task_data = reinterpret_cast<CThostFtdcInstrumentCommissionRateField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInstrumentCommissionRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryExchange(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExchangeField* task_data = reinterpret_cast<CThostFtdcExchangeField*>(task->task_data);
        LOG(INFO)<<"processRspQryExchange->"<<"ExchangeID:"<<task_data->ExchangeID<<",ExchangeName:"<<task_data->ExchangeName<<",ExchangeProperty:"<<task_data->ExchangeProperty;
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryExchange->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryProduct(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcProductField* task_data = reinterpret_cast<CThostFtdcProductField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryProduct->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInstrument(Task* task)
{
	//ProductClass:,"1":期货单一合约�?"2":期权单一合约
	//ProductID: "cu_o":option,"cu":future
	if (task->task_data)
	{
		CThostFtdcInstrumentField* task_data = reinterpret_cast<CThostFtdcInstrumentField*>(task->task_data);
		ofstream ofs;
		FileName _instrument_file_name;
		sprintf(_instrument_file_name, "cache/%s_instrument_%s.recordio", this->task_tag.c_str(), getTradingDay().c_str());

		ofs.open(_instrument_file_name, std::ios::binary);
		recordio::RecordWriter writer(&ofs);
		writer.WriteBuffer(reinterpret_cast<const char*>(task_data), sizeof(CThostFtdcInstrumentField));
		writer.Close();

		v_instruments.push_back(task_data);
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInstrument->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
	if(task->task_last)
	{
        LOG(INFO)<<"Req Complete for QryInstrument,Reset Available";
		available_ = true;
		cond_.notify_one();
	}
};

void CTPTraderHandler::processRspQryDepthMarketData(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcDepthMarketDataField* task_data = reinterpret_cast<CThostFtdcDepthMarketDataField*>(task->task_data);
		v_depth_market_data.push_back(task_data);
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryDepthMarketData->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
	if(task->task_last)
	{
		LOG(INFO)<<"Req Complete for DepthMarketData , Reset Available";
		available_ = true;
		cond_.notify_one();
	}
};

void CTPTraderHandler::processRspQrySettlementInfo(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcSettlementInfoField* task_data = reinterpret_cast<CThostFtdcSettlementInfoField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQrySettlementInfo->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryTransferBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTransferBankField* task_data = reinterpret_cast<CThostFtdcTransferBankField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryTransferBank->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInvestorPositionDetail(Task* task)
{
	if (task->task_data)
	{

		CThostFtdcInvestorPositionDetailField* task_data = reinterpret_cast<CThostFtdcInvestorPositionDetailField*>(task->task_data);
		ofstream ofs;
		ofs.open("position_details.recordio",std::ios::binary);
		ofs << task_data->InstrumentID << ","
		<< task_data->BrokerID << ","
		<< task_data->InvestorID << ","
		<< task_data->HedgeFlag << ","
		<< task_data->Direction << ","
		<< task_data->OpenDate << ","
		<< task_data->TradeID << ","
		<< task_data->Volume << ","
		<< task_data->OpenPrice << ","
		<< task_data->TradingDay << ","
		<< task_data->SettlementID << ","
		<< task_data->TradeType << ","
		<< task_data->CombInstrumentID << ","
		<< task_data->ExchangeID << ","
		<< task_data->CloseProfitByDate << ","
		<< task_data->CloseProfitByTrade << ","
		<< task_data->PositionProfitByDate << ","
		<< task_data->PositionProfitByTrade << ","
		<< task_data->Margin << ","
		<< task_data->ExchMargin << ","
		<< task_data->MarginRateByMoney << ","
		<< task_data->MarginRateByVolume << ","
		<<  task_data->LastSettlementPrice << ","
		<< task_data->SettlementPrice << ","
		<< task_data->CloseVolume << ","
		<<  task_data->CloseAmount << ","
		<< task_data->TimeFirstVolume << ","
		<< task_data->InvestUnitID <<std::endl;
		ofs.close();
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInvestorPositionDetail->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
	if(task->task_last)
	{
		LOG(INFO)<<"Req Complete for QryInvestorPositionDetail , Reset Available";
		available_ = true;
		cond_.notify_one();
	}
};

void CTPTraderHandler::processRspQryNotice(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcNoticeField* task_data = reinterpret_cast<CThostFtdcNoticeField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryNotice->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQrySettlementInfoConfirm(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcSettlementInfoConfirmField* task_data = reinterpret_cast<CThostFtdcSettlementInfoConfirmField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQrySettlementInfoConfirm->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInvestorPositionCombineDetail(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInvestorPositionCombineDetailField* task_data = reinterpret_cast<CThostFtdcInvestorPositionCombineDetailField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
        LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInvestorPositionCombineDetail->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryCFMMCTradingAccountKey(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcCFMMCTradingAccountKeyField* task_data = reinterpret_cast<CThostFtdcCFMMCTradingAccountKeyField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryCFMMCTradingAccountKey->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryEWarrantOffset(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcEWarrantOffsetField* task_data = reinterpret_cast<CThostFtdcEWarrantOffsetField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryEWarrantOffset->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInvestorProductGroupMargin(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInvestorProductGroupMarginField* task_data = reinterpret_cast<CThostFtdcInvestorProductGroupMarginField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInvestorProductGroupMargin->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryExchangeMarginRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExchangeMarginRateField* task_data = reinterpret_cast<CThostFtdcExchangeMarginRateField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryExchangeMarginRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryExchangeMarginRateAdjust(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExchangeMarginRateAdjustField* task_data = reinterpret_cast<CThostFtdcExchangeMarginRateAdjustField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryExchangeMarginRateAdjust->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryExchangeRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExchangeRateField* task_data = reinterpret_cast<CThostFtdcExchangeRateField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryExchangeRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQrySecAgentACIDMap(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcSecAgentACIDMapField* task_data = reinterpret_cast<CThostFtdcSecAgentACIDMapField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQrySecAgentACIDMap->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;
		delete task_error;
	}
};

void CTPTraderHandler::processRspQryProductExchRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcProductExchRateField* task_data = reinterpret_cast<CThostFtdcProductExchRateField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryProductExchRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryProductGroup(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcProductGroupField* task_data = reinterpret_cast<CThostFtdcProductGroupField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryProductGroup->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryMMInstrumentCommissionRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcMMInstrumentCommissionRateField* task_data = reinterpret_cast<CThostFtdcMMInstrumentCommissionRateField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryMMInstrumentCommissionRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryMMOptionInstrCommRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcMMOptionInstrCommRateField* task_data = reinterpret_cast<CThostFtdcMMOptionInstrCommRateField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryMMOptionInstrCommRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInstrumentOrderCommRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInstrumentOrderCommRateField* task_data = reinterpret_cast<CThostFtdcInstrumentOrderCommRateField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInstrumentOrderCommRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQrySecAgentTradingAccount(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradingAccountField* task_data = reinterpret_cast<CThostFtdcTradingAccountField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQrySecAgentTradingAccount->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQrySecAgentCheckMode(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcSecAgentCheckModeField* task_data = reinterpret_cast<CThostFtdcSecAgentCheckModeField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQrySecAgentCheckMode->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQrySecAgentTradeInfo(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcSecAgentTradeInfoField* task_data = reinterpret_cast<CThostFtdcSecAgentTradeInfoField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQrySecAgentTradeInfo->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryOptionInstrTradeCost(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOptionInstrTradeCostField* task_data = reinterpret_cast<CThostFtdcOptionInstrTradeCostField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryOptionInstrTradeCost->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryOptionInstrCommRate(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOptionInstrCommRateField* task_data = reinterpret_cast<CThostFtdcOptionInstrCommRateField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryOptionInstrCommRate->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryExecOrder(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExecOrderField* task_data = reinterpret_cast<CThostFtdcExecOrderField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryExecOrder->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryForQuote(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcForQuoteField* task_data = reinterpret_cast<CThostFtdcForQuoteField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryForQuote->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryQuote(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcQuoteField* task_data = reinterpret_cast<CThostFtdcQuoteField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryQuote->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryOptionSelfClose(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOptionSelfCloseField* task_data = reinterpret_cast<CThostFtdcOptionSelfCloseField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryOptionSelfClose->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryInvestUnit(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInvestUnitField* task_data = reinterpret_cast<CThostFtdcInvestUnitField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryInvestUnit->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryCombInstrumentGuard(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcCombInstrumentGuardField* task_data = reinterpret_cast<CThostFtdcCombInstrumentGuardField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryCombInstrumentGuard->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryCombAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcCombActionField* task_data = reinterpret_cast<CThostFtdcCombActionField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryCombAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryTransferSerial(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTransferSerialField* task_data = reinterpret_cast<CThostFtdcTransferSerialField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryTransferSerial->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryAccountregister(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcAccountregisterField* task_data = reinterpret_cast<CThostFtdcAccountregisterField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryAccountregister->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspError(Task* task)
{
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspError->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnOrder(Task* task)
{
	if (task->task_data)
	{

        order_available_ = false;
        std::time_t now_time = std::time(nullptr);
		CThostFtdcOrderField* task_data = reinterpret_cast<CThostFtdcOrderField*>(task->task_data);
        std::tm* now = std::localtime(&now_time);
         
        LOG(INFO)<<"Get task data in process rtn order"<<task_data->InstrumentID;
        //if order insert date(calendar date) is the same of the login date(calendar date), and order insert time is later than login time
        int ret_time_cmp = strcmp(task_data->InsertTime, _login_time);
        bool is_1st_equ = task_data->InsertTime[0] == _login_time[0];
        std::string insert_date_str = std::string(task_data->InsertDate);
        bool _is_same_date =  (std::stoi(insert_date_str.substr(6,2))) == now->tm_mday;
        if(!(strcmp(task_data->InsertTime, _login_time) > 0 && _is_same_date )){
            LOG(INFO)<<"[processRtnOrder] Ignore order callback for inserttime=>"<<task_data->InsertTime<<", insert date=>"<<std::stoi(insert_date_str.substr(6,2))<<",login time=>"<<_login_time<<",login date=>"<<now->tm_mday;
            return;
        }
        OrderIDRef* p_orderidref = new OrderIDRef();
        p_orderidref->FrontID = this->front_id;
        p_orderidref->SessionID = this->sessision_id;
        strcpy(p_orderidref->OrderRef, task_data->OrderRef);
        strcpy(p_orderidref->ExchangeID, task_data->ExchangeID);
        strcpy(p_orderidref->TraderID, task_data->TraderID);
        strcpy(p_orderidref->OrderLocalID, task_data->OrderLocalID);
        strcpy(p_orderidref->OrderSysID, task_data->OrderSysID);

        std::string _order_id1 = get_order_id1(p_orderidref);
        std::string _order_id2 = get_order_id2(p_orderidref);

        auto it1 = m_all_orders.find(_order_id1);
        auto it2 = m_all_orders.find(_order_id2);

        LOG(INFO)<<"Order id1=>"<<_order_id1<<"Order id2=>"<<_order_id2;

        //rREMARK temp solution to whether maintain the order(for multi-strategy case); task tag is the product id of product the 
        //current strategy trades. Thus if the instrumentID startswith the product ID(should double check the logic is correct??);
        // then the order list will maintain the order in the first callback; for strategies that trade  same product should be
        // included in the order table and position table since the position limit is grouped by product
        bool trade_product = is_trade_product(this->task_tag.c_str(), task_data->InstrumentID);

        //3rd callback when trade status has updated, come with execution callback
        if (it2 != m_all_orders.end()){//order return from exchange exists,update the order fields, update  order field
            LOG(INFO)<<"3th order callback, id2 exist,id2=>"<<it2->first<<"m_all_orders_size=>"<<m_all_orders.size();
            ptr_OrderField p_orderfield = it2->second;
            p_orderfield->VolumeTotalOriginal = task_data->VolumeTotalOriginal;
            p_orderfield->LimitPrice = task_data->LimitPrice;
            p_orderfield->Direction = task_data->Direction;
            strcpy(p_orderfield->CombHedgeFlag, task_data->CombHedgeFlag);
            p_orderfield->OrderType = task_data->OrderType;
        
            strcpy(p_orderfield->CombOffsetFlag, task_data->CombOffsetFlag);
            p_orderfield->VolumeTotal = task_data->VolumeTotal;
            p_orderfield->OrderStatus = task_data->OrderStatus;
            if(p_orderfield->OrderStatus == THOST_FTDC_OST_Canceled){
                LOG(INFO)<<"[update order table] Remove order when cancel,with order id2=>"<<_order_id2;
                m_all_orders.erase(it2->first);
                order_complete_ = true;
                cond_.notify_all();
            }
        //the 2nd order callback, when the order is accepted by the exchange
        }else if(it1 != m_all_orders.end()){//order return from ctp exists,but from exchange not exist, update order id and order fields
            LOG(INFO)<<"2nd order callback, id1 exist, order accepted by exchange";
            ptr_OrderField p_orderfield = it1->second;
            p_orderfield->p_orderid_ref->FrontID = this->front_id;
            p_orderfield->p_orderid_ref->SessionID = this->sessision_id;
            strcpy(p_orderfield->p_orderid_ref->OrderRef, task_data->OrderRef);
            strcpy(p_orderfield->p_orderid_ref->ExchangeID, task_data->ExchangeID);
            strcpy(p_orderfield->p_orderid_ref->TraderID, task_data->TraderID);
            strcpy(p_orderfield->p_orderid_ref->OrderLocalID, task_data->OrderLocalID);
            strcpy(p_orderfield->p_orderid_ref->OrderSysID, task_data->OrderSysID);

            p_orderfield->VolumeTotalOriginal = task_data->VolumeTotalOriginal;
            p_orderfield->LimitPrice = task_data->LimitPrice;
            p_orderfield->Direction = task_data->Direction;
            strcpy(p_orderfield->CombHedgeFlag, task_data->CombHedgeFlag);
            strcpy(p_orderfield->CombOffsetFlag, task_data->CombOffsetFlag);
            p_orderfield->OrderType = task_data->OrderType;
            p_orderfield->VolumeTraded = task_data->VolumeTraded;
            p_orderfield->VolumeTotal = task_data->VolumeTotal;
            p_orderfield->OrderStatus = task_data->OrderStatus;
            p_orderfield->InsertTime = now_time;
            if(p_orderfield->OrderStatus == THOST_FTDC_OST_Canceled){ //TODO check whether there is other status to handle here, if cancel,the order is removed, and not processed
                LOG(INFO)<<"[update order table] remove order when canceled with order_id1=>"<<_order_id1;
                m_all_orders.erase(_order_id1);
                order_complete_ = true;
                cond_.notify_all();
            }else{
                LOG(INFO)<<"[update order table] insert order with order id2=>"<<_order_id2<<", and remove order with order id1=>"<<_order_id1;
                m_all_orders.insert(std::pair<std::string, ptr_OrderField>(_order_id2, p_orderfield));
                m_all_orders.erase(_order_id1);
                p_orderfield->order_id = _order_id2;
                // std::cout<<"[order report] order id=>"<<p_orderfield->order_id<<",volume traded=>"<<p_orderfield->VolumeTraded<<",volume remained=>"<<p_orderfield->VolumeTotal<<std::endl;
            }
        //the first order callback, when the order is accepted by CTP, but not yet submit to the exchagne
        }else if (trade_product){//orer not exist and the instrument is traded in the strategy(otherwise ignore, no need to maintain order an pos), insert new order
            LOG(INFO)<<"1st order callback, and strategy tade the product";
            ptr_OrderField p_orderfield = new OrderField();
            p_orderfield->p_orderid_ref = new OrderIDRef();
            p_orderfield->p_orderid_ref->FrontID = this->front_id;
            p_orderfield->p_orderid_ref->SessionID = this->sessision_id;
            strcpy(p_orderfield->p_orderid_ref->OrderRef, task_data->OrderRef);
            strcpy(p_orderfield->p_orderid_ref->ExchangeID, task_data->ExchangeID);
            strcpy(p_orderfield->p_orderid_ref->TraderID, task_data->TraderID);
            strcpy(p_orderfield->p_orderid_ref->OrderLocalID, task_data->OrderLocalID);
            strcpy(p_orderfield->p_orderid_ref->OrderSysID, task_data->OrderSysID);
            p_orderfield->VolumeTotalOriginal = task_data->VolumeTotalOriginal;
            p_orderfield->LimitPrice = task_data->LimitPrice;
            p_orderfield->Direction = task_data->Direction;
            strcpy(p_orderfield->CombHedgeFlag, task_data->CombHedgeFlag);
            strcpy(p_orderfield->CombOffsetFlag, task_data->CombOffsetFlag);
            p_orderfield->OrderType = task_data->OrderType;
            p_orderfield->VolumeTraded = task_data->VolumeTraded;
            p_orderfield->VolumeTotal = task_data->VolumeTotal;
            p_orderfield->OrderStatus = task_data->OrderStatus;
            p_orderfield->order_id = _order_id2;
            p_orderfield->InsertTime = now_time;
            LOG(INFO)<<"[update order table] insert order into table with order id1=>"<<_order_id1;
            m_all_orders.insert(std::pair<std::string, ptr_OrderField>(_order_id1, p_orderfield));
            // std::cout<<"[order report] order id=>"<<p_orderfield->order_id<<",volume traded=>"<<p_orderfield->VolumeTraded<<",volume remained=>"<<p_orderfield->VolumeTotal<<std::endl;
        }else{
            LOG(INFO)<<"Order id not exist, and not handle, and return from the process,with trade product=> "<<trade_product;
            return;
        }
        LOG(INFO)<<"*************Order Report******************";
        LOG(INFO)<<"Front ID=>"<<task_data->FrontID;
        LOG(INFO)<<"Session ID=>"<<task_data->SessionID;
        LOG(INFO)<<"Orderref=>"<<task_data->OrderRef;
        LOG(INFO)<<"ExchangeID=>"<<task_data->ExchangeID;
        LOG(INFO)<<"TraderID=>"<<task_data->TraderID;
        LOG(INFO)<<"OrderLocalID=>"<<task_data->OrderLocalID;
        LOG(INFO)<<"OrderSysID=>"<<task_data->OrderSysID;
        LOG(INFO)<<"Order Volume=>"<<task_data->VolumeTotalOriginal;
        LOG(INFO)<<"Order Price=>"<<task_data->LimitPrice;
        LOG(INFO)<<"Order Side [0:buy,1:sell] =>"<<task_data->Direction;
        LOG(INFO)<<"Hedge Flag=>"<<task_data->CombHedgeFlag;
        LOG(INFO)<<"OrderType=>"<<task_data->OrderType;
        LOG(INFO)<<"Volume Traded=>"<<task_data->VolumeTraded;
        LOG(INFO)<<"Volume Ramained=>"<<task_data->VolumeTotal;
        LOG(INFO)<<"OffsetFlag [0:buy,1:sell,3:closetoday,4:close prev] =>"<<task_data->CombOffsetFlag;
        LOG(INFO)<<"OrderStatus [0:all traded,3:in queue,5:canceled,a:unknown] =>"<<task_data->OrderStatus;
        LOG(INFO)<<"OrderSubmissionStatus [0:submitted,3:accepted,4:rejected] =>"<<task_data->OrderSubmitStatus;
        LOG(INFO)<<"StatusMsg=>"<<task_data->StatusMsg;
        LOG(INFO)<<"OrderUpdateTime=>"<<task_data->UpdateTime;
        LOG(INFO)<<"InsertTime=>"<<task_data->InsertTime;
        LOG(INFO)<<"SuspendTime=>"<<task_data->SuspendTime;
        LOG(INFO)<<"*************End Order Report******************";
        if(trade_product && task_data->OrderStatus == THOST_FTDC_OST_Canceled){//成功撤单之后，释放下单控制锁
            order_complete_ = true;
            LOG(INFO)<<"Reset order_complete for cancel order callback, with order complete=>"<<order_complete_;
            cond_.notify_all();
        }
        order_available_ = true;
        cond_.notify_all();
		delete task_data;
	}//end of handle task_data
};

void CTPTraderHandler::processRtnTrade(Task* task)
{
    std::cout<<"in processRtnTrade"<<std::endl;
	if (task->task_data)
	{
        std::cout<<"get processRtnTrade data"<<std::endl;
		CThostFtdcTradeField* task_data = reinterpret_cast<CThostFtdcTradeField*>(task->task_data);
        OrderIDRef* p_orderidref = new OrderIDRef();
        strcpy(p_orderidref->OrderRef, task_data->OrderRef);
        strcpy(p_orderidref->ExchangeID, task_data->ExchangeID);
        strcpy(p_orderidref->TraderID, task_data->TraderID);
        strcpy(p_orderidref->OrderLocalID, task_data->OrderLocalID);
        strcpy(p_orderidref->OrderSysID, task_data->OrderSysID);

        std::string _order_id = get_order_id2(p_orderidref);
        auto it = m_all_orders.find(_order_id);
        if(it != m_all_orders.end()){ //update order field
            ptr_OrderField p_orderfield = it->second;
            p_orderfield->CombOffsetFlag[0] = task_data->OffsetFlag;
            //TODO test the update
            double _udpate_price = (p_orderfield->Price*p_orderfield->VolumeTraded+task_data->Volume*task_data->Price)/(p_orderfield->VolumeTraded+task_data->Volume);
            //FIXME double check trade volume should be added or updated
            p_orderfield->VolumeTraded += task_data->Volume;
            p_orderfield->Price = _udpate_price;
            p_orderfield->Direction = task_data->Direction;
            LOG(INFO)<<"[exe report] order id=>"<<p_orderfield->order_id<<",volume=>"<<p_orderfield->VolumeTraded<<",price=>"<<p_orderfield->Price<<std::endl;
            update_positions(task_data);
            LOG(INFO)<<"*********************Execution Report*************************";
            LOG(INFO)<<"Orderref=>"<<task_data->OrderRef;
            LOG(INFO)<<"ExchangeID=>"<<task_data->ExchangeID;
            LOG(INFO)<<"TraderID=>"<<task_data->TraderID;
            LOG(INFO)<<"OrderLocalID=>"<<task_data->OrderLocalID;
            LOG(INFO)<<"OrderSysID=>"<<task_data->OrderSysID;
            LOG(INFO)<<"Offset Flag [0:open,1:close,3:closetoday] =>"<<task_data->OffsetFlag;
            LOG(INFO)<<"Trade Volume=>"<<task_data->Volume;
            LOG(INFO)<<"Trade Price=>"<<task_data->Price;
            LOG(INFO)<<"Trade Direction(0:buy,1:sell)=>"<<task_data->Direction;
            LOG(INFO)<<"Trade Time=>"<<task_data->TradeTime;
            LOG(INFO)<<"order vol traded=>"<<p_orderfield->VolumeTraded;
            LOG(INFO)<<"order price=>"<<p_orderfield->Price;
            LOG(INFO)<<"order total vol=>"<<p_orderfield->VolumeTotalOriginal;
            LOG(INFO)<<"order status(0:all traded)=>"<<p_orderfield->OrderStatus;
            LOG(INFO)<<"*********************End Execution Report*************************";
            if((p_orderfield->VolumeTraded == p_orderfield->VolumeTotalOriginal && p_orderfield->OrderStatus==THOST_FTDC_OST_AllTraded)){ 
                // TODO reset order_complete, move to rtn_trade when trade volume confirm
                LOG(INFO)<<"[update order table] remove order when complete with order id2=>"<<it->first;
                m_all_orders.erase(it->first);
                order_complete_ = true;
                cond_.notify_all();
                LOG(INFO)<<"[processRtnTrade] order completed  with order_id=>"<<it->first<<",status [0,tradded,5:canceled] =>"<<p_orderfield->OrderStatus;
            }
        }
        // std::cout<<"before delete in processRtnTrade"<<std::endl;
		delete task_data;
        // std::cout<<"after delete in processRtnTrade"<<std::endl;
	}
};

void CTPTraderHandler::processErrRtnOrderInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputOrderField* task_data = reinterpret_cast<CThostFtdcInputOrderField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnOrderInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOrderActionField* task_data = reinterpret_cast<CThostFtdcOrderActionField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnInstrumentStatus(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInstrumentStatusField* task_data = reinterpret_cast<CThostFtdcInstrumentStatusField*>(task->task_data);

		delete task_data;
	}
};

void CTPTraderHandler::processRtnBulletin(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcBulletinField* task_data = reinterpret_cast<CThostFtdcBulletinField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnTradingNotice(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradingNoticeInfoField* task_data = reinterpret_cast<CThostFtdcTradingNoticeInfoField*>(task->task_data);

		delete task_data;
	}
};

void CTPTraderHandler::processRtnErrorConditionalOrder(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcErrorConditionalOrderField* task_data = reinterpret_cast<CThostFtdcErrorConditionalOrderField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnExecOrder(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExecOrderField* task_data = reinterpret_cast<CThostFtdcExecOrderField*>(task->task_data);

		delete task_data;
	}
};

void CTPTraderHandler::processErrRtnExecOrderInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputExecOrderField* task_data = reinterpret_cast<CThostFtdcInputExecOrderField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnExecOrderInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnExecOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcExecOrderActionField* task_data = reinterpret_cast<CThostFtdcExecOrderActionField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnExecOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnForQuoteInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputForQuoteField* task_data = reinterpret_cast<CThostFtdcInputForQuoteField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnForQuoteInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnQuote(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcQuoteField* task_data = reinterpret_cast<CThostFtdcQuoteField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processErrRtnQuoteInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputQuoteField* task_data = reinterpret_cast<CThostFtdcInputQuoteField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnQuoteInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnQuoteAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcQuoteActionField* task_data = reinterpret_cast<CThostFtdcQuoteActionField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnQuoteAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnForQuoteRsp(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcForQuoteRspField* task_data = reinterpret_cast<CThostFtdcForQuoteRspField*>(task->task_data);

		delete task_data;
	}
};

void CTPTraderHandler::processRtnCFMMCTradingAccountToken(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcCFMMCTradingAccountTokenField* task_data = reinterpret_cast<CThostFtdcCFMMCTradingAccountTokenField*>(task->task_data);

		delete task_data;
	}
};

void CTPTraderHandler::processErrRtnBatchOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcBatchOrderActionField* task_data = reinterpret_cast<CThostFtdcBatchOrderActionField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnBatchOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnOptionSelfClose(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOptionSelfCloseField* task_data = reinterpret_cast<CThostFtdcOptionSelfCloseField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processErrRtnOptionSelfCloseInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputOptionSelfCloseField* task_data = reinterpret_cast<CThostFtdcInputOptionSelfCloseField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnOptionSelfCloseInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnOptionSelfCloseAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOptionSelfCloseActionField* task_data = reinterpret_cast<CThostFtdcOptionSelfCloseActionField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnOptionSelfCloseAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnCombAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcCombActionField* task_data = reinterpret_cast<CThostFtdcCombActionField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processErrRtnCombActionInsert(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcInputCombActionField* task_data = reinterpret_cast<CThostFtdcInputCombActionField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnCombActionInsert->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryContractBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcContractBankField* task_data = reinterpret_cast<CThostFtdcContractBankField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryContractBank->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryParkedOrder(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcParkedOrderField* task_data = reinterpret_cast<CThostFtdcParkedOrderField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryParkedOrder->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryParkedOrderAction(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcParkedOrderActionField* task_data = reinterpret_cast<CThostFtdcParkedOrderActionField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryParkedOrderAction->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryTradingNotice(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcTradingNoticeField* task_data = reinterpret_cast<CThostFtdcTradingNoticeField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryTradingNotice->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryBrokerTradingParams(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcBrokerTradingParamsField* task_data = reinterpret_cast<CThostFtdcBrokerTradingParamsField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryBrokerTradingParams->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQryBrokerTradingAlgos(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcBrokerTradingAlgosField* task_data = reinterpret_cast<CThostFtdcBrokerTradingAlgosField*>(task->task_data);

		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQryBrokerTradingAlgos->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQueryCFMMCTradingAccountToken(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcQueryCFMMCTradingAccountTokenField* task_data = reinterpret_cast<CThostFtdcQueryCFMMCTradingAccountTokenField*>(task->task_data);
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQueryCFMMCTradingAccountToken->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnFromBankToFutureByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspTransferField* task_data = reinterpret_cast<CThostFtdcRspTransferField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnFromFutureToBankByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspTransferField* task_data = reinterpret_cast<CThostFtdcRspTransferField*>(task->task_data);
	
		delete task_data;
	}
};

void CTPTraderHandler::processRtnRepealFromBankToFutureByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspRepealField* task_data = reinterpret_cast<CThostFtdcRspRepealField*>(task->task_data);
	
		delete task_data;
	}
};

void CTPTraderHandler::processRtnRepealFromFutureToBankByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspRepealField* task_data = reinterpret_cast<CThostFtdcRspRepealField*>(task->task_data);
	
		delete task_data;
	}
};

void CTPTraderHandler::processRtnFromBankToFutureByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspTransferField* task_data = reinterpret_cast<CThostFtdcRspTransferField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnFromFutureToBankByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspTransferField* task_data = reinterpret_cast<CThostFtdcRspTransferField*>(task->task_data);
	
		delete task_data;
	}
};

void CTPTraderHandler::processRtnRepealFromBankToFutureByFutureManual(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspRepealField* task_data = reinterpret_cast<CThostFtdcRspRepealField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnRepealFromFutureToBankByFutureManual(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspRepealField* task_data = reinterpret_cast<CThostFtdcRspRepealField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnQueryBankBalanceByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcNotifyQueryAccountField* task_data = reinterpret_cast<CThostFtdcNotifyQueryAccountField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processErrRtnBankToFutureByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqTransferField* task_data = reinterpret_cast<CThostFtdcReqTransferField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnBankToFutureByFuture->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnFutureToBankByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqTransferField* task_data = reinterpret_cast<CThostFtdcReqTransferField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnFutureToBankByFuture->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnRepealBankToFutureByFutureManual(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqRepealField* task_data = reinterpret_cast<CThostFtdcReqRepealField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnRepealBankToFutureByFutureManual->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnRepealFutureToBankByFutureManual(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqRepealField* task_data = reinterpret_cast<CThostFtdcReqRepealField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnRepealFutureToBankByFutureManual->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processErrRtnQueryBankBalanceByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqQueryAccountField* task_data = reinterpret_cast<CThostFtdcReqQueryAccountField*>(task->task_data);
		
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processErrRtnQueryBankBalanceByFuture->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnRepealFromBankToFutureByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspRepealField* task_data = reinterpret_cast<CThostFtdcRspRepealField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRtnRepealFromFutureToBankByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcRspRepealField* task_data = reinterpret_cast<CThostFtdcRspRepealField*>(task->task_data);
		
		delete task_data;
	}
};

void CTPTraderHandler::processRspFromBankToFutureByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqTransferField* task_data = reinterpret_cast<CThostFtdcReqTransferField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspFromBankToFutureByFuture->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspFromFutureToBankByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqTransferField* task_data = reinterpret_cast<CThostFtdcReqTransferField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspFromFutureToBankByFuture->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRspQueryBankAccountMoneyByFuture(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcReqQueryAccountField* task_data = reinterpret_cast<CThostFtdcReqQueryAccountField*>(task->task_data);
	
		delete task_data;
	}
	if (task->task_error)
	{
		CThostFtdcRspInfoField* task_error = reinterpret_cast<CThostFtdcRspInfoField*>(task->task_error);
		LOG_IF(ERROR, task_error->ErrorID!=0)<<"Error processRspQueryBankAccountMoneyByFuture->"<<task_error->ErrorID<<","<<task_error->ErrorMsg;

		delete task_error;
	}
};

void CTPTraderHandler::processRtnOpenAccountByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcOpenAccountField* task_data = reinterpret_cast<CThostFtdcOpenAccountField*>(task->task_data);
	
		delete task_data;
	}
};

void CTPTraderHandler::processRtnCancelAccountByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcCancelAccountField* task_data = reinterpret_cast<CThostFtdcCancelAccountField*>(task->task_data);
	
		delete task_data;
	}
};

void CTPTraderHandler::processRtnChangeAccountByBank(Task* task)
{
	if (task->task_data)
	{
		CThostFtdcChangeAccountField* task_data = reinterpret_cast<CThostFtdcChangeAccountField*>(task->task_data);

		delete task_data;
	}
};

void CTPTraderHandler::processTask()
{
    try
    {
        bool _terminate = false;
        while (!_terminate)
        {
            Task task = this->_task_queue.pop();
            switch (task.task_name)
            {
            
            case ONRSPTERMINATE://when get the terminate signal, it will break from the thead
            {
                _terminate = true;
                break;
            }
            case ONFRONTCONNECTED:
            {
                this->processFrontConnected(&task);
                break;
            }


            case ONFRONTDISCONNECTED:
            {
                this->processFrontDisconnected(&task);
                break;
            }

            case ONHEARTBEATWARNING:
            {
                this->processHeartBeatWarning(&task);
                break;
            }

            case ONRSPAUTHENTICATE:
            {
                this->processRspAuthenticate(&task);
                break;
            }

            case ONRSPUSERLOGIN:
            {
                this->processRspUserLogin(&task);
                break;
            }

            case ONRSPUSERLOGOUT:
            {
                this->processRspUserLogout(&task);
                break;
            }

            case ONRSPUSERPASSWORDUPDATE:
            {
                this->processRspUserPasswordUpdate(&task);
                break;
            }

            case ONRSPTRADINGACCOUNTPASSWORDUPDATE:
            {
                this->processRspTradingAccountPasswordUpdate(&task);
                break;
            }

            case ONRSPUSERAUTHMETHOD:
            {
                this->processRspUserAuthMethod(&task);
                break;
            }

            case ONRSPGENUSERCAPTCHA:
            {
                this->processRspGenUserCaptcha(&task);
                break;
            }

            case ONRSPGENUSERTEXT:
            {
                this->processRspGenUserText(&task);
                break;
            }
			//报单请求
            case ONRSPORDERINSERT:
            {
                this->processRspOrderInsert(&task);
                break;
            }
			//预埋单录入请�?
            case ONRSPPARKEDORDERINSERT:
            {
                this->processRspParkedOrderInsert(&task);
                break;
            }
			//预埋撤单
            case ONRSPPARKEDORDERACTION:
            {
                this->processRspParkedOrderAction(&task);
                break;
            }
			//报单操作请求
            case ONRSPORDERACTION:
            {
                this->processRspOrderAction(&task);
                break;
            }

            // case ONRSPQUERYMAXORDERVOLUME:
            // {
            //     this->processRspQueryMaxOrderVolume(&task);
            //     break;
            // }
			//结算结果确认
            case ONRSPSETTLEMENTINFOCONFIRM:
            {
                this->processRspSettlementInfoConfirm(&task);
                break;
            }
			//删除预埋�?
            case ONRSPREMOVEPARKEDORDER:
            {
                this->processRspRemoveParkedOrder(&task);
                break;
            }
			//删除预埋撤单
            case ONRSPREMOVEPARKEDORDERACTION:
            {
                this->processRspRemoveParkedOrderAction(&task);
                break;
            }

            case ONRSPEXECORDERINSERT:
            {
                this->processRspExecOrderInsert(&task);
                break;
            }

            case ONRSPEXECORDERACTION:
            {
                this->processRspExecOrderAction(&task);
                break;
            }

            case ONRSPFORQUOTEINSERT:
            {
                this->processRspForQuoteInsert(&task);
                break;
            }

            case ONRSPQUOTEINSERT:
            {
                this->processRspQuoteInsert(&task);
                break;
            }

            case ONRSPQUOTEACTION:
            {
                this->processRspQuoteAction(&task);
                break;
            }

            case ONRSPBATCHORDERACTION:
            {
                this->processRspBatchOrderAction(&task);
                break;
            }

            case ONRSPOPTIONSELFCLOSEINSERT:
            {
                this->processRspOptionSelfCloseInsert(&task);
                break;
            }

            case ONRSPOPTIONSELFCLOSEACTION:
            {
                this->processRspOptionSelfCloseAction(&task);
                break;
            }

            case ONRSPCOMBACTIONINSERT:
            {
                this->processRspCombActionInsert(&task);
                break;
            }
			//查询报单
            case ONRSPQRYORDER:
            {
                this->processRspQryOrder(&task);
                break;
            }
			//查询成交
            case ONRSPQRYTRADE:
            {
                this->processRspQryTrade(&task);
                break;
            }
			//查询持仓
            case ONRSPQRYINVESTORPOSITION:
            {
                this->processRspQryInvestorPosition(&task);
                break;
            }
			//查询资金账户
            case ONRSPQRYTRADINGACCOUNT:
            {
                this->processRspQryTradingAccount(&task);
                break;
            }

            case ONRSPQRYINVESTOR:
            {
                this->processRspQryInvestor(&task);
                break;
            }

            case ONRSPQRYTRADINGCODE:
            {
                this->processRspQryTradingCode(&task);
                break;
            }
			//查询合约保证金率
            case ONRSPQRYINSTRUMENTMARGINRATE:
            {
                this->processRspQryInstrumentMarginRate(&task);
                break;
            }
			//查询合约手续费率
            case ONRSPQRYINSTRUMENTCOMMISSIONRATE:
            {
                this->processRspQryInstrumentCommissionRate(&task);
                break;
            }

            case ONRSPQRYEXCHANGE:
            {
                this->processRspQryExchange(&task);
                break;
            }
			//查询产品
            case ONRSPQRYPRODUCT:
            {
                this->processRspQryProduct(&task);
                break;
            }
			//查询合约
            case ONRSPQRYINSTRUMENT:
            {
                this->processRspQryInstrument(&task);
                break;
            }

            case ONRSPQRYDEPTHMARKETDATA:
            {
                this->processRspQryDepthMarketData(&task);
                break;
            }
			//查询结算结果
            case ONRSPQRYSETTLEMENTINFO:
            {
                this->processRspQrySettlementInfo(&task);
                break;
            }

            case ONRSPQRYTRANSFERBANK:
            {
                this->processRspQryTransferBank(&task);
                break;
            }
			//投资者持仓明�?
            case ONRSPQRYINVESTORPOSITIONDETAIL:
            {
                this->processRspQryInvestorPositionDetail(&task);
                break;
            }

            case ONRSPQRYNOTICE:
            {
                this->processRspQryNotice(&task);
                break;
            }

            case ONRSPQRYSETTLEMENTINFOCONFIRM:
            {
                this->processRspQrySettlementInfoConfirm(&task);
                break;
            }

            case ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL:
            {
                this->processRspQryInvestorPositionCombineDetail(&task);
                break;
            }

            case ONRSPQRYCFMMCTRADINGACCOUNTKEY:
            {
                this->processRspQryCFMMCTradingAccountKey(&task);
                break;
            }

            case ONRSPQRYEWARRANTOFFSET:
            {
                this->processRspQryEWarrantOffset(&task);
                break;
            }

            case ONRSPQRYINVESTORPRODUCTGROUPMARGIN:
            {
                this->processRspQryInvestorProductGroupMargin(&task);
                break;
            }

            case ONRSPQRYEXCHANGEMARGINRATE:
            {
                this->processRspQryExchangeMarginRate(&task);
                break;
            }

            case ONRSPQRYEXCHANGEMARGINRATEADJUST:
            {
                this->processRspQryExchangeMarginRateAdjust(&task);
                break;
            }

            case ONRSPQRYEXCHANGERATE:
            {
                this->processRspQryExchangeRate(&task);
                break;
            }

            case ONRSPQRYSECAGENTACIDMAP:
            {
                this->processRspQrySecAgentACIDMap(&task);
                break;
            }

            case ONRSPQRYPRODUCTEXCHRATE:
            {
                this->processRspQryProductExchRate(&task);
                break;
            }

            case ONRSPQRYPRODUCTGROUP:
            {
                this->processRspQryProductGroup(&task);
                break;
            }

            case ONRSPQRYMMINSTRUMENTCOMMISSIONRATE:
            {
                this->processRspQryMMInstrumentCommissionRate(&task);
                break;
            }

            case ONRSPQRYMMOPTIONINSTRCOMMRATE:
            {
                this->processRspQryMMOptionInstrCommRate(&task);
                break;
            }

            case ONRSPQRYINSTRUMENTORDERCOMMRATE:
            {
                this->processRspQryInstrumentOrderCommRate(&task);
                break;
            }
			//查询资金账户
            case ONRSPQRYSECAGENTTRADINGACCOUNT:
            {
                this->processRspQrySecAgentTradingAccount(&task);
                break;
            }

            case ONRSPQRYSECAGENTCHECKMODE:
            {
                this->processRspQrySecAgentCheckMode(&task);
                break;
            }

            case ONRSPQRYSECAGENTTRADEINFO:
            {
                this->processRspQrySecAgentTradeInfo(&task);
                break;
            }

            case ONRSPQRYOPTIONINSTRTRADECOST:
            {
                this->processRspQryOptionInstrTradeCost(&task);
                break;
            }

            case ONRSPQRYOPTIONINSTRCOMMRATE:
            {
                this->processRspQryOptionInstrCommRate(&task);
                break;
            }

            case ONRSPQRYEXECORDER:
            {
                this->processRspQryExecOrder(&task);
                break;
            }
			//查询询价
            case ONRSPQRYFORQUOTE:
            {
                this->processRspQryForQuote(&task);
                break;
            }
			//查询报价
            case ONRSPQRYQUOTE:
            {
                this->processRspQryQuote(&task);
                break;
            }

            case ONRSPQRYOPTIONSELFCLOSE:
            {
                this->processRspQryOptionSelfClose(&task);
                break;
            }

            case ONRSPQRYINVESTUNIT:
            {
                this->processRspQryInvestUnit(&task);
                break;
            }

            case ONRSPQRYCOMBINSTRUMENTGUARD:
            {
                this->processRspQryCombInstrumentGuard(&task);
                break;
            }

            case ONRSPQRYCOMBACTION:
            {
                this->processRspQryCombAction(&task);
                break;
            }

            case ONRSPQRYTRANSFERSERIAL:
            {
                this->processRspQryTransferSerial(&task);
                break;
            }

            case ONRSPQRYACCOUNTREGISTER:
            {
                this->processRspQryAccountregister(&task);
                break;
            }

            case ONRSPERROR:
            {
                this->processRspError(&task);
                break;
            }

            case ONRTNORDER:
            {
                this->processRtnOrder(&task);
                break;
            }

            case ONRTNTRADE:
            {
                this->processRtnTrade(&task);
                break;
            }

            case ONERRRTNORDERINSERT:
            {
                this->processErrRtnOrderInsert(&task);
                break;
            }

            case ONERRRTNORDERACTION:
            {
                this->processErrRtnOrderAction(&task);
                break;
            }

            case ONRTNINSTRUMENTSTATUS:
            {
                this->processRtnInstrumentStatus(&task);
                break;
            }

            case ONRTNBULLETIN:
            {
                this->processRtnBulletin(&task);
                break;
            }

            case ONRTNTRADINGNOTICE:
            {
                this->processRtnTradingNotice(&task);
                break;
            }

            case ONRTNERRORCONDITIONALORDER:
            {
                this->processRtnErrorConditionalOrder(&task);
                break;
            }

            case ONRTNEXECORDER:
            {
                this->processRtnExecOrder(&task);
                break;
            }

            case ONERRRTNEXECORDERINSERT:
            {
                this->processErrRtnExecOrderInsert(&task);
                break;
            }

            case ONERRRTNEXECORDERACTION:
            {
                this->processErrRtnExecOrderAction(&task);
                break;
            }

            case ONERRRTNFORQUOTEINSERT:
            {
                this->processErrRtnForQuoteInsert(&task);
                break;
            }

            case ONRTNQUOTE:
            {
                this->processRtnQuote(&task);
                break;
            }

            case ONERRRTNQUOTEINSERT:
            {
                this->processErrRtnQuoteInsert(&task);
                break;
            }

            case ONERRRTNQUOTEACTION:
            {
                this->processErrRtnQuoteAction(&task);
                break;
            }

            case ONRTNFORQUOTERSP:
            {
                this->processRtnForQuoteRsp(&task);
                break;
            }

            case ONRTNCFMMCTRADINGACCOUNTTOKEN:
            {
                this->processRtnCFMMCTradingAccountToken(&task);
                break;
            }

            case ONERRRTNBATCHORDERACTION:
            {
                this->processErrRtnBatchOrderAction(&task);
                break;
            }

            case ONRTNOPTIONSELFCLOSE:
            {
                this->processRtnOptionSelfClose(&task);
                break;
            }

            case ONERRRTNOPTIONSELFCLOSEINSERT:
            {
                this->processErrRtnOptionSelfCloseInsert(&task);
                break;
            }

            case ONERRRTNOPTIONSELFCLOSEACTION:
            {
                this->processErrRtnOptionSelfCloseAction(&task);
                break;
            }

            case ONRTNCOMBACTION:
            {
                this->processRtnCombAction(&task);
                break;
            }

            case ONERRRTNCOMBACTIONINSERT:
            {
                this->processErrRtnCombActionInsert(&task);
                break;
            }

            case ONRSPQRYCONTRACTBANK:
            {
                this->processRspQryContractBank(&task);
                break;
            }
			//查询预埋�?
            case ONRSPQRYPARKEDORDER:
            {
                this->processRspQryParkedOrder(&task);
                break;
            }
			//查询预埋撤单
            case ONRSPQRYPARKEDORDERACTION:
            {
                this->processRspQryParkedOrderAction(&task);
                break;
            }
			//查询交易通知
            case ONRSPQRYTRADINGNOTICE:
            {
                this->processRspQryTradingNotice(&task);
                break;
            }

            case ONRSPQRYBROKERTRADINGPARAMS:
            {
                this->processRspQryBrokerTradingParams(&task);
                break;
            }

            case ONRSPQRYBROKERTRADINGALGOS:
            {
                this->processRspQryBrokerTradingAlgos(&task);
                break;
            }

            case ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN:
            {
                this->processRspQueryCFMMCTradingAccountToken(&task);
                break;
            }

            case ONRTNFROMBANKTOFUTUREBYBANK:
            {
                this->processRtnFromBankToFutureByBank(&task);
                break;
            }

            case ONRTNFROMFUTURETOBANKBYBANK:
            {
                this->processRtnFromFutureToBankByBank(&task);
                break;
            }

            case ONRTNREPEALFROMBANKTOFUTUREBYBANK:
            {
                this->processRtnRepealFromBankToFutureByBank(&task);
                break;
            }

            case ONRTNREPEALFROMFUTURETOBANKBYBANK:
            {
                this->processRtnRepealFromFutureToBankByBank(&task);
                break;
            }

            case ONRTNFROMBANKTOFUTUREBYFUTURE:
            {
                this->processRtnFromBankToFutureByFuture(&task);
                break;
            }

            case ONRTNFROMFUTURETOBANKBYFUTURE:
            {
                this->processRtnFromFutureToBankByFuture(&task);
                break;
            }

            case ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL:
            {
                this->processRtnRepealFromBankToFutureByFutureManual(&task);
                break;
            }

            case ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL:
            {
                this->processRtnRepealFromFutureToBankByFutureManual(&task);
                break;
            }

            case ONRTNQUERYBANKBALANCEBYFUTURE:
            {
                this->processRtnQueryBankBalanceByFuture(&task);
                break;
            }

            case ONERRRTNBANKTOFUTUREBYFUTURE:
            {
                this->processErrRtnBankToFutureByFuture(&task);
                break;
            }

            case ONERRRTNFUTURETOBANKBYFUTURE:
            {
                this->processErrRtnFutureToBankByFuture(&task);
                break;
            }

            case ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL:
            {
                this->processErrRtnRepealBankToFutureByFutureManual(&task);
                break;
            }

            case ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL:
            {
                this->processErrRtnRepealFutureToBankByFutureManual(&task);
                break;
            }

            case ONERRRTNQUERYBANKBALANCEBYFUTURE:
            {
                this->processErrRtnQueryBankBalanceByFuture(&task);
                break;
            }

            case ONRTNREPEALFROMBANKTOFUTUREBYFUTURE:
            {
                this->processRtnRepealFromBankToFutureByFuture(&task);
                break;
            }

            case ONRTNREPEALFROMFUTURETOBANKBYFUTURE:
            {
                this->processRtnRepealFromFutureToBankByFuture(&task);
                break;
            }

            case ONRSPFROMBANKTOFUTUREBYFUTURE:
            {
                this->processRspFromBankToFutureByFuture(&task);
                break;
            }

            case ONRSPFROMFUTURETOBANKBYFUTURE:
            {
                this->processRspFromFutureToBankByFuture(&task);
                break;
            }

            case ONRSPQUERYBANKACCOUNTMONEYBYFUTURE:
            {
                this->processRspQueryBankAccountMoneyByFuture(&task);
                break;
            }

            case ONRTNOPENACCOUNTBYBANK:
            {
                this->processRtnOpenAccountByBank(&task);
                break;
            }

            case ONRTNCANCELACCOUNTBYBANK:
            {
                this->processRtnCancelAccountByBank(&task);
                break;
            }

            case ONRTNCHANGEACCOUNTBYBANK:
            {
                this->processRtnChangeAccountByBank(&task);
                break;
            }
            }
        if(_terminate){
            LOG(INFO)<<"[processTask] break the processTask while and thread";
            break;//break while, end thread
        }
        }
    }
    catch (const TerminatedError &)
    {
    }
}

bool CTPTraderHandler::CreateFtdcTraderApi(const char *pszFlowPath)
{
    _api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
    if (nullptr == _api)
        return false;
    this->_api->RegisterSpi(this);
    return true;
}

void CTPTraderHandler::init(const std::string& task_tag, const std::string& broker_id, const std::string& user_id)
{

    LOG(INFO)<<"CTPTraderHandler Init with task_tag:"<<task_tag;
    this->_active = true;
    this->_task_thread = thread(&CTPTraderHandler::processTask, this);
    // SubscribePrivateTopic(THOST_TERT_RESUME);
    // SubscribePublicTopic(THOST_TERT_RESUME);
    SubscribePrivateTopic(THOST_TERT_RESTART);
    SubscribePublicTopic(THOST_TERT_RESTART);
    this->task_tag = task_tag;
    this->broker_id = broker_id;
    this->user_id = user_id;
    this->_api->Init();
	LOG(INFO)<<"API VERSION:"<<this->_api->GetApiVersion()<<"wait for front connected api call";
	//TODO check 
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return connected_; //调用了onfrontconnected时候才会将ready_设置为true，没有调用onfrontconnected,就会一直wait.
	}); 
};

void CTPTraderHandler::release()
{
    this->_api->Release();
	connected_ = false;
};

// int CTPTraderHandler::join()
// {
    // LOG(INFO)<<"[join] before join in trade handler";
    // int i = this->_api->Join();
    // LOG(INFO)<<"[join] after join in trade handler";
    // return i;
// };

int CTPTraderHandler::exit()
{
    this->_active = false;

	CThostFtdcUserLogoutField reqUserLogout = {0};
    strcpy(reqUserLogout.BrokerID, this->broker_id.c_str());
    strcpy(reqUserLogout.UserID, this->user_id.c_str());

    this->ReqUserLogout(&reqUserLogout, nRequestID++);

    //TODO improve this, leave time buffer to handle logout callback
    sleep(1);
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
	    return available_;
    }); 	
    LOG(INFO)<<"[exit] complte logout";
    //when strategy ends, it will push a ternminate signal to ctp, then it will breaks in the proscess task, thus terminate the task thread
    Task task = Task();
    task.task_name = ONRSPTERMINATE;
    task.task_id = nRequestID ++;
    this->_task_queue.push(task);
    
    this->_task_thread.join();
    this->_task_queue.terminate();
    LOG(INFO)<<"[exit] after join task thread and terminate task queue";
    this->_api->RegisterSpi(NULL);
    LOG(INFO)<<"[exit] after spi register null";
	LOG(INFO)<<"[exit] before join in trade handler";
    int i = this->_api->Join();
    LOG(INFO)<<"[exit] after join in trade handler";
	this->release();
    this->_api = NULL;
    LOG(INFO)<<"[exit] after trade handler release, start to delete variables";
    //TODO to be added
	for(auto it = v_depth_market_data.begin(); it != v_depth_market_data.end(); ++it)
	{
		delete (*it);
	}
	for(auto it = v_instruments.begin(); it!=v_instruments.end();++it)
	{
		delete(*it);
	}
	for(auto it=v_trading_account.begin(); it!=v_trading_account.end(); ++it)
	{
		delete (*it);
	}
	for(auto it=v_investor_position_fields.begin(); it!=v_investor_position_fields.end(); ++it)
	{
		delete (*it);
	}
    LOG(INFO)<<"[exit] complte exit";
    return 0;
};

string CTPTraderHandler::getTradingDay()
{
    string day = this->_api->GetTradingDay();
    return day;
};

void CTPTraderHandler::RegisterFront(char *pszFrontAddress)
{
    LOG(INFO)<<"In CTP RegisterFront...";
    return _api->RegisterFront(pszFrontAddress);
}
int CTPTraderHandler::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID)
{
    int ret =  _api->ReqAuthenticate(pReqAuthenticateField, nRequestID);
    LOG(INFO)<<"Return req authenticate:"<<ret;
    return ret;
}

void CTPTraderHandler::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
{
    return _api->SubscribePrivateTopic(nResumeType);
}

void CTPTraderHandler::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
{
    return _api->SubscribePublicTopic(nResumeType);
}

int CTPTraderHandler::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
{
	int ret = _api->ReqUserLogin(pReqUserLoginField, nRequestID);
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_;
	}); 
	return ret;
}

int CTPTraderHandler::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	return _api->ReqUserLogout(pUserLogout, nRequestID);
}	

int CTPTraderHandler::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, int nRequestID)
{
	return _api->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}

int CTPTraderHandler::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID)
{
	return _api->ReqQryProduct(pQryProduct, nRequestID);
}

int CTPTraderHandler::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	this->available_ = false;
    LOG(INFO)<<"Send reqqry instrument:"<<pQryInstrument->InstrumentID;
    sleep(5);//FIXME double check this
	int ret = _api->ReqQryInstrument(pQryInstrument, nRequestID); 
    LOG(INFO)<<"ret for send reqqry instruemnt:"<<ret;
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&available_;
	}); 	
	return ret;
}

int CTPTraderHandler::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID)
{
	this->available_ = false;
	LOG(INFO)<<"send request data in reqqrydepthmktdata in traderhandler: "<<pQryDepthMarketData->InstrumentID;
	int ret = _api->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID); 
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&available_;
	}); 	
	return ret;
}

int CTPTraderHandler::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID)
{
	return _api->ReqOrderInsert(pInputOrder, nRequestID);
}

int CTPTraderHandler::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrder, int nRequestID){
    return _api->ReqOrderAction(pInputOrder, nRequestID);
}

//TODO to be commpleted
void CTPTraderHandler::ReqQryMainContract(vector<std::string> productID, int nRequestID)
{
	for (auto iter = productID.begin(); iter != productID.end(); iter++)
	{
		CThostFtdcQryInstrumentField pQryInstrument = {0};
    	std::strcpy(pQryInstrument.InstrumentID, (*iter).c_str());

    	this->ReqQryInstrument(&pQryInstrument, nRequestID++);
	}

}


///请求查询报单
int CTPTraderHandler::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID)
{
	this->available_ = false;
	int ret = _api->ReqQryOrder(pQryOrder, nRequestID);
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&this->available_;
	}); 
	return ret;

	 
}

///请求查询成交
int CTPTraderHandler::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID)
{
	this->available_ = false;
	int ret = _api->ReqQryTrade(pQryTrade, nRequestID);
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&this->available_;
	}); 
	return ret;
}

///请求查询投资者持�?
int CTPTraderHandler::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	this->available_ = false;
	int ret =  _api->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
	LOG(INFO)<<"sent req for inverstor position, ret is:"<<ret;
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&this->available_;
	}); 
	return ret;
}

///请求查询资金账户
int CTPTraderHandler::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	this->available_ = false;
	int ret = _api->ReqQryTradingAccount(pQryTradingAccount, nRequestID++);
	LOG(INFO)<<"sent req for trading account, ret is:"<<ret;
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&this->available_;
	}); 
	return ret;
}

//请求查询投资者持仓明�?
int CTPTraderHandler::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
	this->available_ = false;
	int ret = _api->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail,nRequestID++);
	LOG(INFO)<<"sent req for investor position detail, ret is:"<<ret;
	unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return login_&this->available_;
	}); 
	return ret;
}

std::vector<CThostFtdcInvestorPositionField *> CTPTraderHandler::get_investor_position(std::string investor_id, std::string broker_id)
{
    //FIXME DOUBLE FREE ERROR, comment first
    // if(v_investor_position_fields.size()>0){
        // for(auto it=v_investor_position_fields.begin(); it!=v_investor_position_fields.end(); ++it)
	    // {
            // LOG(WARNING)<<"Delete position fields";
            // delete *it;
            // LOG(WARNING)<<"Complete Delete position fields";
	    // }
    // }

	CThostFtdcQryInvestorPositionField investor_pos_fields = {0};
	std::strcpy(investor_pos_fields.InvestorID, investor_id.c_str());
	std::strcpy(investor_pos_fields.BrokerID, broker_id.c_str());
	int ret =  this->ReqQryInvestorPosition(&investor_pos_fields, nRequestID++);
	LOG(INFO)<<"req investor position:"<<ret;
	return v_investor_position_fields;
}

std::vector<CThostFtdcTradingAccountField*> CTPTraderHandler::get_account(std::string investor_id, std::string broker_id)
{
	for(auto it=v_trading_account.begin(); it!=v_trading_account.end();++it)
	{
		delete *it;
	}
	CThostFtdcQryTradingAccountField trading_account_fields = {0};
	std::strcpy(trading_account_fields.AccountID, investor_id.c_str());
	std::strcpy(trading_account_fields.BrokerID, broker_id.c_str());
	int ret_req = ReqQryTradingAccount(&trading_account_fields, nRequestID++);	
	LOG(INFO)<<"Req return is:"<<ret_req;
	return v_trading_account;
}

int CTPTraderHandler::req_trade(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryTradeField trade_fields = {0};
	std::strcpy(trade_fields.InvestorID, investor_id.c_str());
	std::strcpy(trade_fields.BrokerID, broker_id.c_str());
	int ret_req = ReqQryTrade(&trade_fields, nRequestID++);
	LOG(INFO)<<"Req return is:"<<ret_req;
	return ret_req;
}

int CTPTraderHandler::insert_order(OrderData * p_orderdata){
    LOG(INFO)<<"[insert_order] insert order with symbol=>"<<p_orderdata->symbol<<",vol=>"<<p_orderdata->volume<<",side=>"<<p_orderdata->side<<",price=>"<<p_orderdata->price;
    order_complete_ = false;
    CThostFtdcInputOrderField orderfield ={0};
    strcpy(orderfield.BrokerID, this->broker_id.c_str());//"9999"
    strcpy(orderfield.InvestorID, this->user_id.c_str());// "184820"
    strcpy(orderfield.ExchangeID, p_orderdata->exchangeid.c_str());
    strcpy(orderfield.InstrumentID, p_orderdata->symbol.c_str());  
    std::sprintf(orderfield.OrderRef, "%d", nRequestID);
    // std::cout<<"order ref in order field:"<<orderfield.OrderRef<<std::endl;
    orderfield.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    if(p_orderdata->side == OrderSide_Buy){
        orderfield.Direction = THOST_FTDC_D_Buy;    
    }else if (p_orderdata->side == OrderSide_Sell){
        orderfield.Direction = THOST_FTDC_D_Sell;
    }
    orderfield.LimitPrice = p_orderdata->price;
    orderfield.VolumeTotalOriginal = p_orderdata->volume;    
    orderfield.ContingentCondition = THOST_FTDC_CC_Immediately;  
    if(p_orderdata->position_effect == PositionEffect_Close){
        orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday; //TODO by default close today, to see whether to support close yesterday
    }else if(p_orderdata->position_effect ==  PositionEffect_Open){
        orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    }
    orderfield.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    //TODO double check 下单类型；test SHFE,只有即成撤单，或者当日有效可�?    
    // orderfield.TimeCondition = THOST_FTDC_TC_IOC;//立即完成，否则撤�?
    orderfield.TimeCondition = THOST_FTDC_TC_GFD;//当日有效
    orderfield.VolumeCondition = THOST_FTDC_VC_AV;    
    orderfield.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;  
    int ret = ReqOrderInsert(&orderfield, nRequestID++);
    unique_lock<mutex> mlock(mutex_);
	    cond_.wait(mlock, [&]() {
	    	return order_complete_;
	    });
    return ret;
}

std::string CTPTraderHandler::get_order_id1(ptr_OrderIDRef p_orderidref){
    std::ostringstream oss;
    oss<<p_orderidref->FrontID <<"_"<<p_orderidref->SessionID<< "_"<<p_orderidref->OrderRef;
    return oss.str();
}

std::string CTPTraderHandler::get_order_id2(ptr_OrderIDRef p_orderidref){
    std::ostringstream oss;
    oss<<p_orderidref->ExchangeID<<"_"<<p_orderidref->OrderSysID;
    return oss.str();
}

void CTPTraderHandler::update_positions(CThostFtdcTradeField* p_trade){
    LOG(INFO)<<"*******************************START UPDATE POSITIONS:"<<p_trade->InstrumentID<<",exe volume:"<<p_trade->Volume<<",pos_available:"<<pos_available_<<",order_complete:"<<order_complete_;
    this->pos_available_ = false;
    unique_lock<mutex> mlock(mutex_);
    double exe_price = p_trade->Price;
    int exe_vol = p_trade->Volume; 

    bool _trade_open = true;
    //如果是平仓、平今或者平昨，则交易数量变动是负的
    if(p_trade->OffsetFlag == THOST_FTDC_OF_Close || p_trade->OffsetFlag==THOST_FTDC_OF_CloseToday || p_trade->OffsetFlag== THOST_FTDC_OF_CloseYesterday){
        exe_vol = - exe_vol;
        _trade_open = false;
    }
    LOG(INFO)<<"[update_positions] Start update positions,curr pos size:"<<v_investor_position_fields.size();

    bool flag = false;
    if (v_investor_position_fields.size()>0){//have positions now
        for(auto it=v_investor_position_fields.begin(); it!=v_investor_position_fields.end(); ++it){
            ptr_Position  p_curr_pos = *it;
            LOG(INFO)<<"[update_positions] current positions:"<<p_curr_pos->InstrumentID<<",pos vwap:"<<p_curr_pos->OpenCost<<",pos vol:"<<p_curr_pos->OpenVolume<<",pos side:"<<p_curr_pos->PosiDirection;
            LOG(INFO)<<"[update_positions]to be added exe,check cond:"<<p_trade->InstrumentID<<",exe side:"<<p_trade->Direction<<",pos side:"<<p_curr_pos->PosiDirection;

            bool _is_long = p_curr_pos->PosiDirection == THOST_FTDC_PD_Long && p_trade->Direction == THOST_FTDC_D_Buy;
            bool _is_short = p_curr_pos->PosiDirection == THOST_FTDC_PD_Short && p_trade->Direction == THOST_FTDC_D_Sell;
            bool _is_same_direction = _is_long || _is_short;
            std::cout<<"pos idrection(2:long,3:short)=>"<<p_curr_pos->PosiDirection<<",trade direction(0:buy, 1:sell)=>"<<p_trade->Direction<<",is_logn=>"<<_is_long<<",_is_short=>"<<_is_short<<std::endl;
            //合约相同，开仓方向相同或者平仓方向相反，则合共和更新仓位
            bool _is_pos_exist = (strcmp(p_curr_pos->InstrumentID, p_trade->InstrumentID)==0) && ((_trade_open&&_is_same_direction)||(!_trade_open && !_is_same_direction));
            LOG(INFO)<<"[update_positions] check whether to merge position========>:"<<_is_pos_exist;
            if(_is_pos_exist){ //position exists 
                LOG(INFO)<<"pos exist, and update position"<<",pos vol:"<<p_curr_pos->TodayPosition<<",exe vol:"<<exe_vol;
                flag = true;
                if (p_curr_pos->TodayPosition + exe_vol == 0){
                    p_curr_pos->OpenCost = 0.0; 
                }else{
                    p_curr_pos->OpenCost = (p_curr_pos->OpenCost*p_curr_pos->TodayPosition + p_trade->Price*exe_vol)/(p_curr_pos->TodayPosition+exe_vol);
                }
                p_curr_pos->TodayPosition += exe_vol;
                //TODO add other value updates
                LOG(INFO)<<"[update_positions] After update position,curr vol=>"<<p_curr_pos->TodayPosition;
                break;
            }
        }
    }
    
    if(!flag){
        LOG(INFO)<<"[update_positions] symbol not exist, start create new position for open order,flag=>"<<flag<<"all pos size=>"<<v_investor_position_fields.size();
        ptr_Position p_pos = new PositionField();
        strcpy(p_pos->InstrumentID, p_trade->InstrumentID);
        p_pos->OpenCost = p_trade->Price;
        p_pos->TodayPosition = p_trade->Volume;
        // p_pos->volume_today = p_exe->volume;
        if(p_trade->Direction == THOST_FTDC_D_Buy){
            p_pos->PosiDirection = THOST_FTDC_PD_Long;
        } else if(p_trade->Direction == THOST_FTDC_D_Sell){
            p_pos->PosiDirection = THOST_FTDC_PD_Short;
        }
        //TODO add other value updates 
        LOG(INFO)<<"[update_positions] new add pos,vwap=>"<<p_pos->OpenCost<<",vol=>"<<p_pos->TodayPosition<<",direction [2:long,3:short] =>"<<p_pos->PosiDirection;
        v_investor_position_fields.push_back(p_pos);
        LOG(INFO)<<"[update_positions] after add new transaction,all position size=>"<<v_investor_position_fields.size()<<",curr pos vol=>"<<p_pos->TodayPosition;
    }
    this->pos_available_ = true;
    LOG(INFO)<<"*****************************[update_positions] complete update position, pos_avaible_=>"<<pos_available_<<",order_complete_=>"<<order_complete_;
    mlock.unlock();     //释放�?
    cond_.notify_all(); //通知正在阻塞等待的线�?
}

int CTPTraderHandler::cancel_order(ptr_OrderIDRef p_orderidref){
    
    order_complete_ = false;
    CThostFtdcInputOrderActionField orderfield ={0};

    //account info
    strcpy(orderfield.BrokerID, this->broker_id.c_str());//"9999"
    strcpy(orderfield.InvestorID, this->user_id.c_str());// "184820"
    
    //following 2 fields form the unique order
    strcpy(orderfield.ExchangeID,p_orderidref->ExchangeID);
    strcpy(orderfield.OrderSysID, p_orderidref->OrderSysID);

    //following 3 fields form the unique order
    orderfield.SessionID = p_orderidref->SessionID;
    orderfield.FrontID = p_orderidref->FrontID;
    strcpy(orderfield.OrderRef, p_orderidref->OrderRef);

    orderfield.ActionFlag = THOST_FTDC_AF_Delete;

    int ret = ReqOrderAction(&orderfield, nRequestID++);
    return ret;
}

std::vector<ptr_OrderField> CTPTraderHandler::get_all_orders()
{
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
    return order_available_ ; 
    }); //等待条件变量通知
    std::vector<ptr_OrderField> v_ret_orders;
    for (auto it = m_all_orders.begin(); it != m_all_orders.end(); ++it){
        v_ret_orders.push_back(it->second);
    }
    return v_ret_orders;
}

int CTPTraderHandler::cancel_all_orders(){
    int ret = 0;
    // std::cout<<"calling cancel all orders"<<std::endl;
    for (auto it = m_all_orders.begin(); it != m_all_orders.end(); ++it){
        if(!(it->second->OrderStatus == THOST_FTDC_OST_AllTraded || it->second->OrderStatus == THOST_FTDC_OST_Canceled)){
            std::cout<<"?????????cancel order=>"<<it->second->p_orderid_ref->OrderRef<<std::endl;
            ret = cancel_order(it->second->p_orderid_ref);
        }
    }
    return ret;
}

std::vector<ptr_Position> CTPTraderHandler::get_positions(){
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return pos_available_ ; 
    }); //等待条件变量通知
    return this->v_investor_position_fields;
}

std::vector<ptr_Position> CTPTraderHandler::get_positions(const std::string& instrument_id){
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return pos_available_ ; 
    }); //等待条件变量通知
    std::vector<ptr_Position> v_ret_pos;
    for(auto it = this->v_investor_position_fields.begin(); it != v_investor_position_fields.end(); ++it){
        ptr_Position p_cur_pos = *it;
        if(strcmp(p_cur_pos->InstrumentID, instrument_id.c_str()) == 0 && p_cur_pos->TodayPosition>0){
            v_ret_pos.push_back(p_cur_pos);
        }
    }
    return v_ret_pos;
}

int CTPTraderHandler::close_position(ptr_Position p_pos){
    LOG(INFO)<<"[close_position] close position for symbol=>"<<p_pos->InstrumentID<<",vol=>"<<p_pos->TodayPosition<<", side=>"<<p_pos->PosiDirection;
    OrderData *p_orderdata = new OrderData();
    p_orderdata->volume = p_pos->TodayPosition;
    p_orderdata->exchangeid = p_pos->ExchangeID;
    if(p_pos->PosiDirection == THOST_FTDC_PD_Long){
        p_orderdata->side = OrderSide_Sell;
        p_orderdata->price = this->down_limit_price;
    }else if(p_pos->PosiDirection == THOST_FTDC_PD_Short){
        p_orderdata->side = OrderSide_Buy;
        p_orderdata->price = this->up_limit_price;
    }
    p_orderdata->order_type = OrderType_Limit;
    p_orderdata->position_effect = PositionEffect_Close;
    p_orderdata->symbol = p_pos->InstrumentID;
    int ret = insert_order(p_orderdata);
    LOG(INFO)<<"[close_position] return for close position";
    return ret;
}
    
int CTPTraderHandler::close_all_positions(){
    std::vector<ptr_Position> v_pos = get_positions();//FIXME check whether to filter by product_id or symbol
    int ret = 0;
    LOG(INFO)<<"[close_all_positions] close all positions with size=>"<<v_pos.size();
    for(auto it = v_pos.begin(); it!=v_pos.end(); ++it){
        ptr_Position p_cur_pos = *it;
        if(p_cur_pos->TodayPosition >0){
            ret = close_position(p_cur_pos);
        }
    }
    return ret;
}