#pragma once
// ---- ����k�ߵ��� ---- //

#include <vector>
#include <string>
#include "define.h"

// k�����ݽṹ
struct KLineDataType
{
	TThostFtdcTimeType time_stamp;
	double open_price;   // ��
	double high_price;   // ��
	double low_price;    // ��
	double close_price;  // ��
	int volume;          // ��
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
	// �ӱ������ݹ���k�ߣ����洢������(�ٶ���������û�ж���)
	void KLineFromLocalData(const std::string &sFilePath, const std::string &dFilePath); 
	// ��ʵʱ���ݹ���k��
	bool KLineFromRealtimeData(CThostFtdcDepthMarketDataField *pDepthMarketData, KLineDataType* p_kline_data);
public:
	std::vector<double> m_priceVec; // �洢1���ӵļ۸�
	std::vector<int> m_volumeVec; // �洢1���ӵĳɽ���
	std::vector<KLineDataType* > m_KLineDataVec;
	std::string last_update_time;
	
};
