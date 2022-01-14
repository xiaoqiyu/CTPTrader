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
    this->_task_queue.push(task);
};

//关注执行回报, 如成交, 撤单拒绝等
void SimTrader::on_execution_report(ExecRpt *rpt)
{
    LOG(INFO)<<"call back in execution:"<<rpt->symbol<<std::endl;
    Task task = Task();
    task.task_name = ONSIMEXECUTIONREPORT;
    if(rpt)
    {
        std::cout<<"push exe report to queue"<<std::endl;
        ExecRpt *task_data = new ExecRpt();
        *task_data = *rpt;
        task.task_data = task_data;
        std::cout<<"new exe task complete"<<std::endl;
    }
    LOG(INFO)<<"start push exe task to task queue";
    this->_task_queue.push(task);
}

void SimTrader::on_trade_data_connected()
{
    this->connected_ = true;
    LOG(INFO) << "connected to server in connect callback...."<<this->connected_;
}

void SimTrader::on_trade_data_disconnected()
{
    this->connected_ = false;
    LOG(INFO) << "disconnected to server....\n";
}

void SimTrader::on_account_status(AccountStatus *account_status)
{
    LOG(INFO) << "change of accounts : " << account_status->state << std::endl;
}

void SimTrader::process_execution_report(Task *task)
{
    LOG(INFO)<<"Execution reports:trades, start update positions";
    if (task->task_data)
    {
        ExecRpt *task_data = reinterpret_cast<ExecRpt *>(task->task_data);
        if (task_data->volume>0 && task_data->exec_type == ExecType_Trade){
            
            update_positions(task_data);
            LOG(INFO) << "price: " << task_data->price << std::endl;
            LOG(INFO) << "volume: " << task_data->volume << std::endl;
            LOG(INFO) << "amount: " << task_data->amount << std::endl;
            LOG(INFO) << "commission: " << task_data->commission << std::endl;
            LOG(INFO) << "cost: " << task_data->cost << std::endl;
            LOG(INFO) << "created_at: " << task_data->created_at << std::endl;
        }
        
        //FIXME why double delete, where to delete?????
        // delete task_data;
    }
    if (task->task_error)
    {
        LOG(ERROR)<<"process execute error";
    }
    LOG(INFO)<<"Order complete:symbol";
    order_complete_ = true;
    available_ = true;
	cond_.notify_all(); 
}

void SimTrader::process_order_status(Task *task)
{
    LOG(INFO)<< "Process order status in gm trade----------------------------------";
    std::vector<ptr_position> v_all_pos = get_positions();
    // for (auto it = v_all_pos.begin(); it != v_all_pos.end(); ++it){
        // ptr_position _tmp_pos = *it;
        // std::cout<<_tmp_pos->symbol<<",vol:"<<_tmp_pos->volume<<",available:"<<_tmp_pos->available<<",vwap:"<<_tmp_pos->vwap<<std::endl;
    // }
    // 
    if (task->task_data)
    {
        Order *task_data = reinterpret_cast<Order *>(task->task_data);
        if(task_data->status == 1 && task_data->volume >0){
            // update_positions(task_data);//TODO check whether have to update positions here
            LOG(INFO)<<"Order reports";
            LOG(INFO) << "symbol: " << task_data->symbol << std::endl;
            LOG(INFO) << "cl_ord_id" << task_data->cl_ord_id << std::endl;
            LOG(INFO) << "status: " << task_data->status << std::endl;
            LOG(INFO) << "volume: " << task_data->volume << std::endl;
            LOG(INFO) << "filled_amount: " << task_data->filled_amount << std::endl;
            LOG(INFO) << "filled_commission: " << task_data->filled_commission << std::endl;
            LOG(INFO) << "filled_volume: " << task_data->filled_volume << std::endl;
            LOG(INFO) << "filled_vwap: " << task_data->filled_vwap << std::endl;
            LOG(INFO) << "created_at: " << task_data->created_at << std::endl;
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
            std::cout<<"case: order report"<<std::endl;
            this->process_order_status(&task);
        }
        case ONSIMEXECUTIONREPORT:
        {
            std::cout<<"case: execution report"<<std::endl;
            this->process_execution_report(&task);

        }
        }        
    }
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
    this->available_ = false;
    unique_lock<mutex> mlock(mutex_);
    std::string exe_symbol = p_exe->symbol;
    float exe_price = p_exe->price;
    
    long exe_vol = p_exe->volume;//open 
    if(p_exe->position_effect == PositionEffect_Close) exe_vol = -exe_vol;
    LOG(INFO)<<"Start update positions,curr pos size:"<<all_positions.size();
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
                LOG(INFO)<<"After update position,vol:"<<p_curr_pos->volume<<",available:"<<p_curr_pos->available;
            }
        }
    }
    
    if(!flag){
        LOG(INFO)<<"symbol not exist, start create new position for open order,flag:"<<flag<<"pos size:"<<all_positions.size();
        LOG(INFO)<<"EXE POS:"<<exe_symbol;
        ptr_position p_pos = new Position();
        strcpy(p_pos->symbol, exe_symbol.c_str());
        p_pos->vwap = exe_price;
        p_pos->volume = p_exe->volume;
        p_pos->volume_today = p_exe->volume;
        p_pos->side = p_exe->side;
        //TODO add other value updates 
        all_positions.push_back(p_pos);
        LOG(INFO)<<"after add new transaction,all position size:"<<all_positions.size()<<",curr pos vol:"<<p_pos->volume<< std::endl;
    }
    this->available_ = true;
    mlock.unlock();     //释放锁
    cond_.notify_one(); //通知正在阻塞等待的线程
    
}

std::vector<ptr_position> SimTrader::get_positions(){
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return order_complete_&&available_ ; //FIXME double check
    }); //等待条件变量通知
    init_positions(account_id);
    return this->all_positions;
}
std::vector<ptr_position> SimTrader::get_positions(const std::string& instrument_id){
    unique_lock<mutex> mlock(mutex_);
    cond_.wait(mlock, [&]() {
        return order_complete_&&available_;//FIXME double check
    }); //等待条件变量通知

    // init_positions(account_id);
    LOG(INFO)<<"In get positions, after cond wait";
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
    _order = order_volume(p_orderdata->symbol.c_str(), p_orderdata->volume,p_orderdata->side, OrderType_Limit,p_orderdata->position_effect, p_orderdata->price, account_id.c_str());
    unique_lock<mutex> mlock(mutex_);
	cond_.wait(mlock, [&]() {
		return order_complete_;
	}); 	
    
    Order* p_ret = &_order;
    LOG(INFO)<<"Order complete:order symbol:"<<p_ret->symbol<<",status:"<<p_ret->status<<",filled vol:"<<p_ret->filled_volume;
    return p_ret;
}