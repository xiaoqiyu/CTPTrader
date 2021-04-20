#include <iostream>
#include "StrategyHandler.h"

void StrategyHandler::on_tick(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	// std::cout<<"Push data to queue: "<<pDepthMarketData->InstrumentID<<std::endl;
	MktData data = MktData();
	data.data_type = FDEPTHMKT;
	CThostFtdcDepthMarketDataField *mkt_data = new CThostFtdcDepthMarketDataField();
	*mkt_data = *pDepthMarketData;
	data.mkt_data = mkt_data;
	this->p_dataqueue->push(data);
}

void StrategyHandler::process_tick()
{
	std::cout << "============================Start Process Data==========================" << std::endl;
	try
	{
		while (true)
		{
			MktData data = this->p_dataqueue->pop();
			switch (data.data_type)
			{
			case FDEPTHMKT: //期货深度行情数据
			{
				if (data.mkt_data)
				{
					CThostFtdcDepthMarketDataField *pDepthMarketData = (CThostFtdcDepthMarketDataField *)data.mkt_data;
					// std::cout << "Save Data: " << pDepthMarketData->InstrumentID<<std::endl;//减少IO阻塞
					this->mkt_depth_outfile << pDepthMarketData->InstrumentID << ","
											// << pDepthMarketData->ExchangeID << ","//null 
											// << pDepthMarketData->ExchangeInstID << "," //null
											<< pDepthMarketData->ActionDay << ","
											<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << ","
											<< pDepthMarketData->LastPrice << ","
											<< pDepthMarketData->PreSettlementPrice << ","
											<< pDepthMarketData->PreClosePrice << ","
											<< pDepthMarketData->OpenPrice << ","
											<< pDepthMarketData->HighestPrice << ","
											<< pDepthMarketData->LowestPrice << ","
											<< pDepthMarketData->AveragePrice << ","
											<< pDepthMarketData->ClosePrice << ","
											<< pDepthMarketData->Volume << ","
											<< pDepthMarketData->Turnover << ","
											<< pDepthMarketData->SettlementPrice << ","
											<< pDepthMarketData->UpperLimitPrice << ","
											<< pDepthMarketData->LowerLimitPrice << ","
											<< pDepthMarketData->BidPrice1 << ","
											<< pDepthMarketData->BidVolume1 << ","
											// << pDepthMarketData->BidPrice2 << "," //null
											// << pDepthMarketData->BidVolume2 << "," //null
											// << pDepthMarketData->BidPrice3 << "," //null
											// << pDepthMarketData->BidVolume3 << "," //null
											// << pDepthMarketData->BidPrice4 << "," //null
											// << pDepthMarketData->BidVolume4 << "," //null
											// << pDepthMarketData->BidPrice5 << "," //null
											// << pDepthMarketData->BidVolume5 << "," //null
											<< pDepthMarketData->AskPrice1 << ","
											<< pDepthMarketData->AskVolume1 << ","
											// << pDepthMarketData->AskPrice2 << "," //null
											// << pDepthMarketData->AskVolume2 << "," //null
											// << pDepthMarketData->AskPrice3 << ","//null
											// << pDepthMarketData->AskVolume3 << ","//null
											// << pDepthMarketData->AskPrice4 << "," //null 
											// << pDepthMarketData->AskVolume4 << "," //null
											// << pDepthMarketData->AskPrice5 << "," //null
											// << pDepthMarketData->AskVolume5 << "," //null
											<< pDepthMarketData->PreOpenInterest << ","
											<< pDepthMarketData->OpenInterest << ","
											<< pDepthMarketData->PreDelta << ","
											<< pDepthMarketData->CurrDelta << ","
											<< std::endl;
					// outFile.close();

					// 计算实时k线
					// std::string instrumentKey = std::string(pDepthMarketData->InstrumentID);
					// if (g_KlineHash.find(instrumentKey) == g_KlineHash.end())
					// 	g_KlineHash[instrumentKey] = TickToKlineHelper();
					// g_KlineHash[instrumentKey].KLineFromRealtimeData(pDepthMarketData);
					KLineDataType *p_kline_data = new KLineDataType();
					bool ret = this->p_kline_helper->KLineFromRealtimeData(pDepthMarketData, p_kline_data);

					if(ret)
					{
						std::cout << "k line:" << pDepthMarketData->InstrumentID << ":" << p_kline_data->open_price << p_kline_data->high_price << std::endl;
						this->kline_outfile << pDepthMarketData->InstrumentID << ","
											<< pDepthMarketData->UpdateTime << ","
											<< p_kline_data->open_price << ","
											<< p_kline_data->high_price << ","
											<< p_kline_data->low_price << ","
											<< p_kline_data->close_price << ","
											<< p_kline_data->volume << std::endl;
					}

					//计算因子和下单信号
					

				}
				if (data.error)
				{
					std::cout << "handle error in market data subscribe" << std::endl;
				}

				break;
			}
			default:
				break;
			}
		}
	}
	catch (const TerminatedError &)
	{
	}
}

void calculate_kline();

void StrategyHandler::calculate_kline()
{
}