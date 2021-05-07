#include <iostream>
#include "QTStrategyBase.h"

// void QTStrategyBase::on_tick(CThostFtdcDepthMarketDataField *pDepthMarketData)
// {
// 	// std::cout<<"Push data to queue: "<<pDepthMarketData->InstrumentID<<std::endl;
// 	DataField data =  DataField();
// 	data.data_type = FDEPTHMKT;
// 	CThostFtdcDepthMarketDataField *mkt_data = new CThostFtdcDepthMarketDataField();
// 	*mkt_data = *pDepthMarketData;
// 	data._data = mkt_data;
// 	this->mktdata_queue.push(data);

// }

void QTStrategyBase::process_tick()
{
	std::cout << "============================Start Process Data==========================" << std::endl;
	try
	{
		while (true)
		{
			// DataField data = this->mktdata_queue.pop();
			DataField data = this->p_md_handler->get_data_queue()->pop();
			switch (data.data_type)
			{
			case FDEPTHMKT: //期货深度行情数据
			{
				if (data._data)
				{
					// CThostFtdcDepthMarketDataField *pDepthMarketData = (CThostFtdcDepthMarketDataField *)data._data;
					CThostFtdcDepthMarketDataField *pDepthMarketData = reinterpret_cast<CThostFtdcDepthMarketDataField *>(data._data);
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
											<< pDepthMarketData->AskPrice1 << ","
											<< pDepthMarketData->AskVolume1 << ","
											// << pDepthMarketData->AveragePrice-pDepthMarketData->LastPrice<<"," //agerage price include contract size
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
					delete pDepthMarketData;
					KLineDataType *p_kline_data = new KLineDataType();
					bool ret = this->p_kline_helper->KLineFromRealtimeData(pDepthMarketData, p_kline_data);

					if(ret)
					{
						// std::cout << "k line:" << pDepthMarketData->InstrumentID << ":" << p_kline_data->open_price <<", "<< p_kline_data->high_price << std::endl;
						this->kline_outfile << pDepthMarketData->InstrumentID << ","
											<< pDepthMarketData->UpdateTime << ","
											<< p_kline_data->open_price << ","
											<< p_kline_data->high_price << ","
											<< p_kline_data->low_price << ","
											<< p_kline_data->close_price << ","
											<< p_kline_data->volume << std::endl;
					}
					delete p_kline_data;
					//计算因子和下单信号
				}
				if (data.error)
				{
					std::cout <<"handle error in market data subscribe" << std::endl;
					// delete data.error;
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

void QTStrategyBase::calculate_kline(){};


void QTStrategyBase::start()
{
	// this->data_thread.join();
}
void QTStrategyBase::stop()
{
	CThostFtdcUserLogoutField reqUserLogout = {0};
    strcpy(reqUserLogout.BrokerID, this->broker_id.c_str());
    strcpy(reqUserLogout.UserID, this->user_id.c_str());
    this->p_trader_handler->ReqUserLogout(&reqUserLogout, nRequestID++);
    sleep(5);
}


void QTStrategyBase::insert_limit_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType order_ref,  TThostFtdcDirectionType direction,TThostFtdcInstrumentIDType instrumentID)
{
	CThostFtdcInputOrderField input_order_field = {0};
	strcpy(input_order_field.InstrumentID, instrumentID);
	strcpy(input_order_field.OrderRef, order_ref);
	input_order_field.VolumeTotalOriginal = volume;
	input_order_field.LimitPrice = limit_price;
	input_order_field.Direction = direction;
	input_order_field.OrderPriceType = '2';
	this->p_trader_handler->ReqOrderInsert(&input_order_field, nRequestID);
}
void QTStrategyBase::insert_market_order(TThostFtdcPriceType limit_price, TThostFtdcVolumeType volume, TThostFtdcOrderRefType order_ref, TThostFtdcOrderPriceTypeType order_price_type, TThostFtdcDirectionType direction, TThostFtdcInstrumentIDType instrumentID)
{
	CThostFtdcInputOrderField input_order_field = {0};
	strcpy(input_order_field.InstrumentID, instrumentID);
	strcpy(input_order_field.OrderRef, order_ref);
	input_order_field.VolumeTotalOriginal = volume;
	input_order_field.LimitPrice = limit_price;
	input_order_field.Direction = direction;
	input_order_field.OrderPriceType = order_price_type;
	this->p_trader_handler->ReqOrderInsert(&input_order_field, nRequestID);
}

void QTStrategyBase::release()
{
	mkt_depth_outfile.close();
	kline_outfile.close();
	delete p_kline_helper;
	// delete mktdata_queue;
	delete p_order_queue;
	this->p_md_handler->release();
	this->p_trader_handler->exit();
}


