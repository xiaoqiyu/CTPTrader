#include<iostream>
#include<vector>
#include "data_analysis.h"

int main(int argc, char *argv[])
{
    read_instruments();
    std::string dirname = "/home/kiki/projects/DERIQT_F/cache/mkt/";
    std::string trade_date="";
    std::string product_id = "";
    if (argc > 1){
        trade_date = argv[1];
    }
    std::vector<std::string> ret = list_files(dirname);
    for(auto it=ret.begin(); it != ret.end();++it)
    {
        std::string _file_name = *it;
        if(_file_name.find(trade_date) != std::string::npos)
        {
            std::cout<<"find: "<<trade_date<<" in "<<_file_name<<std::endl;
            data_preprocessing(*it);
        }
    
    }
    return 0;
}