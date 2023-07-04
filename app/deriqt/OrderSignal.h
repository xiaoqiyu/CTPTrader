#pragma once
#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <glog/logging.h>
#include "define.h"
// #include "gmtrade_def.h"
#include "UserStruct.h"
#include "INIReader.h"


class OrderSignal
{
public:
	OrderSignal(const std::string& name):strategy_name(name){
		FileName _strategy_file = {'\0'};
		// std::string _str_file_name = "/home/kiki/projects/DERIQT_F/conf/strategy.ini"; //FIXME remove hardcode

		std::string _str_file_name = "/home/kiki/workspace/CTPTrader/conf/"+name+".ini"; //FIXME remove hardcode
		strcpy(_strategy_file, _str_file_name.c_str());
		config_ptr.reset(new INIReader(_strategy_file));
		if (config_ptr->ParseError() != 0)
		{
			LOG(FATAL)<< "[init] Fail to load config file in current directory:"<< _str_file_name;
		}
		std::vector<std::string> v_rev;
		char c = ',';
		std::stringstream sstr(config_ptr->Get("strategy","strategy_name","ma"));
		std::string token;
		while(getline(sstr, token, c)){
			v_strategy_name.push_back(token);
		}
		this->strategy_num = v_strategy_name.size();
		this->long_score_benchmark = std::stod(config_ptr->Get("strategy","long_score_ratio","0.0")) * strategy_num;
		this->short_score_benchmark = std::stod(config_ptr->Get("strategy","short_score_ratio","0.0")) * strategy_num;

		// FIXME remove hardcode, load dl model
		// module_ptr = std::make_unique< torch::jit::script::Module>(torch::jit::load("/home/kiki/workspace/CTPTrader/app/torch_example/rnn_rb.pt"));
		// at::Tensor output = module.forward(inputs).toTensor();

		// load param model 
		std::fstream newfile;
		char c = ',';
		std::string token;
		std::vector<double> v_bins;
		std::vector<double> v_var;
		std::vector<double> v_means;
		newfile.open("/home/kiki/workspace/CTPTrader/conf/tsmodels_rb.txt", std::ios::in);
		int line_num = 0; 
		if (newfile.is_open()){
		std::string tp;
		while(getline(newfile, tp)){
			std::stringstream sstr(tp);
			while(getline(sstr, token, c)){
			if(line_num==0){
					v_bins.push_back(std::stod(token));
			}else if (line_num == 1){
				v_means.push_back(std::stod(token));
			}else if (line_num == 2){
				v_var.push_back(std::stod(token));
			}
				}
			line_num ++;
		}
		newfile.close();
		}
	};
	~OrderSignal();
	OrderData* get_signal(const std::vector<std::string>&v_rev, ptr_daily_cache p_daily);
	int get_com_signal(const std::vector<std::string>&v_rev, double _range);
	int _ma_rules(double _ma_diff_last, double _ma_diff_curr);
	int _reg_rules(double _log_return, double _mid_log_return);
	int _dual_thrust(double last_price, double _range, double open_price);
	int _dl_rules(std::string update_time, double price_spread, double last_price, double interest_diff, double volume, double wap, double log_return);

private:
	int _order_volume; 
	int order_side; 
	int order_type; //market, limit
	double order_price;
	double open_price = 0.0;
	std::string sec_id;
	std::unique_ptr<INIReader> config_ptr;
	// std::unique_ptr< torch::jit::script::Module> module_ptr;
	std::vector<std::string> v_strategy_name;//substrategy/signal name list
	float long_score_benchmark; //final score ratio of sum of sub strategy score 
	float short_score_benchmark; //final score ratio of sum of sub strategy score 
	int strategy_num;
	std::string strategy_name;
	//FIXME hardcode for test
	int test_signal_num = 0;
	std::vector<double> v_var; //varies for each factor from trained model
	std::vector<double> v_means; //means for each factor from trained model
	std::vector<double> v_bins; // means from trained model
};

