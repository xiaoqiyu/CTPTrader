#include<iostream>
#include<vector>
#include <thread>
#include<cstring>
#include<string>
#include "gmtrade_def.h"
#include "gmtrade.h"
#include "GMSimTrader.h"
#include <fstream>
#include <glog/logging.h>
#include <math.h>



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


std::vector<std::string> split_str(std::string s, char c)
{
    // std::string strInstruments = reader.Get("md", "InstrumentID", "rb2110,m2109");
    std::vector<std::string> v;
	std::stringstream sstr(s);
	std::string token;
	int cnt = 0;
    while (getline(sstr, token, c))
    {
       v.push_back(token);
    }
    return v;
}


int main(int argc, char *argv[])
{      
    ifstream fin ("app/simtrade/orders.csv");
    std::string line;

    // token身份认证
    GMSimTrader mt ("a1128cf0aaa3735b04a2706c8029a562e8c2c6b6"); 

    // 设置服务地址api.myquant.cn:9000
    mt.set_endpoint ("api.myquant.cn:9000");

    std::string future_acc = "a1a91403-2fc2-11ec-bd15-00163e0a4100";
    std::string equ_acc = "19377b27-4813-11ec-a1e1-00163e0a4100";
    std::string order_acc = "3a2249d2-4e79-11ec-97c8-00163e0a4100";
    std::string account_id = order_acc;

    // 登录账户id
    mt.login(account_id.c_str());
    mt.init();

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

    
    //position
    gmtrade::DataArray<Position> *ps = mt.get_position(account_id.c_str());
    // vector<vector<std::string>>  curr_pos;
    vector<std::string> curr_positions;
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
            "pnl:"<<p.fpnl<<
            std::endl;
            LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
            LOG(INFO)<<"available: "<<p.available<<std::endl;
            LOG(INFO)<<"instrument id: "<<p.symbol<<","<<p.side<<std::endl;
            LOG(INFO)<<"side:"<<p.side<<std::endl;
            LOG(INFO)<<"fpnl:"<<p.fpnl<<std::endl;
            LOG(INFO)<<"amount"<<p.amount<<std::endl;
            std::cout<<p.fpnl/p.amount<<std::endl;
        }
        // ps->release();
    }

    Cash cash{};
    int res = mt.get_cash (cash, account_id.c_str());
    if (res == 0)
    {
        LOG(INFO)<<"return for query cash:"<<std::endl;
        LOG(INFO) << "account_id: "<< cash.account_id<<std::endl;;
        LOG(INFO) << "available: " << cash.available<<std::endl;
        LOG(INFO) << "balance: " << cash.balance<<std::endl;
        LOG(INFO) << "fpnl: " << cash.fpnl<<std::endl;
    }
    Order _order;
    int pos_num = 0;
    // start order from file
    if (fin.is_open())
    {
        LOG(INFO)<<"order file exist, start to order....."<<std::endl;
        std::vector<std::string> v_line;
        std::vector<std::string> target_positions;
        
        int order_volume;
        int line_num = 0;
        while(std::getline(fin, line))
        {
            line_num += 1;
            if (line_num==1) continue;
            //TODO HACK 
            if (line_num == 2) break;
            v_line.clear();

            v_line = split_str(line, ',');
            target_positions.push_back(v_line[0]);
            if(std::find(curr_positions.begin(), curr_positions.end(), v_line[0]) == curr_positions.end() && pos_num <20)
            {

                LOG(INFO)<<"buy order for code:"<<v_line[0]<<",with volume:"<<std::stoi(v_line[2])<<std::endl;
                _order = mt.order_volume(v_line[0].c_str(),std::stoi(v_line[2])*100,OrderSide_Buy,OrderType_Market,PositionEffect_Open,56.15,equ_acc.c_str());
                if (_order.status == 1) pos_num +=1;
                LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<"pos num: "<<pos_num<<std::endl;
            }
        }    
        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            // LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
            if(std::find(target_positions.begin(),target_positions.end(), p.symbol) == target_positions.end())
            {
                LOG(INFO)<<"sell order for code:"<<p.symbol<<",with volume:"<<p.available<<std::endl;
                _order = mt.order_volume(p.symbol,p.available,OrderSide_Sell,OrderType_Market,PositionEffect_CloseYesterday,56.15,equ_acc.c_str());
                LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
            }
        }
        fin.close();
    }else{ // stop profit and loss
        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            // LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
            if(fabs(p.fpnl/p.amount) > 0.2)
            {
                LOG(INFO)<<"sell order for code:"<<p.symbol<<",with volume:"<<p.available<<std::endl;
                _order = mt.order_volume(p.symbol,p.available,OrderSide_Sell,OrderType_Market,PositionEffect_CloseYesterday,56.15,equ_acc.c_str());
                LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
            }
        }
    }
    ps->release();   
    getchar();
    return 0;
}
