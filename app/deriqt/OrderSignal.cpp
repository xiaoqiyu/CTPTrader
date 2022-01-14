#include "OrderSignal.h"
#include <vector>

OrderData* OrderSignal::get_signal(const std::vector<std::string>&v_rev){
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

	// LOG(INFO)<<"Recieve:"<<_symbol<<",update_time:"<<_update_time<<",update msecc:"<<_update_milsec<<",volume:"<<_volume
    // <<",last price:"<<_last_price<<",max:"<<_max<<",min:"<<_min<<",spread:"<<_spread<<",:mid:"<<_mid<<",vwap:"<<_vwap<<",slope:"<<_slope;
	// long long total_vol = 0;
	bool _is_long = false;
	bool _is_short = false;
	_is_long = _mid-_last_price>1.0&& _spread>1.0; // get long signal, model and factor apply here
	_is_short = _last_price-_mid>1.0 &&_spread>1.0; // get short signal, model and factor apply here

	std::string symbol = "DCE."+ _symbol;
	
	if(_is_long){ //get long signal
		// LOG(INFO)<<"long signal";
		p_orderdata->symbol = "DCE."+_symbol;//FIXME fix exchange hardcode
		p_orderdata->order_type = OrderType_Limit;
		p_orderdata->position_effect = PositionEffect_Open;
		p_orderdata->side = OrderSide_Buy;
		p_orderdata->price = _last_price;
		p_orderdata->volume = 1;
		p_orderdata->status = LONG_SIGNAL;	
		return p_orderdata; 
		
	}else if (_is_short){ //get short signal
		// LOG(INFO)<<"short signal"; 
		p_orderdata->symbol = "DCE."+_symbol;//FIXME fix exchange hardcode
		p_orderdata->order_type = OrderType_Limit;
		p_orderdata->position_effect = PositionEffect_Open;
		p_orderdata->side = OrderSide_Sell;
		p_orderdata->price = _last_price;
		p_orderdata->volume = 1;
		p_orderdata->status = SHORT_SIGNAL;
		return p_orderdata; 
	}else{//no signal, check whether to stop loss
		p_orderdata->status = NO_SIGNAL;	
		p_orderdata->price = _last_price;
	}


	return p_orderdata;
}

OrderData* OrderSignal::get_signal_v0(const std::vector<std::string>&v_rev, int trading_mode, std::vector<Position *> v_positions,StrategyConfig *p_strategy_config, int order_limit){
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
	bool _is_long = false;
	bool _is_short = false;
	std::cout<<_mid<<","<<_last_price;
	// _is_long = _mid - _last_price > 0.01;
	_is_long = _mid-_last_price>1.0&& _spread>1.0; // get long signal, model and factor apply here
	_is_short = _last_price-_mid>1.0 &&_spread>1.0; // get short signal, model and factor apply here

	std::cout<<"check signal"<<std::endl;

	if(_is_long){ //get long signal
		LOG(INFO)<<"long signal,order vol available:"<<order_limit;
		if(v_positions.size() == 0){
			p_orderdata->symbol = "DCE."+_symbol;
			p_orderdata->order_type = OrderType_Market;
			p_orderdata->position_effect = PositionEffect_Open;
			p_orderdata->side = OrderSide_Buy;
			p_orderdata->price = 0.0;
			p_orderdata->volume = order_limit;
			p_orderdata->status = 2;
			return p_orderdata; 
		}
		for(auto it=v_positions.begin(); it!=v_positions.end();++it){
			int _side = PositionSide_Long;
			Position *p_curr_pos = *it;
			if(p_curr_pos->side == PositionSide_Short){ // currt short position
				LOG(INFO)<<"Ignore long signal when holding short positions"; //FIXME improved according to order_type
			}else{ //curr long positions, open long position for the remaining avalable shots
				p_orderdata->symbol = p_curr_pos->symbol;
				p_orderdata->order_type = OrderType_Market;
				p_orderdata->position_effect = PositionEffect_Open;
				p_orderdata->side = OrderSide_Buy;
				p_orderdata->price = 0.0;
				p_orderdata->volume = order_limit;
				p_orderdata->status = 2;
				return p_orderdata; 
			}
		}

	}else if (_is_short){ //get short signal
		LOG(INFO)<<"short signal,order vol available:"<<order_limit;
		if(v_positions.size() == 0){
			p_orderdata->symbol = "DCE."+_symbol;
			p_orderdata->order_type = OrderType_Market;
			p_orderdata->position_effect = PositionEffect_Open;
			p_orderdata->side = OrderSide_Sell;
			p_orderdata->price = 0.0;
			p_orderdata->volume = order_limit;
			p_orderdata->status = 2;
			return p_orderdata; 
		}
		for(auto it=v_positions.begin(); it!=v_positions.end();++it){
			int _side = PositionSide_Long;
			Position *p_curr_pos = *it;
			if(p_curr_pos->side == PositionSide_Long){ // currt long  position
				LOG(INFO)<<"Ignore short positions when holding long positions"; //FIXME improved according to order_type
			}else{ //curr short positions, open long position for the remaining avalable shots
				p_orderdata->symbol = p_curr_pos->symbol;
				p_orderdata->order_type = OrderType_Market;
				p_orderdata->position_effect = PositionEffect_Open;
				p_orderdata->side = OrderSide_Sell;
				p_orderdata->price = 0.0;
				p_orderdata->volume = order_limit;
				p_orderdata->status = 2;
				return p_orderdata; 
			}
		}
		

	}else{ //no signal, check stop profit and loss
		// LOG(INFO)<<"no signal";
		for(auto it=v_positions.begin(); it!=v_positions.end();++it){
			// LOG(INFO)<<"check stop profit and loss for current:";
			int _side = PositionSide_Long;
			bool _is_close;
			Position *p_curr_pos = *it;
			std::cout<<"available:"<<p_curr_pos->available<<std::endl;
			if (p_curr_pos->available <=0 || p_curr_pos->volume <=0 || p_curr_pos->vwap<=0) continue;
			double _limit_price;
			bool _is_stop_profit = false;
			bool _is_stop_loss = false;
			if(p_curr_pos->side == PositionSide_Long){
				_side = PositionSide_Short;
				_is_stop_profit = _last_price-p_curr_pos->vwap >= p_strategy_config->stop_profit;
				_is_stop_loss = _last_price - p_curr_pos->vwap <= -p_strategy_config->stop_loss;
				LOG(INFO)<<"Check close long,last_price:"<<_last_price<<",vwap:"<<p_curr_pos->vwap<<",stop_profit:"<<p_strategy_config->stop_profit<<",pos availabe:"<<p_curr_pos->available<<",pos vol:"<<p_curr_pos->volume;
				LOG(INFO)<<"stop loss:"<<p_strategy_config->stop_loss<<",is stop profit:"<<_is_stop_profit<<"is_stop_loss:"<<_is_stop_loss;
				if (_is_stop_profit){
					_limit_price =  p_curr_pos->vwap + p_strategy_config->stop_profit; //stop profit limit price
				}else if(_is_stop_loss){
					_limit_price = p_curr_pos->vwap - p_strategy_config->stop_loss;
				}
			}else{
				_side = PositionSide_Long;
				_is_stop_profit = p_curr_pos->vwap - _last_price >= p_strategy_config->stop_profit;
				_is_stop_loss = p_curr_pos->vwap - _last_price <= -p_strategy_config->stop_loss;
				LOG(INFO)<<"Check close short,last_price:"<<_last_price<<",vwap:"<<p_curr_pos->vwap<<",stop_profit:"<<p_strategy_config->stop_profit;
				LOG(INFO)<<"stop loss:"<<p_strategy_config->stop_loss<<",is stop profit:"<<_is_stop_profit<<"is_stop_loss:"<<_is_stop_loss;
				if (_is_stop_profit){
					_limit_price =  p_curr_pos->vwap - p_strategy_config->stop_profit; //stop profit limit price
				}else if(_is_stop_loss){
					_limit_price = p_curr_pos->vwap + p_strategy_config->stop_loss;
				}
			}

			if(_is_stop_profit || _is_stop_loss){
				p_orderdata->symbol = p_curr_pos->symbol;
				p_orderdata->order_type = OrderType_Stop;
				p_orderdata->position_effect = PositionEffect_Close;
				p_orderdata->side = _side;
				p_orderdata->price = _limit_price;
				p_orderdata->volume = p_curr_pos->volume;//todays volume
				p_orderdata->status = 1;
				return p_orderdata; //if this event trigger the stop profit and loss, then will not check the open signal REMARK
			}	
		}
	}
	// LOG(INFO)<<"Recieve:"<<_symbol<<",update_time:"<<_update_time<<",update msecc:"<<_update_milsec<<",volume:"<<_volume
    // <<",last price:"<<_last_price<<",max:"<<_max<<",min:"<<_min<<",spread:"<<_spread<<",:mid:"<<_mid<<",vwap:"<<_vwap<<",slope:"<<_slope;
	return p_orderdata;
}