#include "GMSimTrader.h"



void SimTrader::exit()
{
    // this->_active = false;
    this->_task_thread.join();
}
//关注委托状态变化
void SimTrader::on_order_status(Order *order)
{
    // LOG(INFO)<<"call back in order status:"<<order->symbol<<order->status<<order->ord_rej_reason<<order->ord_rej_reason_detail;
    Task task = Task();
    task.task_name = ONSIMORDERSTATUS;
    if (order)
    {
        Order *task_data = new Order();
        *task_data = *order;
        task.task_data = task_data;
    }
    if(order->status == OrderStatus_New){//TODO check this
        this->_task_queue.push(task);
    }
};

//关注执行回报, 如成交, 撤单拒绝等
void SimTrader::on_execution_report(ExecRpt *rpt)
{
    LOG(INFO)<<"[on_execution_report] call back in execution:"<<rpt->symbol<<std::endl;
    Task task = Task();
    task.task_name = ONSIMEXECUTIONREPORT;
    
    if(rpt)
    {
        ExecRpt *task_data = new ExecRpt();
        *task_data = *rpt;
        task.task_data = task_data;
    }
    LOG(INFO)<<"[on_execution_report] start push exe task to task queue";
    this->_task_queue.push(task);
}

void SimTrader::on_trade_data_connected()
{
    int ret = cancel_all_orders();
    LOG(INFO)<<"[on_trade_data_connected] return for cancel all orders=>"<<ret;
    init_positions(account_id);
    this->connected_ = true;
    LOG(INFO) << "[on_trade_data_connected] connected to server in connect callback...."<<this->connected_;
}

void SimTrader::on_trade_data_disconnected()
{
    this->connected_ = false;
    LOG(INFO) << "[on_trade_data_disconnected] disconnected to server....\n";
}

void SimTrader::on_account_status(AccountStatus *account_status)
{
    LOG(INFO) << "change of accounts : " << account_status->state << std::endl;
}

void SimTrader::process_execution_report(Task *task)
{
    LOG(INFO)<<"***********************Execution Reports************************************";
    if (task->task_data)
    {
        // std::cout<<"????????????????in process execute report:"<<task->task_data<<std::endl;
        ExecRpt *task_data = reinterpret_cast<ExecRpt *>(task->task_data);
        // std::cout<<"????????????????in process execute report:"<<task_data->volume<<","<<task_data->exec_type<< std::endl;
        // if(task_data->exec_type == ExecType_Unknown && task_data->volume==0){ //FIXME double check the handling of the unknown type, why has unknown type
            // 
            // int ret = cancel_all_orders();
            // REMARK: this will be reset in order callback
            // if (ret==0){
                // order_complete_ = true;
            // }
            // LOG(INFO)<<"Unknow exe type, ignore the callback, cancel order ret=>"<<ret<<"order_complete=>"<<order_complete_;
        // }
        if (task_data->volume>0 && task_data->exec_type == ExecType_Trade){
            // std::cout<<"???????????start process Execution report"<<std::endl;
            update_positions(task_data);
            LOG(INFO) << "order id=>"<<task_data->order_id;
            LOG(INFO) << "exe id=>"<<task_data->exec_id;
            LOG(INFO) << "price=>" << task_data->price;
            LOG(INFO) << "volume=>" << task_data->volume;
            LOG(INFO) << "amount=>" << task_data->amount;
            LOG(INFO) << "commission=>" << task_data->commission;
            LOG(INFO) << "cost=>" << task_data->cost;
            LOG(INFO) << "created_at=>" << task_data->created_at;
            LOG(INFO) << "position effect=>"<<task_data->position_effect;
            LOG(INFO) << "side=>"<<task_data->side;

            auto it_order = order_vol_map.find(task_data->order_id);
            long _order_vol = 0;
            if(it_order != order_vol_map.end()){
                _order_vol = it_order->second;
            }else{
                LOG(WARNING)<<"Order not exist for order id:"<<task_data->order_id;
            }
            auto it_exe = execute_vol_map.find(task_data->order_id);
            if(it_order != order_vol_map.end() && it_exe != execute_vol_map.end()){
                LOG(INFO)<<"Order id:"<<it_order->first<<",order volume:"<<it_order->second<<",acc exe volume:"<<it_exe->second;
                if(it_order->second == it_exe->second){
                    order_complete_ = true;
                    LOG(INFO)<<"in process execution reports:order completed, reset:"<<order_complete_<<",available:"<<available_<<",order vol:"<<it_order->second<<",exe acc vol:"<<it_exe->second;
                }
            }
        }
        
        //FIXME why double delete, where to delete?????
        // delete task_data;
    }
    if (task->task_error)
    {
        LOG(ERROR)<<"process execute error";
    }


    // order_complete_ = true;//REMARK if not completely executed, dnt reset order_completed and available
    available_ = true;
    // LOG(INFO)<<"reset order complete to true,order complete:"<<order_complete_<<",available:"<<available_;
	cond_.notify_all(); 
}

void SimTrader::process_order_status(Task *task)
{
    LOG(INFO)<< "**************************Order Reports***********************************";
    // std::vector<ptr_position> v_all_pos = get_positions();
    // for (auto it = v_all_pos.begin(); it != v_all_pos.end(); ++it){
        // ptr_position _tmp_pos = *it;
        // std::cout<<_tmp_pos->symbol<<",vol:"<<_tmp_pos->volume<<",available:"<<_tmp_pos->available<<",vwap:"<<_tmp_pos->vwap<<std::endl;
    // }
    // 
    if (task->task_data)
    {
        Order *task_data = reinterpret_cast<Order *>(task->task_data);
        // if(task_data->status == 1 && task_data->volume >0)
        if(task_data){
            update_orders(task_data);
            //FIXME status 全部等于 5？？？？canceled,check filled amout(如果vol 是0，则撤销) 
            if(task_data->status == OrderStatus_Canceled && task_data->filled_volume==0){

                order_complete_ = true;
                available_ = true;
                order_available_ = true;
                LOG(INFO)<<"?????reset order complete in order cancel,order complete:"<<order_complete_<<",available:"<<available_<<",order available:"<<order_available_;
	            cond_.notify_all(); 
                
            }
            LOG(INFO) << "symbol=> " << task_data->symbol;
            LOG(INFO) << "cl_ord_id=> " << task_data->cl_ord_id;
            LOG(INFO) << "order id=> "<<task_data->order_id;
            LOG(INFO) << "status=> " << task_data->status;
            LOG(INFO) << "side=> " << task_data->side;
            LOG(INFO) << "position effect=> " <<task_data->position_effect; 
            LOG(INFO) << "volume=> " << task_data->volume;
            LOG(INFO) << "filled_amount=> " << task_data->filled_amount;
            LOG(INFO) << "filled_commission=> " << task_data->filled_commission;
            LOG(INFO) << "filled_volume=> " << task_data->filled_volume;
            LOG(INFO) << "filled_vwap=> " << task_data->filled_vwap;
            LOG(INFO) << "created_at=> " << task_data->created_at;
            LOG(INFO) << "updated_at=> " << task_data->updated_at;
            
        }
        delete task_data;
    }
    if (task->task_error)
    {
        LOG(ERROR)<<"Process order error";
    }
}

void SimTrader::processTask(){
    // LOG(INFO)<<"Process task in gm simtrade:"<<this->_active<<","<<this->connected_;
    // while(this->_active && this->connected_)//FIXME check status
    LOG(INFO)<<"-----------------------------------in process task: ";
    while(true)
    {
        Task task = this->_task_queue.pop();
        LOG(INFO)<<"poped task:"<<task.task_name;
        switch (task.task_name)
        {
        case ONSIMCONNECTED:
        {
            this->connected_ = true;
            break;
        }
        case ONSIMDISCONNECTED:
        {
            this->connected_ = false;
            break;
        }
        case ONSIMORDERSTATUS:
        {
            this->process_order_status(&task);
        }
        case ONSIMEXECUTIONREPORT:
        {
            this->process_execution_report(&task);

        }
        }        
    }
}

void SimTrader::update_orders(ptr_order p_order){
    this->order_complete_ = false;
    unique_lock<mutex> mlock(mutex_);
    order_vol_map.insert(std::pair<std::string, int>(p_order->order_id, p_order->volume));
    for (auto it = all_orders.begin(); it != all_orders.end(); ++it){
        ptr_order _tmp = *it;
        if(strcmp(_tmp->order_id, p_order->order_id)==0){
            //TODO check whether to update other fields
            _tmp->status = p_order->status;
            _tmp->filled_volume = p_order->filled_volume;
            _tmp->filled_amount = p_order->filled_amount;
            _tmp->filled_vwap = p_order->filled_vwap;
            _tmp->filled_commission = p_order->filled_commission;
            _tmp->updated_at = p_order->updated_at;
            _tmp->target_percent = p_order->target_percent;
        }
    }
    this->order_available_ = true;
    mlock.unlock();     //释放锁
    cond_.notify_one(); //通知正在阻塞等待的线程
}

void SimTrader::update_positions(Order* order){
    this->available_ = false;
    unique_lock<mutex> mlock(mutex_);
    std::string order_symbol = order->symbol;
    // float exe_price = p_exe->price;
    
    long order_vol = order->volume;
    if(order->position_effect == PositionEffect_Close) order_vol = -order_vol;
    // all_positions = get_positions();
    for(auto it = all_positions.begin();it !=all_positions.end();++it){
        Position* _tmp=*it;
        std::cout<<_tmp->symbol<<",vol:"<<_tmp->volume<<",available:"<<_tmp->available<<",vwap:"<<_tmp->vwap<<std::endl;
    }
    LOG(INFO)<<"Start update positions,curr pos size:"<<all_positions.size();
    
    bool flag = false;
    if (this->all_positions.size()>0){//have positions now
        for(auto it=all_positions.begin(); it!=all_positions.end(); ++it){
            ptr_position p_curr_pos = *it;
            LOG(INFO)<<"current positions:"<<p_curr_pos->symbol<<",pos vwap:"<<p_curr_pos->vwap<<",pos vol:"<<p_curr_pos->available<<",pos side:"<<p_curr_pos->side;
            LOG_IF(WARNING, p_curr_pos->side == 0)<<"symbol:"<<p_curr_pos->symbol<<",vwap:"<<p_curr_pos->vwap<<",vol:"<<p_curr_pos->volume<<",available:"<<p_curr_pos->available;
            LOG(INFO)<<"to be added exe,check cond:order status:"<<order->status<<",symbol:"<<order->symbol<<",order side:"<<order->side<<",pos side:"<<p_curr_pos->symbol<<",pos side:"<<p_curr_pos->side;
            //代码一样，买卖相反且方向相反
            bool _is_update_pos = strcmp(p_curr_pos->symbol, order->symbol)==0 && p_curr_pos->side != order->side && order->position_effect==PositionEffect_Close;
            LOG(INFO)<<"check whether to update position available----------------:"<<_is_update_pos;
            if(_is_update_pos){ //position exists 
                LOG(INFO)<<"pos exist, and update position"<<"order type:"<<order->order_type<<",pos vol:"<<p_curr_pos->available<<",order vol:"<<order_vol;
                flag = true;
                p_curr_pos->available += order_vol;
                LOG(INFO)<<"After update position,available:"<<p_curr_pos->available;
            }
        }
    }
                                                
    this->available_ = true;
    mlock.unlock();     //释放锁
    cond_.notify_one(); //通知正在阻塞等待的线程
}

void SimTrader::update_positions(ExecRpt*p_exe){
    LOG(INFO)<<"*******************************START UPDATE POSITIONS:"<<p_exe->symbol<<",exe volume:"<<p_exe->volume<<",available:"<<available_<<",order_complete:"<<order_complete_;
    this->available_ = false;
    unique_lock<mutex> mlock(mutex_);
    std::string exe_symbol = p_exe->symbol;
    float exe_price = p_exe->price;
    
    // update execute vol by order id
    auto it  = execute_vol_map.find(p_exe->order_id);
    long updated_vol = p_exe->volume;
    if (it != execute_vol_map.end()){
        updated_vol += it->second;
        LOG(INFO)<<"[update_positions] Update exe acc vol by order id:"<<p_exe->order_id<<",before=>"<<it->second<<"exe vol=>"<<p_exe->volume<<"after=>"<<updated_vol;
        LOG(INFO)<<"---------- update map before insert=>"<<it->first<<",vol=>"<<updated_vol;
        it->second = updated_vol;
        // execute_vol_map.insert(std::pair<std::string, long>(it->first, updated_vol));
        auto it1 = execute_vol_map.find(p_exe->order_id);
        LOG(INFO)<<"--------------update map after insert=>"<<it1->first<<",vol=>"<<it1->second<<",order id:"<<p_exe->order_id;
    }else{
        LOG(INFO)<<"--------------init map before insert=>"<<p_exe->order_id<<",vol=>"<<updated_vol;
        execute_vol_map.insert(std::pair<std::string, long>(p_exe->order_id, updated_vol));
        LOG(INFO)<<"[update_positions] Add exe acc vol by order id:"<<p_exe->order_id<<",exe vol=>"<<p_exe->volume<<",updated vol:"<<updated_vol;
        auto it2 = execute_vol_map.find(p_exe->order_id);
        LOG(INFO)<<"--------------init map after insert=>"<<it2->first<<"vol=>"<<it2->second<<",order id:"<<p_exe->order_id;
    }


    long exe_vol = p_exe->volume;//open 
    if(p_exe->position_effect == PositionEffect_Close) exe_vol = -exe_vol;
    LOG(INFO)<<"[update_positions] Start update positions,curr pos size:"<<all_positions.size();
    bool flag = false;
    if (this->all_positions.size()>0){//have positions now
        for(auto it=all_positions.begin(); it!=all_positions.end(); ++it){
            ptr_position p_curr_pos = *it;
            LOG(INFO)<<"current positions:"<<p_curr_pos->symbol<<",pos vwap:"<<p_curr_pos->vwap<<",pos vol:"<<p_curr_pos->volume<<",pos side:"<<p_curr_pos->side;
            LOG(INFO)<<"to be added exe,check cond---------------------:"<<p_exe->symbol<<",exe side:"<<p_exe->side<<",pos side:"<<p_curr_pos->side;
            //代码一样，同时多空方向一致且为开或者多空方向相反且为平
            bool _is_pos_exist = strcmp(p_curr_pos->symbol, p_exe->symbol)==0 && (p_curr_pos->side == p_exe->side && p_exe->position_effect==PositionEffect_Open || p_curr_pos->side != p_exe->side && p_exe->position_effect==PositionEffect_Close);
            LOG(INFO)<<"check whether to merge position----------------:"<<_is_pos_exist;
            if(_is_pos_exist){ //position exists 
                LOG(INFO)<<"pos exist, and update position"<<"exe type:"<<p_exe->exec_type<<",pos vol:"<<p_curr_pos->volume<<",exe vol:"<<exe_vol<<",pos available:"<<p_curr_pos->available;
                flag = true;
                if (p_curr_pos->volume+exe_vol == 0){
                    p_curr_pos->vwap = 0.0;
                }else{
                    p_curr_pos->vwap = (p_curr_pos->vwap*p_curr_pos->volume + exe_price*exe_vol)/(p_curr_pos->volume+exe_vol);
                }
                p_curr_pos->volume += exe_vol;
                p_curr_pos->available = p_curr_pos->volume;

                //TODO add other value updates
                LOG(INFO)<<"[update_positions] After update position,curr vol=>"<<p_curr_pos->volume<<",available=>"<<p_curr_pos->available;
            }
        }
    }
    
    if(!flag){
        LOG(INFO)<<"[update_positions] symbol not exist, start create new position for open order,flag=>"<<flag<<"all pos size=>"<<all_positions.size();
        ptr_position p_pos = new Position();
        strcpy(p_pos->symbol, exe_symbol.c_str());
        p_pos->vwap = exe_price;
        p_pos->volume = p_exe->volume;
        p_pos->volume_today = p_exe->volume;
        p_pos->side = p_exe->side;
        //TODO add other value updates 
        all_positions.push_back(p_pos);
        LOG(INFO)<<"[update_positions] after add new transaction,all position size=>"<<all_positions.size()<<",curr pos vol=>"<<p_pos->volume;
    }
    this->available_ = true;
    LOG(INFO)<<"*****************************[update_positions] complete update position, avaible_=>"<<available_;
    mlock.unlock();     //释放锁
    cond_.notify_all(); //通知正在阻塞等待的线程
    
}

std::vector<ptr_position> SimTrader::get_positions(){
    // std::cout<<"???????????in get positions:order_complete=>"<<order_complete_<<"available_=>"<<available_<<std::endl;
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return order_complete_&&available_ ; //FIXME double check
    }); //等待条件变量通知
    // init_positions(account_id);
    return this->all_positions;
}

std::vector<ptr_order> SimTrader::get_all_orders(){
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return order_available_ ; //FIXME double check
    }); //等待条件变量通知
    return this->all_orders;
}

std::vector<ptr_position> SimTrader::get_positions(const std::string& instrument_id){
    LOG(INFO)<<"in get positions for symbol,order_complete:"<<order_complete_<<",availabel: "<<available_;
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return order_complete_&&available_;//FIXME double check
    }); //等待条件变量通知

    // init_positions(account_id);
    LOG(INFO)<<"In get positions, after cond wait, order complete:"<<order_complete_<<",available:"<<available_;
    std::vector<ptr_position> ret_pos;
    for(auto it = all_positions.begin(); it!=all_positions.end();++it){
        ptr_position _tmp = *it;
        if(_tmp->symbol == instrument_id && _tmp->volume >0) ret_pos.push_back(_tmp);
    }
    return ret_pos;
}
int SimTrader::get_position_details(const std::string& account_id)
{
    gmtrade::DataArray<Position> *ps = this->get_position(account_id.c_str());
    if (ps->status()==0){
        this->p_pos = ps;
        return 0;
    }
    return -1; // not get correct results
}
std::vector<ptr_position> SimTrader::get_position_details(const std::string& account_id, const std::string& instrument_id){
    std::vector<ptr_position> ret_pos;
    if (this->get_position_details(account_id))
    {
        for (int i = 0; i<this->p_pos->count(); i++)
        {
            Position &p = this->p_pos->at(i);
            if(p.symbol == instrument_id){
                 ret_pos.push_back(&p);
            }
        }
    }
    return ret_pos;
}

Order* SimTrader::insert_order(CThostFtdcInputOrderField *p_order_field_){
    order_complete_ = false;
    Order _order;
    int order_side;
    int order_type = OrderType_Limit;
    int position_effect;
    char  open_flag [1];
    open_flag[0] = THOST_FTDC_OF_Open;
    char close_flag[1];
    close_flag[1] = THOST_FTDC_OF_Close;
    //set side in CTP order struct to simtrade struct
    if(p_order_field_->Direction ==  THOST_FTDC_D_Buy){
        order_side = OrderSide_Buy;
    }else if(p_order_field_->Direction == THOST_FTDC_D_Sell)
    {
        order_side = OrderSide_Sell;
    }
    if(strcmp(p_order_field_->CombOffsetFlag, open_flag) == 0){
        position_effect = PositionEffect_Open;
    }else if (strcmp(p_order_field_->CombOffsetFlag,close_flag)==0){
        position_effect = PositionEffect_Close;
    }
    
    _order = order_volume(p_order_field_->InstrumentID, p_order_field_->VolumeTotalOriginal,
    order_side, order_type,position_effect,p_order_field_->LimitPrice, account_id.c_str());
    unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return order_complete_;
	}); 	
    
    Order* p_ret = &_order;
    LOG(INFO)<<"Order complete:order symbol:"<<p_ret->symbol<<",status:"<<p_ret->status<<",filled vol:"<<p_ret->filled_volume;
    return p_ret;
}

Order* SimTrader::insert_order(OrderData * p_orderdata){
    order_complete_ = false;
    Order _order;
    LOG(INFO)<<"insert order in simtrade:symbol:"<<p_orderdata->symbol<<",side:"<<p_orderdata->side;
    _order = order_volume(p_orderdata->symbol.c_str(), p_orderdata->volume,p_orderdata->side, p_orderdata->order_type,p_orderdata->position_effect, p_orderdata->price, account_id.c_str());
    LOG(INFO)<<"Get order status:"<<_order.status<<",rej:"<<_order.ord_rej_reason<<",rej details:"<<_order.ord_rej_reason_detail;
    unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return order_complete_;
	}); 	
    
    Order* p_ret = &_order;
    LOG(INFO)<<"Order complete:"<<order_complete_<<",order symbol:"<<p_ret->symbol<<",status:"<<p_ret->status<<",side:"<<p_ret->side<<",position effect:"<<p_ret->position_effect;
    return p_ret;
}

int SimTrader::cancel_all_orders(){
    int ret = order_cancel_all();
    LOG(INFO)<<"[cancel_all_orders] returns=>"<<ret;
    // int ret;
    // std::cout<<account_id<<std::endl;
    // gmtrade::DataArray<Order>* ret_order = get_unfinished_orders(account_id.c_str());
    // std::cout<<"unfinished order cnt is:"<<ret_order->count()<<std::endl;
    // if(ret_order->status()==0){
        // for(int i=0; i<ret_order->count();++i){
            // Order &_tmp = ret_order->at(i);
            // std::cout<<"cancel order:"<<_tmp.order_id<<std::endl;
            // ret = order_cancel(_tmp.order_id, account_id.c_str());
            // std::cout<<"------------ret is:"<<ret;
        // }
        // ret_order->release();
    // }
    sleep(3);
    return ret;
}

/*
监控账户的风险度和订单/持仓状况
if 到达收盘时间：
    - 撤单（未结委托）
    - 平仓（不暴露隔夜风险）
else：
    判断是否有超时平仓的需求，拿到现订单，看update 时间和现在间隔，超过一定时间则平仓
    sleep(xx)
else:
    判断是否止盈止损，拿到持仓，如果有触发止盈止损的订单，则调用止盈止损
else:
    风险度，保证金等其他监控指标
*/
int SimTrader::risk_monitor(RiskInputData* p_risk_input, StrategyConfig* p_strategy_conf){
    LOG(INFO)<<"[risk_monitor] Start risk monitor:connected_=>"<<connected_;
    while(connected_){
        std::time_t now_time = std::time(nullptr);
        tm *ltm = localtime(&now_time);
        if(ltm->tm_hour == 14 && ltm->tm_min == 55){//收盘撤销订单
            LOG(INFO)<<"[risk_monitor] market closed, close all positions";
            order_cancel_all();
            order_close_all();
        }else{
            //超时撤销委托
            gmtrade::DataArray<Order>* ret_order = get_unfinished_orders(account_id.c_str());
            std::cout<<"[risk_monitor] unfinished order cnt is:"<<ret_order->count()<<std::endl;
            if(ret_order->status()==0){
                for(int i=0; i<ret_order->count();++i){
                    Order &_tmp = ret_order->at(i);
                    std::time_t order_delay = now_time - _tmp.updated_at;
                    int ret;
                    if(order_delay > p_strategy_conf->cancel_order_delay){
                        ret = cancel_all_orders();//FIXME should call order_cancle, but order_cancel has some issue
                        // ret = order_cancel(_tmp.order_id, account_id.c_str());
                        sleep(5);
                        LOG(INFO)<<"[risk_monitor] cancel order for order delay=>"<<order_delay<<"cancel order return=>"<<ret<<"cancel order id=>"<<_tmp.order_id<<"order vol=>"<<_tmp.volume;
                    }
                }
            ret_order->release();
            }
            double _last_price = p_risk_input->last_price;
            //止盈止损
            std::vector<ptr_position> ret_all_pos = get_positions();
            for(auto it = ret_all_pos.begin(); it != ret_all_pos.end(); ++it){
                ptr_position  _cur_pos = *it;
                double stop_profit_bc = p_strategy_conf->stop_profit;
                double stop_loss_bc = p_strategy_conf->stop_loss;
                bool stop_profit = (_cur_pos->side=PositionSide_Long && _last_price-_cur_pos->vwap >stop_profit_bc) || (_cur_pos->side=PositionSide_Short && _last_price-_cur_pos->vwap<-stop_profit_bc);
                bool stop_loss = (_cur_pos->side=PositionSide_Long && _last_price-_cur_pos->vwap <-stop_loss_bc) || (_cur_pos->side=PositionSide_Short && _last_price-_cur_pos->vwap>stop_loss_bc);
                // if(stop_profit || stop_loss)
                OrderData* p_order = new OrderData();
                p_order->order_type = OrderType_Limit;
                p_order->volume = _cur_pos->volume;
                p_order->position_effect = PositionEffect_Close;
                p_order->symbol = p_risk_input->symbol;
                if(_cur_pos->side == PositionSide_Long && stop_profit){//long position and stop profit
                    p_order->side = OrderSide_Sell;
                    p_order->price = _cur_pos->vwap + stop_profit_bc;
                }else if(_cur_pos->side == PositionSide_Long && stop_loss){
                    p_order->side = OrderSide_Sell;
                    p_order->price = _cur_pos->vwap - stop_loss_bc;
                }else if(_cur_pos->side == PositionSide_Short && stop_profit){
                    p_order->side = OrderSide_Buy;
                    p_order->price = _cur_pos->vwap - stop_profit_bc;
                }else if(_cur_pos->side == PositionSide_Short && stop_loss){
                    p_order->side = OrderSide_Buy;
                    p_order->price = _cur_pos->vwap + stop_loss_bc;
                }else{
                    LOG(WARNING)<<"[risk_monitor] position invalid:"<<"position side=>"<<_cur_pos->side<<",stop profit=>"<<stop_profit<<",stop loss=>"<<stop_loss;
                }
                if(stop_profit || stop_loss){
                    LOG(INFO) <<"[risk_monitor] insert order for stop_profit or loss,stop_profit=>"<<stop_profit<<",stop loss=>"<<stop_loss;
                    Order* p_order_ret = new Order();
                    p_order_ret = insert_order(p_order);
                    LOG(INFO)<<"[risk_monitor] order return status=>"<<p_order_ret->status<<",order rej reason=>"<<p_order_ret->ord_rej_reason<<",rej details=>"<<p_order_ret->ord_rej_reason_detail;
                }
            }
            //add other risk monitor conditions
        }
    }
    
    return 0;
}