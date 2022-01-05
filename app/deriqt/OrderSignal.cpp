#include "OrderSignal.h"
#include <vector>

//FIXME remove hardcode
double stop_profit_loss = 1.0;

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
	
	long long total_vol = 0;

	if (v_positions.size()>0){//stop_profit and loss FIXME if there is positions for the current instruments(long or short, then it will not open, re-consider this restriction)
		for(auto it=v_positions.begin(); it!=v_positions.end();++it){
			int _side = PositionSide_Long;

			Position *p_curr_pos = *it;
			if(p_curr_pos->side == PositionSide_Long){
				_side = PositionSide_Short;
			}
			total_vol += p_curr_pos->volume; // add the vol in the positions
			
			//TODO pos fpnl not added yet,TBD
			bool is_close = (_last_price - p_curr_pos->vwap >=stop_profit_loss && p_curr_pos->side==PositionSide_Long && p_curr_pos->volume>0 ) || (p_curr_pos->vwap - _last_price >=stop_profit_loss && p_curr_pos->side==PositionSide_Short&&p_curr_pos->volume>0)||_update_time=="14:55:00";
			// LOG(INFO)<<"is closed:"<<is_close<<",last price:"<<_last_price<<",curr vwap:"<<p_curr_pos->vwap<<",curr side:"<<p_curr_pos->side<<",curr vol:"<<p_curr_pos->volume<<",updatetime:"<<_update_time;
			if(is_close){ //fpnl=((price-vwap)*volume*multiplier)
				LOG(INFO)<<"Get stop profit/loss signal";
				double _order_price = p_curr_pos->vwap;
				if(p_curr_pos->side==PositionSide_Long){
					_order_price += stop_profit_loss;
				}else if(p_curr_pos->side == PositionSide_Short){
					_order_price -= stop_profit_loss;
				}
				p_orderdata->symbol = p_curr_pos->symbol;
				p_orderdata->order_type = OrderType_Limit;
				p_orderdata->position_effect = PositionEffect_Close;
				p_orderdata->side = _side;
				p_orderdata->price = _order_price;
				p_orderdata->volume = p_curr_pos->volume;//todays volume
				p_orderdata->status = 1;
				return p_orderdata; //if this event trigger the stop profit and loss, then will not check the open signal REMARK
			}
		}
	}
	//FIXME REMOVE THE HARDCODE OF position limit(now hardcode the postion limit to 5), will change to margin level when the risk management is supported
	if(total_vol<5){ //if this event not trigger the stop profit and loss, and the current position is less than the pos limit, then check open signal 
		if(_mid-_last_price>1.0&& _spread>1.0){ //open long
			LOG(INFO)<<"Get long open signal, curr total vol:"<<total_vol;
			//FIXME HARDCODE exchange
			p_orderdata->symbol = "DCE."+_symbol;
			p_orderdata->order_type = OrderType_Market;
			p_orderdata->position_effect = PositionEffect_Open;
			p_orderdata->side = OrderSide_Buy;
			p_orderdata->price = 0.0;
			p_orderdata->volume = 1;//1 shot
			p_orderdata->status = 2;

		}else if (_last_price-_mid>1.0 &&_spread>1.0){//open short
			LOG(INFO)<<"Get short open signal";
			//FIXME HARDCODE exchange
			p_orderdata->symbol = "DCE."+_symbol;
			p_orderdata->order_type = OrderType_Market;
			p_orderdata->position_effect = PositionEffect_Open;
			p_orderdata->side = OrderSide_Sell;
			p_orderdata->price = 0.0;
			p_orderdata->volume = 1;//1 shot
			p_orderdata->status = 2;
		}
	}
	// LOG(INFO)<<"before return in get_signal"<<p_orderdata->status<<","<<p_orderdata->symbol<<","<<p_orderdata->side;

	//FIXME task_tag is not grarantee to be product id
	// std::string _exchange = get_exchange_id_order11(this->mode, this->task_tag); 

    // sample data from log:Recieve:eg2205,15:01:13,770,352685,4819,4819,4819,2,4820.85,48027.5,4819
    //Recieve:eg2205,14:59:33,279,351987,4819,4821,0,1,4818.71,48027.2,4819
	// LOG(INFO)<<"Recieve:"<<_symbol<<",update_time:"<<_update_time<<",update msecc:"<<_update_milsec<<",volume:"<<_volume
    // <<",last price:"<<_last_price<<",max:"<<_max<<",min:"<<_min<<",spread:"<<_spread<<",:mid:"<<_mid<<",vwap:"<<_vwap<<",slope:"<<_slope;
	return p_orderdata;
}