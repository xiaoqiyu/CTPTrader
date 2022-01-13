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
    mutex mutex_;             //互斥锁
    condition_variable cond_; //条件变量
    bool _terminate = false;

public:
    //存入新的任务
    void push(const Task &task)
    {
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
        cond_.notify_one(); //通知正在阻塞等待的线程
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
    double stop_profit = 0.0;
    double stop_loss = 0.0;
    int close_type = 0; //开仓激进程度， 如空信号，现持有多仓；0： 平现有多仓；1： 忽略该信号；2： 平现有多仓，并开空仓（数量由pos_limit决定）
    long vol_limit = 0; //
    double init_cash = 0;
    float risk_ratio = 0.1; 
    int order_duration = 20;
}StrategyConfig;


typedef struct 
{
	std::string symbol;     
	int volume;
	int side;
	int order_type;
	int position_effect;
	double price;
	std::string account;
	int status;
}OrderData;


class OrderQueue
{
private:
    queue<OrderData> queue_;       //标准库队列
    mutex mutex_;             //互斥锁
    condition_variable cond_; //条件变量
    bool _terminate = false;

public:
    OrderQueue(){};
    ~OrderQueue(){};
    void push(const OrderData &data)
    {
        unique_lock<mutex> mlock(mutex_);
        queue_.push(data);  //向队列中存入数据
        mlock.unlock();     //释放锁
        cond_.notify_one(); //通知正在阻塞等待的线程
    }

    OrderData pop()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() ;
        }); //等待条件变量通知
        if (_terminate)
            throw TerminatedError();
        OrderData data = queue_.front(); //获取队列中的最后一个数据
        queue_.pop();               //删除该数据
        return data;                //返回该数据
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //通知正在阻塞等待的线程
    }
};


typedef DataQueue* data_queue_ptr;
typedef TaskQueue* task_queue_ptr;
// typedef OrderQueue* order_queue_ptr;
typedef char FileName[50];


// int test(std::string product_id, int mode){
    // std::unordered_map<std::string, std::string> gm_exchange_map;
    // std::unordered_map<std::string, std::string> ctp_exchange_map;
    // std::string no_results;
    // gm_exchange_map.insert(std::pair<std::string, std::string>("eg", "DCE"));
    // if(mode == 1){//simtrade
        // auto it = gm_exchange_map.find(product_id);
        // if (it != gm_exchange_map.end()){
            // return it->second;
        // }
    // }else if(mode == 2){
        // auto it = ctp_exchange_map.find(product_id);
        // if (it != ctp_exchange_map.end()){
            // return it->second;
        // }
    // }
    // return 0;
// }