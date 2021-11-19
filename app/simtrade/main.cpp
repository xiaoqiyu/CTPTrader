#include<iostream>
#include<vector>
#include <thread>
#include<cstring>
#include "gmtrade_def.h"
#include "gmtrade.h"
#include "GMSimTrader.h"
#include <fstream>
#include <glog/logging.h>



int create_simtrader()
{

    // token身份认证
    GMSimTrader mt ("a1128cf0aaa3735b04a2706c8029a562e8c2c6b6"); 

    // 设置服务地址api.myquant.cn:9000
    mt.set_endpoint ("api.myquant.cn:9000");

    // 登录账户id
    mt.login("13651466226");
    mt.init();

    //开始接收事件
    int status = mt.start();
    std::string future_acc = "a1a91403-2fc2-11ec-bd15-00163e0a4100";
    std::string equ_acc = "d3b493fa-4165-11ec-abdb-00163e0a4100";
    std::string account_id = future_acc;

    //判断状态
    if (status == 0)
    {
        LOG(INFO) << "connected to server" << std::endl;
    }
    else
    {
        LOG(INFO) << "Fail to connect to server" << std::endl;
    }

    
    //position
    gmtrade::DataArray<Position> *ps = mt.get_position(account_id.c_str());
    if(ps->status()==0)
    {
        LOG(INFO)<<"return for query position: "<<ps->count()<<std::endl;
        ofstream fout;
        fout.open("position.txt", ios::out | ios::trunc );

        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            fout<<"account id:"<<p.account_id<<","<<
            "available:"<<p.available<<","<<
            "instrument id:"<<p.symbol<<","<<
            "side:"<<p.side<<","<<
            std::endl;
            LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
            LOG(INFO)<<"available: "<<p.available<<std::endl;
            LOG(INFO)<<"instrument id: "<<p.symbol<<","<<p.side<<std::endl;
        }
        ps->release();
    }

    Cash cash{};
    int res = mt.get_cash (cash, future_acc.c_str());
    if (res == 0)
    {
        LOG(INFO)<<"return for query cash:"<<std::endl;
        LOG(INFO) << "account_id: "<< cash.account_id<<std::endl;;
        LOG(INFO) << "available: " << cash.available<<std::endl;
        LOG(INFO) << "balance: " << cash.balance<<std::endl;
        LOG(INFO) << "fpnl: " << cash.fpnl<<std::endl;
    }

    // DataArray<Order>* get_orders(const char *account = NULL);
    
    std::string order_cmd;
    std::cin>>order_cmd;
    while(order_cmd != "exit") 
    {
        std::string _symbol="DCE.m2201";
        std::string _sec_id = "SHSE.600158";
        // mt.order_volume(symbol=_symbol.c_str(), volume=1, side=2,order_type=2, position_effect=2, price=0, account=future_acc.c_str());
        // Order _order = mt.order_volume(_symbol.c_str(),1,1,2,1,0.0,account_id.c_str());
        //id,volume, side(1:b,2:s), ordertype(1:limit, 2: market, 3: stop)position(0:unknow, 1:long, 2:short),price, account
        Order _order;
        // std::string _sec_id;
        _order = mt.order_volume(_sec_id.c_str(),4000,OrderSide_Buy,OrderType_Market,PositionEffect_Open,56.15,equ_acc.c_str());
        LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
        std::cin>>order_cmd;
    }
    return 0;

}




int main(int argc, char *argv[])
{      

        // token身份认证
    GMSimTrader mt ("a1128cf0aaa3735b04a2706c8029a562e8c2c6b6"); 

    // 设置服务地址api.myquant.cn:9000
    mt.set_endpoint ("api.myquant.cn:9000");

    // 登录账户id
    mt.login("a1a91403-2fc2-11ec-bd15-00163e0a4100");
    mt.init();

    //开始接收事件
    int status = mt.start();
    std::string future_acc = "a1a91403-2fc2-11ec-bd15-00163e0a4100";
    std::string equ_acc = "d3b493fa-4165-11ec-abdb-00163e0a4100";
    std::string account_id = future_acc;

    //判断状态
    if (status == 0)
    {
        LOG(INFO) << "connected to server" << std::endl;
    }
    else
    {
        LOG(INFO) << "Fail to connect to server" << std::endl;
    }

    
    //position
    gmtrade::DataArray<Position> *ps = mt.get_position(account_id.c_str());
    if(ps->status()==0)
    {
        LOG(INFO)<<"return for query position: "<<ps->count()<<std::endl;
        ofstream fout;
        fout.open("position.txt", ios::out | ios::trunc );

        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            fout<<"account id:"<<p.account_id<<","<<
            "available:"<<p.available<<","<<
            "instrument id:"<<p.symbol<<","<<
            "side:"<<p.side<<","<<
            std::endl;
            LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
            LOG(INFO)<<"available: "<<p.available<<std::endl;
            LOG(INFO)<<"instrument id: "<<p.symbol<<","<<p.side<<std::endl;
        }
        ps->release();
    }

    Cash cash{};
    int res = mt.get_cash (cash, future_acc.c_str());
    if (res == 0)
    {
        LOG(INFO)<<"return for query cash:"<<std::endl;
        LOG(INFO) << "account_id: "<< cash.account_id<<std::endl;;
        LOG(INFO) << "available: " << cash.available<<std::endl;
        LOG(INFO) << "balance: " << cash.balance<<std::endl;
        LOG(INFO) << "fpnl: " << cash.fpnl<<std::endl;
    }

    // DataArray<Order>* get_orders(const char *account = NULL);
    
    std::string order_cmd;
    std::cin>>order_cmd;
    while(order_cmd != "exit") 
    {
        std::string _symbol="DCE.m2201";
        std::string _sec_id = "SHSE.600158";
        // mt.order_volume(symbol=_symbol.c_str(), volume=1, side=2,order_type=2, position_effect=2, price=0, account=future_acc.c_str());
        // Order _order = mt.order_volume(_symbol.c_str(),1,1,2,1,0.0,account_id.c_str());
        //id,volume, side(1:b,2:s), ordertype(1:limit, 2: market, 3: stop)position(0:unknow, 1:long, 2:short),price, account
        Order _order;
        // std::string _sec_id;
        _order = mt.order_volume(_symbol.c_str(),1,OrderSide_Buy,OrderType_Market,PositionEffect_Open,56.15,future_acc.c_str());
        LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
        std::cin>>order_cmd;
    }
    getchar();
    return 0;
}