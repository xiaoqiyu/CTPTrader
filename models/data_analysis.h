#pragma once
#include<stdio.h>
#include<iostream>
#include <errno.h>
#include<string.h>
#include <limits.h>
#include"ThostFtdcUserApiStruct.h"

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
    FILE* fp = fopen("/home/kiki/projects/CTPTrader/cache/cu2106_depth_market_data_20210514.txt", "r");
    int errnum;
    if (NULL != fp)
    {
        std::cout<<"read file"<<std::endl;
        CThostFtdcDepthMarketDataField* p_mkt = new CThostFtdcDepthMarketDataField();
        int _size = fread(p_mkt,1,sizeof(CThostFtdcDepthMarketDataField), fp);
        std::cout<<p_mkt->InstrumentID<<","<<p_mkt->ClosePrice<<","<<p_mkt->AskPrice1<<std::endl;
        fclose(fp);
    }else{
        std::cout<<"file is null"<<std::endl;
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
}