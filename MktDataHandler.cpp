#include <iostream>
#include "MktDataHandler.h"


void MktDataHandler::push_mkt_depth_data(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // std::cout<<"Push data to queue: "<<pDepthMarketData->InstrumentID<<std::endl;
	MktData data = MktData();
	data.data_type = FDEPTHMKT;
	CThostFtdcDepthMarketDataField *mkt_data = new CThostFtdcDepthMarketDataField();
	*mkt_data = *pDepthMarketData;
	data.mkt_data = mkt_data;
    this->p_dataqueue->push(data);
}

void MktDataHandler::process_mkt_depth_data()
{
    std::cout<<"============================Start Process Data=========================="<<std::endl;
	try
	{
		while(true)
		{
        
		MktData data = this->p_dataqueue->pop();
		switch (data.data_type)
		{
			case FDEPTHMKT: //期货深度行情数据
			{
				if(data.mkt_data)
				{
					std::cout<<"===========================Save Data=============================="<<std::endl;
					CThostFtdcDepthMarketDataField *pDepthMarketData = (CThostFtdcDepthMarketDataField*)data.mkt_data;
					std::cout << "合约代码： " << pDepthMarketData->InstrumentID << ",";
					// std::cout << "合约在交易所的代码： " << pDepthMarketData->ExchangeInstID << std::endl;
					std::cout << "最新价： " << pDepthMarketData->LastPrice << ",";
					std::cout << "数量： " << pDepthMarketData->Volume << std::endl;
					// 如果只获取某一个合约行情，可以逐tick地存入文件或数据库
					
					char filePath[100] = {'\0'};
					sprintf(filePath, "cache/%s_market_data_new.txt", pDepthMarketData->TradingDay);
					std::ofstream outFile;
					// outFile.open(filePath, std::ios::app); // 文件追加写入 
					this->mkt_depth_outfile << pDepthMarketData->InstrumentID << "," 
						<<pDepthMarketData->ExchangeID<<","
						<<pDepthMarketData->ExchangeInstID<<","
						<<pDepthMarketData->ActionDay<<","
						<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << "," 
						<< pDepthMarketData->LastPrice << "," 
						<<pDepthMarketData->PreSettlementPrice<<","
						<<pDepthMarketData->PreClosePrice<<","
						<<pDepthMarketData->PreOpenInterest<<","
						<<pDepthMarketData->OpenPrice<<","
						<<pDepthMarketData->HighestPrice<<","
						<<pDepthMarketData->LowestPrice<<","
						<<pDepthMarketData->Volume<<","
						<<pDepthMarketData->Turnover<<","
						<<pDepthMarketData->OpenInterest<<","
						<<pDepthMarketData->ClosePrice<<","
						<<pDepthMarketData->SettlementPrice<<","
						<<pDepthMarketData->UpperLimitPrice<<","
						<<pDepthMarketData->LowestPrice<<","
						<<pDepthMarketData->AveragePrice<<","
						<<pDepthMarketData->PreDelta<<","
						<<pDepthMarketData->CurrDelta<<","
						<<pDepthMarketData->BidPrice1<<","
						<<pDepthMarketData->BidVolume1<<","
						<<pDepthMarketData->BidPrice2<<","
						<<pDepthMarketData->BidVolume2<<","
						<<pDepthMarketData->BidPrice3<<","
						<<pDepthMarketData->BidVolume3<<","
						<<pDepthMarketData->BidPrice4<<","
						<<pDepthMarketData->BidVolume4<<","
						<<pDepthMarketData->BidPrice5<<","
						<<pDepthMarketData->BidVolume5<<","
						<<pDepthMarketData->AskPrice1<<","
						<<pDepthMarketData->AskVolume1<<","
						<<pDepthMarketData->AskPrice2<<","
						<<pDepthMarketData->AskVolume2<<","
						<<pDepthMarketData->AskPrice3<<","
						<<pDepthMarketData->AskVolume3<<","
						<<pDepthMarketData->AskPrice4<<","
						<<pDepthMarketData->AskVolume4<<","
						<<pDepthMarketData->AskPrice5<<","
						<<pDepthMarketData->AskVolume5<<","<<std::endl;
					// outFile.close();

					// 计算实时k线
					// std::string instrumentKey = std::string(pDepthMarketData->InstrumentID);
					// if (g_KlineHash.find(instrumentKey) == g_KlineHash.end())
					// 	g_KlineHash[instrumentKey] = TickToKlineHelper();
					// g_KlineHash[instrumentKey].KLineFromRealtimeData(pDepthMarketData);
                    KLineDataType *p_kline_data = this->p_kline_helper->KLineFromRealtimeData(pDepthMarketData);
                    // char filePath[100] = {'\0'};
                    // sprintf(filePath, "cache/%s_kline.txt", pDepthMarketData->TradingDay);
                    // std::ofstream outFile;
                    // this->kline_outfile.open(filePath, std::ios::app); // 文件追加写入 
                    if (NULL == p_kline_data)
                    {
                        std::cout<<"No K line return"<<std::endl;
                    }else
                    {
                        this->kline_outfile << pDepthMarketData->InstrumentID << "," 
                    		<<pDepthMarketData->UpdateTime <<","
                    		<< p_kline_data->open_price <<","
                    		<< p_kline_data->high_price <<","
                    		<< p_kline_data->low_price << ","
                    		<< p_kline_data->close_price <<","
                    		<< p_kline_data->volume << std::endl;
                    }				
				}
				if(data.error)
				{
					std::cout<<"handle error in market data subscribe"<<std::endl;
				}
				
				break;

			}
			default:
				break;
			}
			
		}
	}
	catch(const TerminatedError &)
	{

	}

}

void calculate_kline();

void MktDataHandler::calculate_kline()
{

}