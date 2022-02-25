#pragma once
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <codecvt>
#include <condition_variable>
#include <locale>
#include <vector>
#include <unordered_map>
#include "define.h"
#include "gmtrade.h"
#include "ThostFtdcUserApiStruct.h"
#include <boost/thread/concurrent_queues/sync_queue.hpp>

using namespace std;

//任务结构体
struct Task
{
    int task_name;    //回调函数名称对应的常量
    void *task_data;  //数据指针
    void *task_error; //错误指针
    int task_id;      //请求id
    bool task_last;   //是否为最后返回
    Task(): task_name(0), task_data(NULL), task_error(NULL), task_id(0), task_last(false){};
    ~Task(){
        if(!task_data){
            
        }
    };
};

struct DataField
{
    int data_type; //数据类别
    void *_data; //数据指针
    void *error; //错误指针
};

class TerminatedError : std::exception
{
};

class TaskQueue
{
private:
    queue<Task> queue_;       //标准库队列
    // boost::sync_queue<Task> queue_;
    mutex mutex_;             //互斥锁
    condition_variable cond_; //条件变量
    bool _terminate = false;

public:
    //存入新的任务
    void push(const Task &task)
    {
        // std::cout<<"push task:"<<task.task_name<<std::endl;
        unique_lock<mutex> mlock(mutex_);
        queue_.push(task);  //向队列中存入数据
        mlock.unlock();     //释放锁
        cond_.notify_one(); //通知正在阻塞等待的线程
    }

    //取出老的任务
    Task pop()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() || _terminate;
        }); //等待条件变量通知
        if (_terminate)
            throw TerminatedError();
        Task task = queue_.front(); //获取队列中的最后一个任务
        queue_.pop();               //删除该任务
        // std::cout<<"poped task:"<<task.task_name<<std::endl;
        return task;                //返回该任务
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //通知正在阻塞等待的线程
    }
};

class DataQueue
{
private:
    queue<DataField> queue_;       //标准库队列
    // boost::sync_queue<DataField> queue_;
    mutex mutex_;             //互斥锁
    condition_variable cond_; //条件变量
    bool _terminate = false;

public:
    DataQueue(){};
    ~DataQueue(){};
    //存入新的数据
    void push(const DataField &data)
    {
        unique_lock<mutex> mlock(mutex_);
        queue_.push(data);  //向队列中存入数据
        mlock.unlock();     //释放锁
        cond_.notify_all(); //通知正在阻塞等待的线程
    }

    //取出老的任务
    DataField pop()
    {
        
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() ;
        }); //等待条件变量通知
        if (_terminate)
            throw TerminatedError();
        DataField data = queue_.front(); //获取队列中的最后一个数据
        queue_.pop();               //删除该数据
        return data;                //返回该数据
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //通知正在阻塞等待的线程
    }
};



//将GBK编码的字符串转换为UTF8
inline string toUtf(const string &gb2312)
{
#ifdef _MSC_VER
    const static locale loc("zh-CN");
#else
    const static locale loc("zh_CN.GB18030");
#endif

    vector<wchar_t> wstr(gb2312.size());
    wchar_t *wstrEnd = nullptr;
    const char *gbEnd = nullptr;
    mbstate_t state = {};
    int res = use_facet<codecvt<wchar_t, char, mbstate_t>>(loc).in(state,
                                                                   gb2312.data(), gb2312.data() + gb2312.size(), gbEnd,
                                                                   wstr.data(), wstr.data() + wstr.size(), wstrEnd);

    if (codecvt_base::ok == res)
    {
        wstring_convert<codecvt_utf8<wchar_t>> cutf8;
        return cutf8.to_bytes(wstring(wstr.data(), wstrEnd));
    }

    return string();
}

typedef struct{
    double stop_profit = 50;//real money, not pct，每笔委托的止盈设置，单位：元；
    double stop_loss = 50;//real money, not pct，每笔委托的止损设置，单位：元
    int close_type = 0; //开仓激进程度， 如空信号，现持有多仓；0： 平现有多仓；1： 忽略该信号；2： 平现有多仓，并开空仓（数量由pos_limit决定）
    long vol_limit = 0; //持仓的最大数量，单位，手
    double init_cash = 0; //初始资金，单位：元
    float risk_ratio = 0.1; //资金风险度限额
    int order_duration = 20; //两次下单的时间间隔限制，单位：秒
    int signal_delay = 5; //下单信号延迟，单位：秒，超时则忽略当前下单信号
    int risk_duration = 60; // 持仓风险检查的频率，单位：秒；
    int cancel_order_delay = 120; // 撤销委托的间隔，单位：秒；如果一笔限价委托超时，则在风险监控线程中会自动撤销该笔委托
}StrategyConfig;


struct OrderData
{
	std::string symbol;     
    std::string exchangeid;
	int volume;
	int side;
	int order_type;
	int position_effect;
	double price;
	std::string account;
	int status;
    std::time_t order_insert_time;
    OrderData(){
        status=-1;
        price = 0.0;
        volume = 0;
    }

};


typedef DataQueue* data_queue_ptr;
typedef TaskQueue* task_queue_ptr;
typedef char FileName[50];



struct RiskInputData
{
    std::string symbol;
    std::string update_time;
    std::string exchangeid;
    double last_price;
};


enum OrderVerify
{
	OrderVerify_valid = 0,
	OrderVerify_unvalid = -1,
};

struct OrderIDRef{
    int FrontID;
    int SessionID;
    char OrderRef[13];
    char ExchangeID[9];
    char TraderID[21];
    char OrderLocalID[13];
    char OrderSysID[21];
};

typedef OrderIDRef* ptr_OrderIDRef;
struct OrderField{
    ptr_OrderIDRef p_orderid_ref;
    // ptr_Order p_order;
    std::string order_id;
    //委托数量
    TThostFtdcVolumeType	VolumeTotalOriginal;
    //限价
    TThostFtdcPriceType	LimitPrice;
    //买卖方向
    // #define THOST_FTDC_DEN_Buy '0'
    // #define THOST_FTDC_DEN_Sell '1'
    TThostFtdcDirectionType	Direction;
    //组合投机套保标志
    TThostFtdcCombHedgeFlagType	CombHedgeFlag;
    //报单类型 THOST_FTDC_TC_IOC '1' 立即完成，否则撤销
    TThostFtdcOrderTypeType	OrderType;
    //已成交数量
    TThostFtdcVolumeType	VolumeTraded;
    //剩余数量
    TThostFtdcVolumeType	VolumeTotal;
    ///组合开平标志 THOST_FTDC_OF_Open
    TThostFtdcCombOffsetFlagType	CombOffsetFlag;
    //已成交均价
    TThostFtdcPriceType	Price;
    ///报单状态
    TThostFtdcOrderStatusType	OrderStatus;
    // /最后修改时间
	// TThostFtdcTimeType	UpdateTime;
    // 订单插入时间
    // TThostFtdcTimeType	InsertTime;
    //本地维护的订单插入时间
    std::time_t InsertTime;
    
};
typedef OrderField* ptr_OrderField;
typedef CThostFtdcInvestorPositionField PositionField;



typedef PositionField* ptr_Position;







