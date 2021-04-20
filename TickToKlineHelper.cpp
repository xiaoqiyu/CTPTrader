#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "include/ThostFtdcUserApiStruct.h"
#include "TickToKlineHelper.h"

void TickToKlineHelper::KLineFromLocalData(const std::string &sFilePath, const std::string &dFilePath)
{
	// �������������
	m_priceVec.clear();
	m_volumeVec.clear();
	m_KLineDataArray.clear();

	std::cout << "��ʼת��tick��k��..." << std::endl;
	// Ĭ�϶�ȡ��tick���ݱ���4���ֶΣ���Լ���롢����ʱ�䡢���¼ۡ��ɽ���
	std::ifstream srcInFile;
	std::ofstream dstOutFile;
	srcInFile.open(sFilePath, std::ios::in);
	dstOutFile.open(dFilePath, std::ios::out);
	dstOutFile << "���̼�" << ','
			   << "��߼�" << ','
			   << "��ͼ�" << ','
			   << "���̼�" << ','
			   << "�ɽ���" << std::endl;

	// һ������ļ�һ�߼���k�����ݣ�1����k��ÿ�ζ�ȡ60 * 2 = 120������
	std::string lineStr;
	bool isFirstLine = true;
	while (std::getline(srcInFile, lineStr))
	{
		if (isFirstLine)
		{
			// ������һ�б�ͷ
			isFirstLine = false;
			continue;
		}
		std::istringstream ss(lineStr);
		std::string fieldStr;
		int count = 4;
		while (std::getline(ss, fieldStr, ','))
		{
			count--;
			if (count == 1)
				m_priceVec.push_back(std::atof(fieldStr.c_str()));
			else if (count == 0)
			{
				m_volumeVec.push_back(std::atoi(fieldStr.c_str()));
				break;
			}
		}

		// ����k��
		if (m_priceVec.size() == KLINENUM)
		{
			KLineDataType k_line_data;
			k_line_data.open_price = m_priceVec.front();
			k_line_data.high_price = *std::max_element(m_priceVec.cbegin(), m_priceVec.cend());
			k_line_data.low_price = *std::min_element(m_priceVec.cbegin(), m_priceVec.cend());
			k_line_data.close_price = m_priceVec.back();
			// �ɽ�������ʵ���㷨�ǵ�ǰ�������һ���ɽ�����ȥ��ȥһ���������һ���ɽ���
			k_line_data.volume = m_volumeVec.back() - m_volumeVec.front();
			//m_KLineDataArray.push_back(k_line_data); // �˴����Դ浽�ڴ�

			dstOutFile << k_line_data.open_price << ','
					   << k_line_data.high_price << ','
					   << k_line_data.low_price << ','
					   << k_line_data.close_price << ','
					   << k_line_data.volume << std::endl;

			m_priceVec.clear();
			m_volumeVec.clear();
		}
	}
	srcInFile.close();
	dstOutFile.close();
	std::cout << "k�����ɳɹ�" << std::endl;
}

bool TickToKlineHelper::KLineFromRealtimeData(CThostFtdcDepthMarketDataField *pDepthMarketData, KLineDataType * p_kline_data)
{
	m_priceVec.push_back(pDepthMarketData->LastPrice);
	m_volumeVec.push_back(pDepthMarketData->Volume);
	// KLineDataType *p_kline_data;
	if (m_priceVec.size() == KLINENUM)
	{
		// KLineDataType k_line_data;
		p_kline_data->open_price = m_priceVec.front();
		p_kline_data->high_price = *std::max_element(m_priceVec.cbegin(), m_priceVec.cend());
		p_kline_data->low_price = *std::min_element(m_priceVec.cbegin(), m_priceVec.cend());
		p_kline_data->close_price = m_priceVec.back();
		// �ɽ�������ʵ���㷨�ǵ�ǰ�������һ���ɽ�����ȥ��ȥһ���������һ���ɽ���
		p_kline_data->volume = m_volumeVec.back() - m_volumeVec.front();
		m_KLineDataArray.push_back(p_kline_data); // �˴����Դ浽�ڴ�
		std::cout << "KLINE: " <<pDepthMarketData->InstrumentID<<","<<pDepthMarketData->UpdateTime << ","<<p_kline_data->open_price << "," 
				<< p_kline_data->high_price << "," << p_kline_data->low_price << "," << p_kline_data->close_price
				<< "," << p_kline_data->volume << std::endl;

		m_priceVec.clear();
		m_volumeVec.clear();
		// p_kline_data = &k_line_data;
		// char filePath[100] = {'\0'};
		// sprintf(filePath, "cache/%s_kline.txt", pDepthMarketData->TradingDay);
		// std::ofstream outFile;
		// outFile.open(filePath, std::ios::app); // �ļ�׷��д��
		// outFile << pDepthMarketData->InstrumentID << ","
		// 		<<pDepthMarketData->UpdateTime <<","
		// 		<< k_line_data.open_price <<","
		// 		<< k_line_data.high_price <<","
		// 		<< k_line_data.low_price << ","
		// 		<<k_line_data.close_price <<","
		// 		<< k_line_data.volume << std::endl;
		// outFile.close();
		return true;
	}
	return false;
}
