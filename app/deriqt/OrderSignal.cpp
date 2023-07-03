#include "OrderSignal.h"
#include <vector>

int OrderSignal::_dual_thrust(double last_price, double _range, double open_price){ 
	double k1 = std::stod(config_ptr->Get("dual","k1","0.0"));
	double k2 = std::stod(config_ptr->Get("dual","k2","0.0"));
	std::cout<<k1<<","<<k2<<","<<last_price<<","<<open_price<<","<<open_price+k1*_range<<","<<open_price-k2*_range<<std::endl;
	if(last_price > open_price + k1 *_range){
		return 1;
	}else if(last_price < open_price - k2 * _range){
		return -1;
	}else{
		return 0;
	}
	return 0;
}

int OrderSignal::_ma_rules(double _ma_diff_last, double _ma_diff_curr){
	double edge = std::stod(config_ptr->Get("reg","edge","0.0"));
	if (_ma_diff_last <  edge && _ma_diff_curr > edge){
		return 1;
	}else if(_ma_diff_last > edge && _ma_diff_curr < edge){
		return -1;
	}else{
		return 0;
	}
	return 0;
}

// [models]
// log_return = 0.9368
// log_return_0 = 0.0174
// wap_log_return = 0.8194
// intercept = 000.00000119
// std::stod(reader_str.Get("strategy","up_limit_price","0.0"));
int OrderSignal::_reg_rules(double _log_return, double _mid_log_return){
	double _log_return_coef = std::stod(config_ptr->Get("reg","log_return","0.0"));
	double _mid_log_return_coef = std::stod(config_ptr->Get("reg","wap_log_return","0.0"));
	double _intercept = std::stod(config_ptr->Get("reg","intercept","0.0"));
	double _reg_long_thread = std::stod(config_ptr->Get("reg","long_threshold","0.0"));
	double _reg_short_thread = std::stod(config_ptr->Get("reg","short_threshold","0.0"));
	double _score = _log_return_coef * _log_return + _mid_log_return_coef * _mid_log_return + _intercept;
	
	if (_score>= _reg_long_thread){
		return 1;
	}else if(_score <= -_reg_short_thread){
		return -1;
	}else{
		return 0;
	}
	return 0;
}

int OrderSignal::_dl_rules(std::string update_time, double price_spread, double last_price, double interest_diff, double volume, double wap, double log_return){
	
	return 0;
}


int OrderSignal::get_com_signal(const std::vector<std::string>&v_rev, double _range){
	std::string _symbol = v_rev[0];
	std::string _update_time = v_rev[1];
	int _update_milsec = std::stoi(v_rev[2]);
	long _volume = std::stoi(v_rev[3]);
	double _last_price = std::stod(v_rev[4]);
	double _max = std::stod(v_rev[5]);
	double _min = std::stod(v_rev[6]);
	double _spread = std::stod(v_rev[7]);
	double _mid = std::stod(v_rev[8]);
	double _vwap = std::stod(v_rev[9]);
	double _log_return = std::stod(v_rev[10]);
	double _log_return_short = std::stod(v_rev[11]);
	double _log_return_long = std::stod(v_rev[12]);
	double _mid_log_return_short = std::stod(v_rev[13]);
	double _mid_log_return_long = std::stod(v_rev[14]);
	double _ma_short = std::stod(v_rev[15]);
	double _ma_long = std::stod(v_rev[16]);
	double _curr_vol = std::stod(v_rev[17]);
	double _curr_interest = std::stod(v_rev[18]);
	double _ma_ls_diff_last = std::stod(v_rev[19]);
	double _ma_ls_diff_curr = std::stod(v_rev[20]);
	double _tick_direction = std::stod(v_rev[21]);

	//print and check the factor
	//update_time:13:54:02
	// LOG(INFO)<<"Recieve:"<<_symbol<<",update_time:"<<_update_time<<",update msecc:"<<_update_milsec<<",volume:"<<_volume
	// <<",last price:"<<_last_price<<",max:"<<_max<<",min:"<<_min<<",spread:"<<_spread<<",:mid:"<<_mid<<",vwap:"<<_vwap<<",log return:"
	// <<_log_return<<",log return short:"<<_log_return_short<<",log return long:"<<_log_return_long<<",mid log return short:"<<_mid_log_return_short
	// <<",mid log return long:"<<_mid_log_return_long<<",ma short:"<<_ma_short<<",ma long:"<<_ma_long<<",ma diff last:"<<_ma_ls_diff_last
	// <<",ma diff curr:"<<_ma_ls_diff_curr<<", curr_vol"<<_curr_vol<<",curr_interest:"<<_curr_interest<<",tick direction:"<<_tick_direction;
	
	double long_score = 0.0;
	double short_score = 0.0;

	int n_strategy = 0;
	int total_score = 0;
	for (const auto &s : v_strategy_name)
	{       
		if(s == "ma"){
			total_score += _ma_rules(_ma_ls_diff_last, _ma_ls_diff_curr);
		}else if(s == "reg"){
			total_score += _reg_rules(_log_return, _mid_log_return_short); //TODO check the factor
		}else if (s == "dual"){
			total_score += _dual_thrust(_last_price, _range, this->open_price);
		}else{
			LOG(INFO)<<"Input other valid strategy name";
		}
	}
	
	if (total_score >= this->long_score_benchmark){
		LOG(INFO)<<"long signal:total score=>"<<total_score<<", long benchmark=>"<<long_score_benchmark;
		return LONG_SIGNAL;
	}else if(total_score <= -this->short_score_benchmark ){
		LOG(INFO)<<"short signal:total score=>"<<total_score<<", short benchmark=>"<<short_score_benchmark;
		return SHORT_SIGNAL;
	}else{
		return NO_SIGNAL;
	}
	return NO_SIGNAL;
}


OrderData* OrderSignal::get_signal(const std::vector<std::string>&v_rev, ptr_daily_cache p_daily){
	std::string _symbol = v_rev[0];
	std::string _update_time = v_rev[1];
	
	int _update_milsec = std::stoi(v_rev[2]);
	double _last_price = std::stod(v_rev[4]);
	
	std::string _exchangeid = v_rev[12];
	OrderData* p_orderdata = new OrderData();
	double _range = std::max(p_daily->hh-p_daily->lc, p_daily->hc-p_daily->ll);
	this->open_price = p_daily->open_price;
	int ret_signal = get_com_signal(v_rev, _range); //get the final signal
	//FIXME hardcode for test
	// if (test_signal_num == 0){
	// 	ret_signal = LONG_SIGNAL;
	// 	test_signal_num += 1;
	// }
	// else if(test_signal_num == 1)
	// {
	// 	ret_signal = SHORT_SIGNAL;
	// 	test_signal_num += 1;
	// }
	
	// std::cout<<"get_signal,time=>"<<_update_time<<",signal=>"<<ret_signal<<std::endl;
	if(ret_signal == LONG_SIGNAL){ //get long signal
		p_orderdata->exchangeid = _exchangeid;
		p_orderdata->symbol = _symbol;
		p_orderdata->order_type = OrderType_Limit;
		p_orderdata->position_effect = PositionEffect_Open;
		p_orderdata->side = OrderSide_Buy;
		p_orderdata->price = p_daily->down_limit;//TODO add condition check and exception handling
		p_orderdata->volume = 1;
		p_orderdata->status = LONG_SIGNAL;	
		std::cout<<"[get_signal] long signal update_time=>"<<_update_time<<"update milisec=>"<<_update_milsec<<std::endl;
		return p_orderdata; 
	}else if (ret_signal == SHORT_SIGNAL){ //get short signal
		p_orderdata->symbol = _symbol;
		p_orderdata->exchangeid = _exchangeid;
		p_orderdata->order_type = OrderType_Limit;
		p_orderdata->position_effect = PositionEffect_Open;
		p_orderdata->side = OrderSide_Sell;
		p_orderdata->price = p_daily->up_limit;//TODO add condition check and exception handling
		p_orderdata->volume = 1;
		p_orderdata->status = SHORT_SIGNAL;
		std::cout<<"[get_signal] short signal update_time=>"<<_update_time<<"update milisec=>"<<_update_milsec<<std::endl;
		return p_orderdata; 
	}else{//no signal, check whether to stop loss
		p_orderdata->status = NO_SIGNAL;	
		p_orderdata->price = _last_price;
	}
	return p_orderdata;
}
