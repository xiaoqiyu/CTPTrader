#include<iostream>
#include<vector>
#include <thread>
#include<cstring>
#include<string>
// #include "gmtrade_def.h"
// #include "gmtrade.h"
#include "GMSimTrader.h"
#include <fstream>
#include <glog/logging.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[])
{      
    // token身份认证
    SimTrader mt ("a1128cf0aaa3735b04a2706c8029a562e8c2c6b6"); 
    ifstream fin ("app/gmsimtrade/orders.csv");
    std::string line;

    std::string mode = "s";
    
    if (argc > 1) mode = argv[1];
    LOG(INFO)<<"run mode is:"<<mode<<std::endl;

    int select_acc = 0;
    if(argc>2) select_acc = std::stoi(argv[2]);

    int stop_profit_loss_pct = 20;
    if(argc>3) stop_profit_loss_pct = std::stoi((argv[3]));

    // 设置服务地址api.myquant.cn:9000
    mt.set_endpoint ("api.myquant.cn:9000");

    std::string future_acc = "a1a91403-2fc2-11ec-bd15-00163e0a4100";
    std::string equ_acc = "1a6d41a2-5590-11ec-8c77-00163e0a4100";
    std::string equ_test_acc = "d3b493fa-4165-11ec-abdb-00163e0a4100";
    std::string order_acc = "3a2249d2-4e79-11ec-97c8-00163e0a4100";
    std::string account_id = future_acc;

    // 登录账户id
    mt.login(account_id.c_str());
    // mt.init();

    //开始接收事件
    int status = mt.start();

    //判断状态
    if (status == 0)
    {
        LOG(INFO) << "connected to server" << std::endl;
    }
    else
    {
        LOG(INFO) << "Fail to connect to server" << std::endl;
    }


    Order _order;
    std::string symbol = "DCE.m2205";
    _order = mt.order_volume(symbol.c_str(),1,OrderSide_Buy,OrderType_Limit,PositionEffect_Open,3010,account_id.c_str());
    LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
    sleep(5);
    std::cout<<"order id:"<<_order.order_id<<std::endl;

    symbol = "DCE.eg2205";
    _order = mt.order_volume(symbol.c_str(),1,OrderSide_Buy,OrderType_Limit,PositionEffect_Open,4810,account_id.c_str());
    LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
    sleep(20);
    std::cout<<"order id:"<<_order.order_id<<std::endl;

    int ret = mt.order_cancel(_order.order_id, account_id.c_str());
    // int ret = mt.order_cancel_all();
    std::cout<<"return for cancel order:"<<ret<<std::endl;

    // gmtrade::DataArray<Order>* ret_order = mt.get_unfinished_orders(account_id.c_str());
    // std::cout<<"unfinished order cnt is:"<<ret_order->count()<<std::endl;
    // if(ret_order->status()==0){
        // for(int i=0; i<ret_order->count();++i){
            // Order &_tmp = ret_order->at(i);
            // int ret = mt.order_cancel(_tmp.order_id, account_id.c_str());
            // std::cout<<"return for cancel order:"<<ret<<std::endl;
        // }
    // ret_order->release();
    // }
    // 

    // _order = mt.order_volume(symbol.c_str(),1,OrderSide_Sell,OrderType_Market,PositionEffect_Close,56.15,account_id.c_str());
    // LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
    // usleep(20000);
    // _order = mt.order_volume(symbol.c_str(),1,OrderSide_Sell,OrderType_Market,PositionEffect_Close,56.15,account_id.c_str());
    // LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;

    
    getchar();
    return 0;
}


