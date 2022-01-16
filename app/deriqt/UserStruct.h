#pragma once
#include <string>
#include <iostream>
#include <codecvt>
#include <locale>
//#include <folly/executors/UnboundedBlockingQueue.h>
#include <boost/thread/concurrent_queues/sync_queue.hpp>

//boost::sync_queue example https://github.com/boostorg/thread/blob/develop/example/producer_consumer.cpp
//for more careful usage, should catch sync_queue_is_closed exception


//����ṹ��
struct Task
{
    int task_name;    //�ص��������ƶ�Ӧ�ĳ���
    void *task_data;  //����ָ��
    void *task_error; //����ָ��
    int task_id;      //����id
    bool task_last;   //�Ƿ�Ϊ��󷵻�
    Task(): task_name(0), task_data(NULL), task_error(NULL), task_id(0), task_last(false){};
    ~Task(){
        if(!task_data){
            
        }
    };
};

struct DataField
{
    int data_type; //�������
    void *_data; //����ָ��
    void *error; //����ָ��
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
    //�����µ�����
    void push(const Task &task)
    {
        std::cout<<"queue size:"<<queue_.size()<<std::endl;
        LOG(INFO)<<"start push to task Queue";
        queue_.push(task);  //������д�������
        std::cout<<"complete push to task Queue, notify";<<std::endl;
    }

    //ȡ���ϵ�����
    Task pop()
    {
        Task task;
        queue_.pull(task); //��ȡ�����е����һ������
        return task;                //���ظ�����
    }

    void terminate()
    {
        _terminate = true;
    }
};

class DataQueue
{
private:
    folly::UnboundedBlockingQueue<DataField> queue_;       //��׼�����
    bool _terminate = false;

public:
    DataQueue(){};
    ~DataQueue(){};
    //�����µ�����
    void push(const DataField &data)
    {
        queue_.push(data);  //������д�������
    }

    //ȡ���ϵ�����
    DataField pop()
    {
        DataField data;
        queue_.pull(data); //��ȡ�����е����һ������
        return data;                //���ظ�����
    }

    void terminate()
    {
        _terminate = true;
    }
};



//��GBK������ַ���ת��ΪUTF8
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
