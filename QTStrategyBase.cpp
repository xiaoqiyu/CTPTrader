#include <iostream>
#include "QTStrategyBase.h"


void QTStrategyBase::on_tick()
{
	try
	{
		while (true)
		{
			DataField data = this->p_md_handler->get_data_queue()->pop();
			switch (data.data_type)
			{
			case FDEPTHMKT: //期货深度行情数据
			{
				// std::cout<<"in on_tick:"<<data.data_type<<std::endl;
				if (data._data)
				{
					CThostFtdcDepthMarketDataField *pDepthMarketData = reinterpret_cast<CThostFtdcDepthMarketDataField *>(data._data);
					// std::cout << "Save Data: " << pDepthMarketData->InstrumentID<<std::endl;//减少IO阻塞
					// std::cout<<"get fstream index:"<<std::endl;
					int _idx = this->m_filename_idx[pDepthMarketData->InstrumentID];
					// std::cout<<"fstream index is: "<<_idx<<std::endl;
					// std::cout<<"depth file stream pointer:"<<this->v_depth_outfile.size()<<std::endl;
					// std::ofstream* p_f = reinterpret_cast<std::ofstream*>(this->v_depth_outfile[_idx]);
					// std::cout<<"file stream pointer:"<<p_f<<std::endl;
					// std::string str = formatString("%s,%s,%s.%d,%f,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%d,%f,%d,%f,%f,%f\n",
					// 								pDepthMarketData->InstrumentID,
					// 								pDepthMarketData->ActionDay,
					// 								pDepthMarketData->UpdateTime,pDepthMarketData->UpdateMillisec,
					// 								pDepthMarketData->LastPrice,
					// 								pDepthMarketData->PreSettlementPrice,
					// 								pDepthMarketData->PreClosePrice,
					// 								pDepthMarketData->OpenPrice,
					// 								pDepthMarketData->HighestPrice,
					// 								pDepthMarketData->LowestPrice,
					// 								pDepthMarketData->AveragePrice,		
					// 								// pDepthMarketData->ClosePrice,
					// 								pDepthMarketData->Volume,
					// 								pDepthMarketData->Turnover,
					// 								// pDepthMarketData->SettlementPrice ,
					// 								pDepthMarketData->UpperLimitPrice ,
					// 								pDepthMarketData->LowerLimitPrice,
					// 								pDepthMarketData->BidPrice1 ,
					// 								pDepthMarketData->BidVolume1 ,
					// 								pDepthMarketData->AskPrice1 ,
					// 								pDepthMarketData->AskVolume1 ,
					// 								pDepthMarketData->PreOpenInterest ,
					// 								pDepthMarketData->OpenInterest ,
					// 								pDepthMarketData->PreDelta
					// 								// pDepthMarketData->CurrDelta
					// 								);
					std::string _depth_file_name = this->m_depth_filename[pDepthMarketData->InstrumentID];
					std::ofstream _depth_file;
					_depth_file.open(_depth_file_name, std::ios::app);
					_depth_file<< pDepthMarketData->InstrumentID << ","
											<< pDepthMarketData->ActionDay << ","
											<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << ","
											<< pDepthMarketData->LastPrice << ","
											<< pDepthMarketData->PreSettlementPrice << ","
											<< pDepthMarketData->PreClosePrice << ","
											<< pDepthMarketData->OpenPrice << ","
											<< pDepthMarketData->HighestPrice << ","
											<< pDepthMarketData->LowestPrice << ","
											<< pDepthMarketData->AveragePrice << ","
											// << pDepthMarketData->ClosePrice << ","
											<< pDepthMarketData->Volume << ","
											<< pDepthMarketData->Turnover << ","
											// << pDepthMarketData->SettlementPrice << ","
											<< pDepthMarketData->UpperLimitPrice << ","
											<< pDepthMarketData->LowerLimitPrice << ","
											<< pDepthMarketData->BidPrice1 << ","
											<< pDepthMarketData->BidVolume1 << ","
											<< pDepthMarketData->AskPrice1 << ","
											<< pDepthMarketData->AskVolume1 << ","
											<< pDepthMarketData->PreOpenInterest << ","
											<< pDepthMarketData->OpenInterest << ","
											<< pDepthMarketData->PreDelta << ","
											// << pDepthMarketData->CurrDelta << ","
											<< std::endl;

					delete pDepthMarketData;
					_depth_file.close();
					KLineDataType *p_kline_data = new KLineDataType();

					bool ret = this->v_t2k_helper[_idx]->KLineFromRealtimeData(pDepthMarketData, p_kline_data);

					if(ret)
					{
						// 	std::string str1 = formatString("%s,%s,%f,%f,%f,%f,%d\n",
						// 								pDepthMarketData->InstrumentID,
						// 								pDepthMarketData->UpdateTime,
						// 								p_kline_data->open_price,
						// 								p_kline_data->high_price,
						// 								p_kline_data->low_price,	
						// 								p_kline_data->close_price,
						// 								p_kline_data->volume);
						// std::ofstream* p_ff = this->v_kline_outfile[_idx];
						// std::cout<<"f stream pointer:"<<p_ff<<std::endl;
						// p_ff->write(str1.c_str(), str1.length());
						std::string _kline_file_name1 = this->m_kline_filename[pDepthMarketData->InstrumentID];
						std::ofstream _kline_file;
						_kline_file.open(_kline_file_name1, std::ios::app);
						_kline_file<<pDepthMarketData->InstrumentID << ","
													<<pDepthMarketData->UpdateTime << ","
													<<p_kline_data->open_price << ","
													<<p_kline_data->high_price << ","
													<<p_kline_data->low_price << ","
													<<p_kline_data->close_price << ","
													<<p_kline_data->volume<< std::endl;
						_kline_file.close();
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
	this->start_ = true;
	this->p_md_handler->SubscribeMarketData();

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

int QTStrategyBase::get_instrument_by_product(std::string product_id)
{
	std::cout<<"Query Instrument for productID:"<<product_id<<std::endl;
	CThostFtdcQryInstrumentField pQryInstrument = {0};
	std::strcpy(pQryInstrument.InstrumentID, product_id.c_str());
	return this->p_trader_handler->ReqQryInstrument(&pQryInstrument, nRequestID++);
}

int QTStrategyBase::get_investor_position(std::string investor_id, std::string broker_id)
{
	CThostFtdcQryInvestorPositionField investor_pos_fields = {0};
	std::strcpy(investor_pos_fields.InvestorID, investor_id.c_str());
	std::strcpy(investor_pos_fields.BrokerID, broker_id.c_str());
	return this->p_trader_handler->ReqQryInvestorPosition(&investor_pos_fields, nRequestID++);
}

void QTStrategyBase::stop()
{
	//TODO thread management
	this->data_thread.join(); //stop data_thread, but the ctp instance is still active
	// this->data_thread.termininate();
    // sleep(5);
}


void QTStrategyBase::release()
{
	delete p_order_queue;
	for(auto iter=v_t2k_helper.begin(); iter!=v_t2k_helper.end(); ++iter)
	{
		delete *iter;
	}
	// for(auto iter=v_depth_outfile.begin(); iter!=v_depth_outfile.end();++iter)
	// {
	// 	(*iter)->close();
	// }
	// for(auto iter=v_kline_outfile.begin(); iter!=v_kline_outfile.end(); ++iter)
	// {
	// 	(*iter)->close();
	// }
	this->p_md_handler->exit();
	this->p_trader_handler->exit();
}


