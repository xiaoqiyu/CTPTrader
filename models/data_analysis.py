import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd
# instrumentid, actiondate,updatetime,lastprice,presettlementprice,precloseprice,openprice,highprice,lowprice,averageprice,
# close,volume,turnover,settlementprice,upperlimitprice,lowerlimitprice,bidprice1,bidvolume1,askprice1,askvolume1,preopeninterest,
# openinterest,predelta,currdeltaF
with open('../cache/rb2110_depth_market_data_20210507.txt') as f:
    lines = f.readlines()
    last_price_lst = [float(item.split(',')[3]) for item in lines]
    avg_price_lst = [float(item.split(',')[9])/10 for item in lines]
    bid_price_lst = [float(item.split(',')[-9]) for item in lines]
    ask_price_lst = [float(item.split(',')[-7]) for item in lines]
    k1 = 0.2
    k2 = 0.5
    
    print(ask_price_lst[:10])
    print(bid_price_lst[:10])
    plt.plot(last_price_lst)
    plt.plot(avg_price_lst)
    print(np.std(np.array([item-avg_price_lst[idx] for idx,item in enumerate(last_price_lst)])))
    # plt.plot(bid_price_lst)
    # plt.plot(ask_price_lst)
    plt.savefig('tick_analysis.jpg')
    
