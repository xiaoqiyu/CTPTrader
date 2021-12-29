#include "OrderSignal.h"
#include <vector>


OrderData* OrderSignal::get_signal(const std::vector<std::string>&v_rev, int trading_mode, std::vector<Position *> v_positions){
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
	
	OrderData* p_orderdata = new OrderData();

	if (v_positions.size()>0){//stop_profit and loss
		for(auto it=v_positions.begin(); it!=v_positions.end();++it){
			int _side = PositionSide_Long;
			if((*it)->side == PositionSide_Long){
				_side = PositionSide_Short;
			}
			if(((*it)->fpnl>10 && (*it)->side==PositionSide_Long ) || ((*it)->fpnl<-10 && (*it)->side==PositionSide_Short)){ //fpnl=((price-vwap)*volume*multiplier)
				LOG(INFO)<<"Get stop profit/loss signal";
				p_orderdata->symbol = (*it)->symbol;
				p_orderdata->order_type = OrderType_Market;
				p_orderdata->position_effect = PositionEffect_Close;
				p_orderdata->side = _side;
				p_orderdata->price = (*it)->vwap;
				p_orderdata->volume = (*it)->volume_today;//todays volume
				p_orderdata->status = 1;
			}
		}
	}else{ //open signal
		if(_mid-_last_price>1.0){ //open long
			LOG(INFO)<<"Get long open signal";
			p_orderdata->symbol = _symbol;
			p_orderdata->order_type = OrderType_Market;
			p_orderdata->position_effect = PositionEffect_Open;
			p_orderdata->side = OrderSide_Buy;
			p_orderdata->price = 0.0;
			p_orderdata->volume = 1;//1 shot
			p_orderdata->status = 2;

		}else if (_last_price-_mid>1.0){//open short
			LOG(INFO)<<"Get short open signal";
			p_orderdata->symbol = _symbol;
			p_orderdata->order_type = OrderType_Market;
			p_orderdata->position_effect = PositionEffect_Open;
			p_orderdata->side = OrderSide_Sell;
			p_orderdata->price = 0.0;
			p_orderdata->volume = 1;//1 shot
			p_orderdata->status = 2;
		}
	}
	// LOG(INFO)<<"before return in get_signal"<<p_orderdata->status<<","<<p_orderdata->symbol<<","<<p_orderdata->side;
	return p_orderdata;
	//FIXME task_tag is not grarantee to be product id
	// std::string _exchange = get_exchange_id_order11(this->mode, this->task_tag); 

    // sample data from log:Recieve:eg2205,15:01:13,770,352685,4819,4819,4819,2,4820.85,48027.5,4819
    //Recieve:eg2205,14:59:33,279,351987,4819,4821,0,1,4818.71,48027.2,4819
	// LOG(INFO)<<"Recieve:"<<_symbol<<","<<_update_time<<","<<_update_milsec<<","<<_volume
    // <<","<<_last_price<<","<<_max<<","<<_min<<","<<_spread<<","<<_mid<<","<<_vwap<<","<<_slope;
}