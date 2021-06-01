#pragma once
// ---- 计算k线的类 ---- //

#include <vector>
#include <string>
#include "define.h"

// k线数据结构
struct KLineDataType
{
	TThostFtdcTimeType time_stamp;
	double open_price;   // 开
	double high_price;   // 高
	double low_price;    // 低
	double close_price;  // 收
	int volume;          // 量
};

class TickToKlineHelper
{
public:
	TickToKlineHelper(){};
	~TickToKlineHelper(){
		for(auto iter=m_KLineDataVec.begin(); iter!=m_KLineDataVec.end(); ++iter)
		{
			delete (*iter);
		}
	};
	// 从本地数据构建k线，并存储到本地(假定本地数据没有丢包)
	void KLineFromLocalData(const std::string &sFilePath, const std::string &dFilePath); 
	// 从实时数据构建k线
	bool KLineFromRealtimeData(CThostFtdcDepthMarketDataField *pDepthMarketData, KLineDataType* p_kline_data);
public:
	std::vector<double> m_priceVec; // 存储1分钟的价格
	std::vector<int> m_volumeVec; // 存储1分钟的成交量
	std::vector<KLineDataType* > m_KLineDataVec;
	std::string last_update_time;
	
};
