#pragma once
// ---- ����k�ߵ��� ---- //

#include <vector>
#include <string>
#include "include/define.h"

// k�����ݽṹ
struct KLineDataType
{
	double open_price;   // ��
	double high_price;   // ��
	double low_price;    // ��
	double close_price;  // ��
	int volume;          // ��
};

class TickToKlineHelper
{
public:
	// �ӱ������ݹ���k�ߣ����洢������(�ٶ���������û�ж���)
	void KLineFromLocalData(const std::string &sFilePath, const std::string &dFilePath); 
	// ��ʵʱ���ݹ���k��
	void KLineFromRealtimeData(CThostFtdcDepthMarketDataField *pDepthMarketData);
public:
	std::vector<double> m_priceVec; // �洢1���ӵļ۸�
	std::vector<int> m_volumeVec; // �洢1���ӵĳɽ���
	std::vector<KLineDataType> m_KLineDataArray;
};
