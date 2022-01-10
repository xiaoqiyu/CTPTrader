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
    std::string account_id = order_acc;

    switch (select_acc)
    {
    case 1: // 量价1, equ
        account_id = equ_acc;
        break;
    case 2: //equ_test
        account_id = equ_test_acc;
        break;
    case 3: //future
        account_id = future_acc;
        break;
    default: //0
        account_id = order_acc;
        break;
    }

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

    // std::string _symbol = "m2201";
    // _order = mt.order_volume(_symbol.c_str(),1,OrderSide_Buy,OrderType_Market,PositionEffect_Open,56.15,equ_acc.c_str());
    
    //position
    gmtrade::DataArray<Position> *ps = mt.get_position(account_id.c_str());
    std::vector<std::string> curr_positions;
    if(ps->status()==0)
    {
        LOG(INFO)<<"return for query position: "<<ps->count()<<std::endl;
        // ofstream fout;
        // fout.open("app/simtrade/position.txt", ios::out | ios::trunc );

        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            // fout<<"account id:"<<p.account_id<<","<<
            // "available:"<<p.available<<","<<
            // "instrument id:"<<p.symbol<<","<<
            // "side:"<<p.side<<","<<
            // "pnl:"<<p.fpnl<<
            // std::endl;
            if (p.available > 0){
                LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
                LOG(INFO)<<"available: "<<p.available<<std::endl;
                LOG(INFO)<<"instrument id: "<<p.symbol<<","<<p.side<<std::endl;
                LOG(INFO)<<"side:"<<p.side<<std::endl;
                LOG(INFO)<<"fpnl:"<<p.fpnl<<std::endl;
                LOG(INFO)<<"amount"<<p.amount<<std::endl;
                std::cout<<p.fpnl/p.amount<<std::endl;
                curr_positions.push_back(p.symbol);
            }
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
    LOG(INFO)<<"curr positions:"<<std::endl;
    for(auto it1 = curr_positions.begin();it1 != curr_positions.end(); ++it1)
    {
        std::cout<<*it1<<std::endl;
    }
    
    if (fin.is_open())
    {
        LOG(INFO)<<"order file exist, start to order....."<<std::endl;
        std::vector<std::string> v_line;
        std::vector<std::string> target_positions;
        
        int order_volume;
        int line_num = 0;
        
        while(std::getline(fin, line))
        {
            LOG(INFO)<<"line:"<<line<<std::endl;
            line_num += 1;
            if (line_num<=1) continue;
            LOG(INFO)<<"lin num after:"<<line_num<<std::endl;

            v_line = split_str(line, ',');
            LOG(INFO)<<"check order for:"<<v_line[0];
            target_positions.push_back(v_line[0]);
            std::vector<std::string>::iterator iter = curr_positions.begin(); 
            while (iter != curr_positions.end() && *iter != v_line[0])
            {
                iter++;
            }
            if(iter == curr_positions.end()){
                if( iter == curr_positions.end() && pos_num <10 && mode == "b")
                {
                    LOG(INFO)<<"buy order for code:"<<v_line[0]<<",with volume:"<<std::stoi(v_line[2])<<std::endl;
                    _order = mt.order_volume(v_line[0].c_str(),std::stoi(v_line[2])*100,OrderSide_Buy,OrderType_Market,PositionEffect_Open,56.15,account_id.c_str());
                    if (_order.status == 1) pos_num +=1;
                    LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<"pos num: "<<pos_num<<std::endl;
                }else{
                    LOG(INFO)<<"not buy mode"<<std::endl;
                }
            }else{
                LOG(INFO)<<"code  exist"<<std::endl;
            }
        }    
        if (mode == "s"){
        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            std::vector<std::string>::iterator iter;
            for(iter = target_positions.begin(); iter!= target_positions.end(); ++iter)
            {
                if(*iter == p.symbol) break;
            }
            if(iter == target_positions.end() && mode == "s" && p.available >0)
            {
                LOG(INFO)<<"sell order for code:"<<p.symbol<<",with volume:"<<p.available<<std::endl;
                _order = mt.order_volume(p.symbol,p.available,OrderSide_Sell,OrderType_Market,PositionEffect_CloseYesterday,56.15,account_id.c_str());
                LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
            }
    
        }
        }
        
        fin.close();

    }else{ // stop profit and loss
        for (int i = 0; i<ps->count(); i++)
        {
            Position &p = ps->at(i);
            // LOG(INFO)<<"account id:"<<p.account_id<<std::endl;
            
            if(fabs(p.fpnl/p.amount) > (stop_profit_loss_pct/100.0))
            {
                LOG(INFO)<<"sell order for code:"<<p.symbol<<",with volume:"<<p.available<<"profit point"<<p.fpnl/p.amount<<" benchmark:"<<stop_profit_loss_pct/100.0;
                _order = mt.order_volume(p.symbol,p.available,OrderSide_Sell,OrderType_Market,PositionEffect_CloseYesterday,56.15,account_id.c_str());
                LOG(INFO)<<_order.status<<","<<_order.ord_rej_reason_detail<<std::endl;
            }
        }
        

    }
    
    ps->release();   
    getchar();
    return 0;
}













