#include "GMSimTrader.h"

void SimTrader::init()
{
    this->_task_thread = thread(&SimTrader::processTask, this);
}

void SimTrader::exit()
{
    this->_active = true;
    this->_task_thread.join();
}
//关注委托状态变化
void SimTrader::on_order_status(Order *order)
{
    LOG(INFO)<<"call back in order status:"<<order->symbol<<std::endl;
    Task task = Task();
    task.task_name = ONSIMORDERSTATUS;
    if (order)
    {
        Order *task_data = new Order();
        *task_data = *order;
        task.task_data = task_data;
        std::cout<<task_data->order_id<<",status:"<<task_data->status<<",reason:"<<task_data->ord_rej_reason<<",details:"<<task_data->ord_rej_reason_detail<<std::endl;
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
    LOG(INFO) << "connected to server in connect callback....\n";
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
        LOG(INFO) << "price: " << task_data->price << std::endl;
        LOG(INFO) << "volume: " << task_data->volume << std::endl;
        LOG(INFO) << "amount: " << task_data->amount << std::endl;
        LOG(INFO) << "commission: " << task_data->commission << std::endl;
        LOG(INFO) << "cost: " << task_data->cost << std::endl;
        LOG(INFO) << "created_at: " << task_data->created_at << std::endl;
        delete task_data;
    }
    if (task->task_error)
    {
        // CThostFtdcRspInfoField *task_error = reinterpret_cast<CThostFtdcRspInfoField *>(task->task_error);
        // LOG_IF(FATAL, task_error->ErrorID != 0) << "Error processRspAuthenticate->" << task_error->ErrorID << "," << task_error->ErrorMsg;
        // delete task_error;
    }
}

void SimTrader::process_order_status(Task *task)
{
    if (task->task_data)
    {
        Order *task_data = reinterpret_cast<Order *>(task->task_data);
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
        // CThostFtdcRspInfoField *task_error = reinterpret_cast<CThostFtdcRspInfoField *>(task->task_error);
        // LOG_IF(FATAL, task_error->ErrorID != 0) << "Error processRspAuthenticate->" << task_error->ErrorID << "," << task_error->ErrorMsg;
        // delete task_error;
    }
}

void SimTrader::processTask()
{
    LOG(INFO)<<"Start process order task\n";
    try
    {
        while (this->_active && this->connected_)
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
    catch (const TerminatedError &)
    {
    }
}