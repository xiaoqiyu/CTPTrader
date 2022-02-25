#include "simnow_order.h"

int main(int argc, char *argv[]){
    std::cout<<"sim now testing"<<std::endl;
    FileName _conf_file = {'\0'};
    std::string _conf_file_name = "/home/kiki/projects/DERIQT_F/conf/test.ini";
    LOG(INFO)<<"argc=>"<<argc<<"argv=>"<<argv[0]<<","<<argv[1];
    bool _tmp = argc>1;
    bool _t1 = argv[1] == "1";
    std::string mode = argv[1];
    std::cout<<_tmp<<","<<_t1<<std::endl;
    if(argc>1){
        if(mode == "1"){
            std::cout<<"reset conf"<<std::endl;
            _conf_file_name = "/home/kiki/projects/DERIQT_F/conf/ctp.ini";
        }
    }
    strcpy(_conf_file, _conf_file_name.c_str());
    INIReader reader(_conf_file);
    char ch[40];
    if (reader.ParseError() != 0)
    {
    	LOG(FATAL)<< "Fail to load config file in current directory:"<< _conf_file;
    	return 1;
    }
    trader_util_ptr p_trader_handler = new CTPTraderHandler();
    p_trader_handler->CreateFtdcTraderApi();
    p_trader_handler->RegisterFront(strcpy(ch, reader.Get("td", "FrontAddr", "127.0.0.1:1234").c_str()));
    p_trader_handler->init("rb",  reader.Get("user", "BrokerID", "9999"), reader.Get("user", "UserID", "123456"));
    sleep(2);
    // this->broker_id = reader.Get("user", "BrokerID", "9999");
    // this->user_id = reader.Get("user", "UserID", "123456");
    LOG(INFO) << "Start CTP Authenticate.......";
    CThostFtdcReqAuthenticateField reqAuth = {0};
    strcpy(reqAuth.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqAuth.UserID, reader.Get("user", "UserID", "123456").c_str());
    strcpy(reqAuth.AuthCode, reader.Get("user", "AuthCode", "!@#$%^&*").c_str());
    strcpy(reqAuth.AppID, reader.Get("user", "AppID", "MyProgram").c_str());
    p_trader_handler->ReqAuthenticate(&reqAuth, nRequestID++);
    sleep(2);
    LOG(INFO)<< "Start CTP Login......" << std::endl;
    CThostFtdcReqUserLoginField reqUserLogin = {0};
    strcpy(reqUserLogin.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());
    strcpy(reqUserLogin.UserID, reader.Get("user", "UserID", "123456").c_str());
    strcpy(reqUserLogin.Password, reader.Get("user", "Password", "123456").c_str());
    strcpy(reqUserLogin.MacAddress, reader.Get("user", "MacAddress", "123456").c_str());
    strcpy(reqUserLogin.UserProductInfo, reader.Get("user", "UserProductInfo", "123456").c_str());
    p_trader_handler->ReqUserLogin(&reqUserLogin, nRequestID++);
    sleep(2);
    std::string trading_date = p_trader_handler->getTradingDay();
    LOG(INFO)<< "Trading date is: " << trading_date;

    
    OrderData *p_orderdata = new OrderData();
    bool _open = false;
    int order_cnt = 0;
    std::string instrument_id = "rb2205";
    double up_limit_price = std::stod(reader.Get("strategy","up_limit_price","0.0"));
    double down_limit_price = std::stod(reader.Get("strategy","down_limit_price","0.0"));
    std::string exchangeid = "SHFE";
    while(order_cnt < 2){
        if (_open){
            p_orderdata->volume = 2;
            p_orderdata->price = down_limit_price;
            p_orderdata->exchangeid = exchangeid;
            p_orderdata->side = OrderSide_Sell;
            p_orderdata->order_type = OrderType_Limit;
            p_orderdata->position_effect = PositionEffect_Close;
            p_orderdata->symbol = instrument_id;
            int ret = p_trader_handler->insert_order(p_orderdata);
            std::cout<<"close order return:"<<ret<<std::endl;
            _open = false;
            order_cnt += 1;
        }else if(!_open){
            p_orderdata->volume = 2;
            p_orderdata->price = up_limit_price;
            p_orderdata->exchangeid = exchangeid;
            p_orderdata->side = OrderSide_Buy;
            p_orderdata->order_type = OrderType_Limit;
            p_orderdata->position_effect = PositionEffect_Open;
            p_orderdata->symbol = instrument_id;
            int ret = p_trader_handler->insert_order(p_orderdata);
            std::cout<<"open order return:"<<ret<<std::endl;
            _open = true;
            order_cnt += 1;
        }
        sleep(2);
        std::vector<ptr_OrderField> v_ret_order = p_trader_handler->get_all_orders();
        for(auto it = v_ret_order.begin(); it!=v_ret_order.end(); ++it){
            ptr_OrderField p_cur_order = *it;
            std::cout<<p_cur_order->order_id<<",vol=>"<<p_cur_order->VolumeTotalOriginal<<",vol traded=>"<<p_cur_order->VolumeTraded<<std::endl;
        }
        std::vector<ptr_Position> v_ret_pos = p_trader_handler->get_positions();
        for(auto it  = v_ret_pos.begin(); it!=v_ret_pos.end(); ++it){
            ptr_Position p_cur_pos = *it;
            std::cout<<"pos=>"<<p_cur_pos->TodayPosition<<",price"<<p_cur_pos->OpenCost<<",hold cost=>"<<p_cur_pos->PositionCost<<std::endl;
        }
        sleep(30);
    }


    // p_trader_handler->broker_id = reader.Get("user", "BrokerID", "9999");
    // p_trader_handler->user_id = reader.Get("user", "UserID", "123456");

    // CThostFtdcInputOrderField orderfield ={0};
    // TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb2205"; 
    // strcpy(orderfield.BrokerID, reader.Get("user", "BrokerID", "9999").c_str());//"9999"
    // strcpy(orderfield.InvestorID, reader.Get("user", "UserID", "123456").c_str());// "184820"
    // strcpy(orderfield.ExchangeID, "SHFE");
    // strcpy(orderfield.InstrumentID, g_pTradeInstrumentID);  
    // strcpy(orderfield.OrderRef,"10");
    // orderfield.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    // orderfield.Direction = THOST_FTDC_D_Sell;
    // orderfield.LimitPrice = 4800.0;
    // orderfield.VolumeTotalOriginal = 1;    
    // orderfield.ContingentCondition = THOST_FTDC_CC_Immediately;  
    // orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    // orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    // orderfield.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;    
    // orderfield.TimeCondition = THOST_FTDC_TC_IOC;
    // orderfield.VolumeCondition = THOST_FTDC_VC_AV;    
    // orderfield.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;  
    // int ret = p_trader_handler->ReqOrderInsert(&orderfield, 0);
    // std::cout<<"order ret:"<<ret<<std::endl;
    getchar();



    // FAK	THOST_FTDC_OPT_LimitPrice	THOST_FTDC_CC_Immediately	THOST_FTDC_TC_IOC	THOST_FTDC_VC_AV
    return 0;
}