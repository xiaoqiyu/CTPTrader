#include <string>
#pragma once
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

//����ṹ��?
struct Task
{
    int task_name;    //�ص��������ƶ�Ӧ�ĳ���
    void *task_data;  //����ָ��
    void *task_error; //����ָ��
    int task_id;      //����id
    bool task_last;   //�Ƿ�Ϊ��󷵻�?
    Task(): task_name(0), task_data(NULL), task_error(NULL), task_id(0), task_last(false){};
    ~Task(){
        if(!task_data){
            
        }
    };
};

struct DataField
{
    int data_type; //�������?
    void *_data; //����ָ��
    void *error; //����ָ��
};

class TerminatedError : std::exception
{
};

class TaskQueue
{
private:
    queue<Task> queue_;       //��׼�����?
    // boost::sync_queue<Task> queue_; // boost sync queue
    mutex mutex_;             //������
    condition_variable cond_; //��������
    bool _terminate = false;

public:
    //�����µ�����
    void push(const Task &task)
    {
        // std::cout<<"push task:"<<task.task_name<<std::endl;
        unique_lock<mutex> mlock(mutex_);
        queue_.push(task);  //������д�������?
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
        Task task = queue_.front(); //��ȡ�����е����һ������?
        queue_.pop();               //ɾ��������
        // std::cout<<"poped task:"<<task.task_name<<std::endl;
        return task;                //���ظ�����
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //֪ͨ���������ȴ����߳�
    }
};

class DataQueue
{
private:
    queue<DataField> queue_;       //��׼�����?
    // boost::sync_queue<DataField> queue_;
    mutex mutex_;             //������
    condition_variable cond_; //��������
    bool _terminate = false;

public:
    DataQueue(){};
    ~DataQueue(){};
    //�����µ�����
    void push(const DataField &data)
    {
        unique_lock<mutex> mlock(mutex_);
        queue_.push(data);  //������д�������?
        mlock.unlock();     //�ͷ���
        cond_.notify_all(); //֪ͨ���������ȴ����߳�
    }

    //ȡ���ϵ�����
    DataField pop()
    {
        
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() ;
        }); //�ȴ���������֪ͨ
        if (_terminate)
            throw TerminatedError();
        DataField data = queue_.front(); //��ȡ�����е����һ������?
        queue_.pop();               //ɾ��������
        return data;                //���ظ�����
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all(); //֪ͨ���������ȴ����߳�
    }
};



//��GBK������ַ����?��ΪUTF8
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
    double stop_profit = 50;//real money, not pct��ÿ��ί�е�ֹӯ���ã���λ��Ԫ��
    double stop_loss = 50;//real money, not pct��ÿ��ί�е�ֹ�����ã���λ��Ԫ
    int close_type = 0; //���ּ����̶ȣ� ����źţ��ֳ��ж�֣�0�� ƽ���ж�֣�?1�� ���Ը��źţ�2�� ƽ���ж�֣������ղ֣�������pos_limit������
    long vol_limit = 0; //�ֲֵ������������λ����?
    double init_cash = 0; //��ʼ�ʽ𣬵�λ��Ԫ
    float risk_ratio = 0.1; //�ʽ���ն��޶�?
    int order_duration = 20; //�����µ���ʱ�������ƣ���λ����
    int signal_delay = 5; //�µ��ź��ӳ٣���λ���룬��ʱ����Ե�ǰ�µ��ź�?
    int risk_duration = 60; // �ֲַ��ռ���Ƶ�ʣ���λ���룻
    int cancel_order_delay = 120; // ����ί�еļ������λ���룻���һ���޼�ί�г�ʱ�����ڷ��ռ���߳��л��Զ������ñ��?��
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
typedef char FileName[100];



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
    //ί������
    TThostFtdcVolumeType	VolumeTotalOriginal;
    //�޼�
    TThostFtdcPriceType	LimitPrice;
    //��������
    // #define THOST_FTDC_DEN_Buy '0'
    // #define THOST_FTDC_DEN_Sell '1'
    TThostFtdcDirectionType	Direction;
    //���Ͷ���ױ����?
    TThostFtdcCombHedgeFlagType	CombHedgeFlag;
    //�������� THOST_FTDC_TC_IOC '1' ������ɣ�������?
    TThostFtdcOrderTypeType	OrderType;
    //�ѳɽ�����
    TThostFtdcVolumeType	VolumeTraded;
    //ʣ������
    TThostFtdcVolumeType	VolumeTotal;
    ///��Ͽ�ƽ���? THOST_FTDC_OF_Open
    TThostFtdcCombOffsetFlagType	CombOffsetFlag;
    //�ѳɽ�����
    TThostFtdcPriceType	Price;
    ///����״̬
    TThostFtdcOrderStatusType	OrderStatus;
    // /����޸�ʱ��?
	// TThostFtdcTimeType	UpdateTime;
    // ��������ʱ��
    // TThostFtdcTimeType	InsertTime;
    //����ά���Ķ�������ʱ��
    std::time_t InsertTime;
    OrderField(){
        Price = 0.0;
        VolumeTraded = 0;
        VolumeTotalOriginal = 0;

    };
    
};
typedef OrderField* ptr_OrderField;
typedef CThostFtdcInvestorPositionField PositionField;



typedef PositionField* ptr_Position;

enum TickType{
    DualOPen=0,  //˫�����ɽ�>=0, �ֲ�>=0, |�ɽ�|==|�ֲ�| 
    DualClose=1, //˫ƽ���ɽ�>=0, �ֲ�<=0, |�ɽ�| == |�ֲ�|
    Transfer=2,//���֣��໻���ջ���ȡ���ڷ��� �ֲ�=0���ɽ�>=0
    Open=3,//����, �ɽ�>=0, �ֲ�>0, |�ɽ�|>|�ֲ�|
    Close=4,//ƽ�֣� �ɽ�>=0, �ֲ�<0, |�ɽ�|>|�ֲ�|
    OtherType=5,//δ֪
};

enum TickDirection{
    Buy=0,//������
    Sell=1,//������
    Unknown=2,//δ֪
};


struct daily_cache{
    std::string InstrumentID;
    std::string product_id;
    double open_price;
    double hh;
    double hc;
    double lc;
    double ll;
    double up_limit;
    double down_limit;
};

typedef daily_cache* ptr_daily_cache;



