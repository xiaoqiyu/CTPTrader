#pragma once
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <vector>
#include <limits.h>
#include "ThostFtdcUserApiStruct.h"

void get_depth_market()
{
    // const char* file_name = "/home/kiki/projects/CTPTrader/cache/cu2106_depth_market_data_20210514.txt";
    // char abs_path_buff[PATH_MAX];
    // if (realpath(file_name, abs_path_buff))
    // {
    //     std::cout<<abs_path_buff<<"/"<<file_name<<std::endl;
    // }else{
    //     std::cout<<"not exist"<<std::endl;
    // }

    vector<std::string> v_timestamp;
    std::string _in = "m2109";
    // std::string file_name = "/home/kiki/projects/CTPTrader/cache/"+_in+"_depth_market_data_"+"20210518"; 
    // FILE *fp = fopen("/home/kiki/projects/CTPTrader/cache/m2109_depth_market_data_20210518.txt", "r");
    FILE *fp = fopen("/home/kiki/projects/CTPTrader/cache/m2109_depth_market_data_20210518.txt", "r");
    int errnum;
    if (NULL != fp)
    {
        std::cout << "read file" << std::endl;
        CThostFtdcDepthMarketDataField *p_mkt = new CThostFtdcDepthMarketDataField();
        int _size;
        while (!feof(fp))
        {
             _size = fread(p_mkt, 1, sizeof(CThostFtdcDepthMarketDataField), fp);
            std::string _s = p_mkt->UpdateTime;
            if (_s==""){
                std::cout<<"empty"<<std::endl;
                continue;}
            // strcpy(_t, p_mkt->UpdateTime);
            v_timestamp.push_back(_s);
           
            // std::cout << p_mkt->InstrumentID << "," << p_mkt->ClosePrice << "," << p_mkt->AskPrice1 <<","<<p_mkt->UpdateTime<<std::endl;
        }
      
        fclose(fp);
    }
    else
    {
        std::cout << "file is null" << std::endl;
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
    }

    auto it = v_timestamp.begin();
    auto it1 = v_timestamp.rbegin();
    std::string t0=v_timestamp[0];
    for (int i=0;i<6;++i)
    {
        std::cout<<*(it+i)<<",";
    }
    std::cout<<std::endl;
    for (int i=0;i<10;++i)
    {
        std::cout<<*(it1+i)<<",";
    }
    // std::cout<<"begin:"<<*it<<","<<*(it+1)<<","<<*(it+2)<<","<<*(it1+1)<<","<<*it1<<std::endl;
    // auto it1 = v_timestamp.end();
    // std::cout<<(*it1)<<std::endl;
    // for(it; it!=v_timestamp.end(); ++it)
    // {
    //     std::cout<<*it<<endl;
    // }
    // auto rt = v_timestamp.end();
    // std::cout<<*it<<","<<*rt<<std::endl;
    std::cout<<v_timestamp.size()<<std::endl;
}





void data_preprocessing(std::string instrument_id, std::string trade_date)
{
    std::string file_name = "/home/kiki/projects/CTPTrader/cache/"+instrument_id+"_depth_market_data_"+trade_date+".recordio"; 
    std::cout<<"read file is: "<<file_name<<std::endl;
    // FILE *fp = fopen(file_name.c_str(), "r");
    std::ifstream ifs(file_name, std::ios::binary);
    recordio::RecordReader reader(&ifs);
    std::string p_file_name = "/home/kiki/projects/CTPTrader/cache/p_"+instrument_id+"_depth_market_data_"+trade_date+".txt"; 
    std::cout<<"write file is: "<<p_file_name<<std::endl;
    int errnum;
    std::string buffer;
    if (true)
    {
        CThostFtdcDepthMarketDataField *p_mkt = new CThostFtdcDepthMarketDataField();
        int _size;
        ofstream fout;
        fout.open(p_file_name,std::ios::app);
        
        while (reader.ReadBuffer(buffer))
        {
            // _size = fread(p_mkt, 1, sizeof(CThostFtdcDepthMarketDataField), fp);
            assert(buffer.size()==sizeof(CThostFtdcDepthMarketDataField));
            memcpy(p_mkt, buffer.data(), buffer.size());
            std::cout<<p_mkt->InstrumentID<<","<<p_mkt->UpdateTime<<std::endl;
            fout<<p_mkt->InstrumentID<<","<<p_mkt->UpdateTime<<"."<<p_mkt->UpdateMillisec<<","
            <<p_mkt->Turnover<<","<<p_mkt->Volume<<","<<p_mkt->LastPrice<<","<<p_mkt->AveragePrice<<","
            <<p_mkt->AskPrice1<<","<<p_mkt->AskVolume1<<","<<p_mkt->BidPrice1<<","
            <<p_mkt->BidVolume1<<std::endl;
        }
        fout.close();
        reader.Close();
    }
    else
    {
        std::cout << "file is null" << std::endl;
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
    }

   
}