#pragma once
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <codecvt>
#include <condition_variable>
#include <locale>

using namespace std;

//����ṹ��
struct Task
{
    int task_name;    //�ص��������ƶ�Ӧ�ĳ���
    void *task_data;  //����ָ��
    void *task_error; //����ָ��
    int task_id;      //����id
    bool task_last;   //�Ƿ�Ϊ��󷵻�
};

struct MktData
{
    int data_type; //�����������
    void *mkt_data; //����ָ��
    void *error; //����ָ��
};

class TerminatedError : std::exception
{
};

class TaskQueue
{
private:
    queue<Task> queue_;       //��׼�����
    mutex mutex_;             //������
    condition_variable cond_; //��������
    bool _terminate = false;

public:
    //�����µ�����
    void push(const Task &task)
    {
        unique_lock<mutex> mlock(mutex_);
        queue_.push(task);  //������д�������
        mlock.unlock();     //�ͷ���
        cond_.notify_one(); //֪ͨ���������ȴ����߳�
    }

    //ȡ���ϵ�����
    Task pop()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() || _terminate;
        }); //�ȴ���������֪ͨ
        if (_terminate)
            throw TerminatedError();
        Task task = queue_.front(); //��ȡ�����е����һ������
        queue_.pop();               //ɾ��������
        return task;                //���ظ�����
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //֪ͨ���������ȴ����߳�
    }
};

class MktDataQueue
{
private:
    queue<MktData> queue_;       //��׼�����
    mutex mutex_;             //������
    condition_variable cond_; //��������
    bool _terminate = false;

public:
    //�����µ�����
    void push(const MktData &data)
    {
        unique_lock<mutex> mlock(mutex_);
        queue_.push(data);  //������д�������
        mlock.unlock();     //�ͷ���
        cond_.notify_one(); //֪ͨ���������ȴ����߳�
    }

    //ȡ���ϵ�����
    MktData pop()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() || _terminate;
        }); //�ȴ���������֪ͨ
        if (_terminate)
            throw TerminatedError();
        MktData data = queue_.front(); //��ȡ�����е����һ������
        queue_.pop();               //ɾ��������
        return data;                //���ظ�����
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //֪ͨ���������ȴ����߳�
    }
};


//��GBK������ַ���ת��ΪUTF8
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

