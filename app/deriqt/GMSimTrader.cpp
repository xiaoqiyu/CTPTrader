#include "GMSimTrader.h"

void SimTrader::init()
{
    LOG(INFO)<<"simtrade init-------------";
    // this->_task_thread = thread(&SimTrader::processTask, this);
}

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
        ExecRpt *task_data = new ExecRpt();
        *task_data = *rpt;
        task.task_data = task_data;
    }
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
    if (task->task_data)
    {
        ExecRpt *task_data = reinterpret_cast<ExecRpt *>(task->task_data);
        if (task_data->volume>0 && task_data->exec_type == ExecType_Trade){
            LOG(INFO)<<"Execution reports:trades, start update positions";
            update_positions(task_data);
            LOG(INFO) << "price: " << task_data->price << std::endl;
            LOG(INFO) << "volume: " << task_data->volume << std::endl;
            LOG(INFO) << "amount: " << task_data->amount << std::endl;
            LOG(INFO) << "commission: " << task_data->commission << std::endl;
            LOG(INFO) << "cost: " << task_data->cost << std::endl;
            LOG(INFO) << "created_at: " << task_data->created_at << std::endl;
        }
        
        /* //REMARK won't handle stop profit and loss here, all the orders will be triggered by tick, generated in order sigal 
        if (task_data->position_effect == PositionEffect_Open && task_data->volume > 0){//for the open position, will add the stop_profit and loss order automatically
            //FIXME  order volume for testing, only order with hardcode param, will add commission, and stop profit/stop loss settings
            double delta_price = 2; //by default: if current order is sell, then the next order is sell will higer(lower) limit price for stop profit(loss)
            int order_side = OrderSide_Buy; //by default: if current order is sell, then the close order side is sell
            if (task_data->side == OrderSide_Buy){
                order_side = OrderSide_Sell;
                delta_price = -delta_price;//if current order is buy, then the close order is sell
            }
            this->order_volume(task_data->symbol, task_data->volume,order_side, OrderType_Limit, PositionEffect_Close,task_data->price);
        }
        */
        //FIXME why double delete, where to delete?????
        // delete task_data;
    }
    if (task->task_error)
    {
        LOG(ERROR)<<"process execute error";
    }
}

void SimTrader::process_order_status(Task *task)
{
    LOG(INFO)<< "Process order status in gm trade----------------------------------";
    if (task->task_data)
    {
        Order *task_data = reinterpret_cast<Order *>(task->task_data);
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
    LOG(INFO)<<"in process task: ";
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
            this->process_order_status(&task);
        }
        case ONSIMEXECUTIONREPORT:
        {
            this->process_execution_report(&task);

        }
        }        
    }
}
























