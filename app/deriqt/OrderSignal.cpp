#include "OrderSignal.h"
#include <vector>


void OrderSignal::get_signal(const std::vector<std::string>&v_rev, int trading_mode){
    // std::string _symbol = "DCE.m2201";
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
    double _slope = std::stod(v_rev[10]);


	
	//FIXME task_tag is not grarantee to be product id
	// std::string _exchange = get_exchange_id_order11(this->mode, this->task_tag); 
	std::string _exchange;
	
	_exchange ="DCE";
    this->sec_id = _exchange + "." + _symbol;

    // sample data from log:Recieve:eg2205,15:01:13,770,352685,4819,4819,4819,2,4820.85,48027.5,4819
	LOG(INFO)<<"Recieve:"<<_symbol<<","<<_update_time<<","<<_update_milsec<<","<<_volume
    <<","<<_last_price<<","<<_max<<","<<_min<<","<<_spread<<","<<_mid<<","<<_vwap<<","<<_slope;

}