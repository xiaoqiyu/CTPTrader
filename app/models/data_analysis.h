#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <vector>
#include <limits.h>
#include <cassert>
#include <string>
#include <utility>
#include <stdlib.h>
#include <glog/logging.h>
#include <dirent.h>

#include "ThostFtdcUserApiStruct.h"
#include "recordio.h"
#include "recordio_range.h"

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

    std::vector<std::string> v_timestamp;
    std::string _in = "m2109";
    // std::string file_name = "/home/kiki/projects/CTPTrader/cache/"+_in+"_depth_market_data_"+"20210518"; 
    // FILE *fp = fopen("/home/kiki/projects/CTPTrader/cache/m2109_depth_market_data_20210518.txt", "r");
    FILE *fp = fopen("/home/kiki/projects/CTPTrader/cache/m2109_depth_market_data_20210518.txt", "r");
    int errnum;
    if (NULL != fp)
    {
        std::cout << "read file" << std::endl;
        CThostFtdcDepthMarketDataField *p_mkt = new CThostFtdcDepthMarketDataField();

        while (!feof(fp))
        {
            fread(p_mkt, 1, sizeof(CThostFtdcDepthMarketDataField), fp);
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


void read_instruments()
{
    std::ifstream ifs( "/home/kiki/projects/CTPTrader/instruments.recordio", std::ios::binary);
    recordio::RecordReader reader(&ifs);
    std::string buffer;
    const std::string p_file_name = "/home/kiki/projects/CTPTrader/cache/p_instruments.txt"; 
    std::ofstream fout;
    fout.open(p_file_name, std::ios::out);
    while (reader.ReadBuffer(buffer)) {
        // std::cout<<"read ins:"<<std::endl;
        CThostFtdcInstrumentField instrument_fields={0};
        assert(buffer.size() == sizeof(instrument_fields));
        memcpy(&instrument_fields, buffer.data(), buffer.size());
        // fout<<instrument_fields.InstrumentID<<","<<instrument_fields.ProductClass<<std::endl;
        fout
            //  << instrument_fields.reserve1 << ","
             << instrument_fields.ExchangeID << ","
            //  << instrument_fields.InstrumentName << ","
            //  << instrument_fields.reserve2 << ","
            //  << instrument_fields.reserve3 << ","
             << instrument_fields.ProductClass << ","
             << instrument_fields.DeliveryYear << ","
             << instrument_fields.DeliveryMonth << ","
             << instrument_fields.MaxMarketOrderVolume << ","
             << instrument_fields.MinMarketOrderVolume << ","
             << instrument_fields.MaxLimitOrderVolume << ","
             << instrument_fields.MinLimitOrderVolume << ","
             << instrument_fields.VolumeMultiple << ","
             << instrument_fields.PriceTick << ","
             << instrument_fields.CreateDate << ","
             << instrument_fields.OpenDate << ","
             << instrument_fields.ExpireDate << ","
             << instrument_fields.StartDelivDate << ","
             << instrument_fields.EndDelivDate << ","
             << instrument_fields.InstLifePhase << ","
             << instrument_fields.IsTrading << ","
             << instrument_fields.PositionType << ","
             << instrument_fields.PositionDateType << ","
             << instrument_fields.LongMarginRatio << ","
             << instrument_fields.ShortMarginRatio << ","
             << instrument_fields.MaxMarginSideAlgorithm << ","
            //  << instrument_fields.reserve4 << ","
             << instrument_fields.StrikePrice << ","
             << instrument_fields.OptionsType << ","
             << instrument_fields.UnderlyingMultiple << ","
             << instrument_fields.CombinationType << ","
             << instrument_fields.InstrumentID << ","
             << instrument_fields.ExchangeInstID << ","
             << instrument_fields.ProductID << ","
             << instrument_fields.UnderlyingInstrID <<std::endl;
    }
    reader.Close();
    fout.close();
}

std::vector<std::string> list_files(std::string dirname)
{
    // std::string dirname;
    DIR *dp;
    std::vector<std::string> ret;
    struct dirent *dirp;
  if((dp = opendir(dirname.c_str())) == NULL)
    {
        std::cout << "Can't open " << dirname << std::endl;
    }
    while((dirp = readdir(dp)) != NULL)
    {
        ret.push_back(dirp->d_name);
    }
    closedir(dp);
    return ret;
}



// void data_preprocessing(std::string task_tag, std::string trade_date, std::string file_name)
void data_preprocessing(std::string file_name)
{

#if true
    // read_instruments();
    // const std::string file_name = "/home/kiki/projects/DERIQT_F/cache/mkt/"+task_tag+"_depth_market_data_"+trade_date+".recordio"; 
    const std::string full_file_name = "/home/kiki/projects/DERIQT_F/cache/mkt/"+file_name; 
    LOG(INFO)<<"read file is: "<<full_file_name;
    // FILE *fp = fopen(file_name.c_str(), "r");
    std::ifstream ifs(full_file_name, std::ios::binary);
    recordio::RecordReader reader(&ifs);
    // const std::string p_file_name = "/home/kiki/projects/DERIQT_F/cache/mkt_pycache/"+task_tag+"_depth_market_data_"+trade_date+".csv"; 
    const std::string p_file_name = "/home/kiki/projects/DERIQT_F/cache/mkt_pycache/"+file_name+".csv"; 
    
    LOG(INFO)<<"write file is: "<<p_file_name;
    int errnum;
    std::string buffer;
    if (true)
    {
        CThostFtdcDepthMarketDataField *p_mkt = new CThostFtdcDepthMarketDataField();
        std::ofstream fout;
        fout.open(p_file_name,std::ios::out);
        //SCHEMA
        // ["InstrumentID", "LastPrice", "OpenPrice", "HighestPrice", "LowestPrice", "Volume", "Turnover", "OpenInterest",
        // "UpperLimitPrice", "LowerLimitPrice", "UpdateTime",
        // "UpdateMillisec",
        // "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1", "BidPrice2", "BidVolume2", "AskPrice2", "AskVolume2",
        // "BidPrice3", "BidVolume3",
        // "AskPrice3", "AskVolume3", "BidPrice4", "BidVolume4", "AskPrice4", "AskVolume4", "BidPrice5", "BidVolume5",
        // "AskPrice5", "AskVolume5"]
        fout <<"InstrumentID"<<","<<"UpdateTime"<<","<<"Turnover"<<","<<"Volume"<<","<< "LastPrice"<<","<<
        "AveragePrice"<<","<< "AskPrice1"<<","<<"AskVolume1"<<","<<"BidPrice1"<<","<<"BidVolume1"<<std::endl;
        while (reader.ReadBuffer(buffer))
        {
            // _size = fread(p_mkt, 1, sizeof(CThostFtdcDepthMarketDataField), fp);
            assert(buffer.size()==sizeof(CThostFtdcDepthMarketDataField));
            memcpy(p_mkt, buffer.data(), buffer.size());
            // std::cout<<p_mkt->InstrumentID<<","<<p_mkt->UpdateTime<<std::endl;
            // std::cout<<p_mkt->UpdateTime<<","<<p_mkt->UpdateMillisec<<std::endl;
            fout<<p_mkt->InstrumentID<<","<<p_mkt->UpdateTime<<","
            <<p_mkt->Turnover<<","<<p_mkt->Volume<<","<<p_mkt->LastPrice<<","<<p_mkt->AveragePrice<<","
            <<p_mkt->AskPrice1<<","<<p_mkt->AskVolume1<<","<<p_mkt->BidPrice1<<","
            <<p_mkt->BidVolume1<<std::endl;
        }
        fout.close();
        reader.Close();
    }
    else
    {
        LOG(INFO) << "file is null" << std::endl;
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
    }
#endif

}


