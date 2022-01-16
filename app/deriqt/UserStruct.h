#pragma once
#include <string>
#include <iostream>
#include <codecvt>
#include <locale>
//#include <folly/executors/UnboundedBlockingQueue.h>
#include <boost/thread/concurrent_queues/sync_queue.hpp>

//boost::sync_queue example https://github.com/boostorg/thread/blob/develop/example/producer_consumer.cpp
//for more careful usage, should catch sync_queue_is_closed exception


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
    boost::sync_queue<Task> queue_;
    bool _terminate = false;

public:
    //存入新的任务
    void push(const Task &task)
    {
        std::cout<<"queue size:"<<queue_.size()<<std::endl;
        LOG(INFO)<<"start push to task Queue";
        queue_.push(task);  //向队列中存入数据
        std::cout<<"complete push to task Queue, notify";<<std::endl;
    }

    //取出老的任务
    Task pop()
    {
        Task task;
        queue_.pull(task); //获取队列中的最后一个任务
        return task;                //返回该任务
    }

    void terminate()
    {
        _terminate = true;
    }
};

class DataQueue
{
private:
    folly::UnboundedBlockingQueue<DataField> queue_;       //标准库队列
    bool _terminate = false;

public:
    DataQueue(){};
    ~DataQueue(){};
    //存入新的数据
    void push(const DataField &data)
    {
        queue_.push(data);  //向队列中存入数据
    }

    //取出老的任务
    DataField pop()
    {
        DataField data;
        queue_.pull(data); //获取队列中的最后一个数据
        return data;                //返回该数据
    }

    void terminate()
    {
        _terminate = true;
    }
};



//将GBK编码的字符串转换为UTF8
inline std::string toUtf(const std::string &gb2312)
{
#ifdef _MSC_VER
    const static std::locale loc("zh-CN");
#else
    const static std::locale loc("zh_CN.GB18030");
#endif

    std::vector<wchar_t> wstr(gb2312.size());
    wchar_t *wstrEnd = nullptr;
    const char *gbEnd = nullptr;
    mbstate_t state = {};
    int res = std::use_facet<codecvt<wchar_t, char, mbstate_t>>(loc).in(state,
                                                                   gb2312.data(), gb2312.data() + gb2312.size(), gbEnd,
                                                                   wstr.data(), wstr.data() + wstr.size(), wstrEnd);

    if (std::codecvt_base::ok == res)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
        return cutf8.to_bytes(std::wstring(wstr.data(), wstrEnd));
    }

    return std::string();
}


typedef DataQueue* data_queue_ptr;
typedef TaskQueue* task_queue_ptr;
typedef char FileName[50];
