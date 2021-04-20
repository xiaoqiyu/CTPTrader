#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "include/ThostFtdcUserApiStruct.h"
#include "TickToKlineHelper.h"

void TickToKlineHelper::KLineFromLocalData(const std::string &sFilePath, const std::string &dFilePath)
{
	// 先清理残留数据
	m_priceVec.clear();
	m_volumeVec.clear();
	m_KLineDataArray.clear();

	std::cout << "开始转换tick到k线..." << std::endl;
	// 默认读取的tick数据表有4个字段：合约代码、更新时间、最新价、成交量
	std::ifstream srcInFile;
	std::ofstream dstOutFile;
	srcInFile.open(sFilePath, std::ios::in);
	dstOutFile.open(dFilePath, std::ios::out);
	dstOutFile << "开盘价" << ','
			   << "最高价" << ','
			   << "最低价" << ','
			   << "收盘价" << ','
			   << "成交量" << std::endl;

	// 一遍解析文件一边计算k线数据，1分钟k线每次读取60 * 2 = 120行数据
	std::string lineStr;
	bool isFirstLine = true;
	while (std::getline(srcInFile, lineStr))
	{
		if (isFirstLine)
		{
			// 跳过第一行表头
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

		// 计算k线
		if (m_priceVec.size() == KLINENUM)
		{
			KLineDataType k_line_data;
			k_line_data.open_price = m_priceVec.front();
			k_line_data.high_price = *std::max_element(m_priceVec.cbegin(), m_priceVec.cend());
			k_line_data.low_price = *std::min_element(m_priceVec.cbegin(), m_priceVec.cend());
			k_line_data.close_price = m_priceVec.back();
			// 成交量的真实的算法是当前区间最后一个成交量减去上去一个区间最后一个成交量
			k_line_data.volume = m_volumeVec.back() - m_volumeVec.front();
			//m_KLineDataArray.push_back(k_line_data); // 此处可以存到内存

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
	std::cout << "k线生成成功" << std::endl;
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
		// 成交量的真实的算法是当前区间最后一个成交量减去上去一个区间最后一个成交量
		p_kline_data->volume = m_volumeVec.back() - m_volumeVec.front();
		m_KLineDataArray.push_back(p_kline_data); // 此处可以存到内存
		std::cout << "KLINE: " <<pDepthMarketData->InstrumentID<<","<<pDepthMarketData->UpdateTime << ","<<p_kline_data->open_price << "," 
				<< p_kline_data->high_price << "," << p_kline_data->low_price << "," << p_kline_data->close_price
				<< "," << p_kline_data->volume << std::endl;

		m_priceVec.clear();
		m_volumeVec.clear();
		// p_kline_data = &k_line_data;
		// char filePath[100] = {'\0'};
		// sprintf(filePath, "cache/%s_kline.txt", pDepthMarketData->TradingDay);
		// std::ofstream outFile;
		// outFile.open(filePath, std::ios::app); // 文件追加写入
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
