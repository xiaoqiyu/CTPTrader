import matplotlib.pyplot as plt
from matplotlib.text import get_rotation
import numpy as np 
import pandas as pd
import os
import subprocess

# fout<<p_mkt->InstrumentID<<","<<p_mkt->UpdateTime<<"."<<p_mkt->UpdateMillisec<<","
# <<p_mkt->Turnover<<","<<p_mkt->Volume<<","<<p_mkt->LastPrice<<","<<p_mkt->AveragePrice<<","
# <<p_mkt->AskPrice1<<","<<p_mkt->AskVolume1<<","<<p_mkt->BidPrice1<<","
# <<p_mkt->BidVolume1<<std::endl;

def get_data(instrument_id="", trade_date=""):
    _file_name = "cache/p_{0}_depth_market_data_{1}.txt".format(instrument_id, trade_date)
    try:
        f = open(_file_name)
    except Exception as ex:
        _cmd = "./main 1 "+instrument_id+" "+trade_date
        print(_cmd)
        os.system(_cmd)
    with open(_file_name) as f:
        lines = f.readlines()
        last_price_lst =[]
        avg_price_lst = []
        bid1_pricce_lst = []
        ask1_pricce_lst = []
        bid1_volume_lst = []
        ask1_volume_lst  =[]
        turnover_lst = []
        volume_lst = []
        min_lst = []
        for item in lines:
            # print(item)
            _instrument_id, update_msec, turnover, volume, last_price, avg_price,ask_price1, ask_vol1, bid_price1, bid_vol1 = item.split(',')
            # print(last_price)
            last_price_lst.append(float(last_price))
            avg_price_lst.append(float(avg_price))
            bid1_pricce_lst.append(float(bid_price1))
            ask1_pricce_lst.append(float(ask_price1))
            bid1_volume_lst.append(int(bid_vol1))
            ask1_volume_lst.append(int(ask_vol1))
            min_lst.append(update_msec.split('.')[0][:8])
        # print(len(lines))
        print(last_price_lst[:5])
        # min_lst = sorted(min_lst)
        print(min_lst[:5], min_lst[-5:])
        x = list(range(len(last_price_lst)))
        print(len(x))
        # x = np.arange(0, math.pi*2, 0.05)
        fig = plt.figure()
        ax = fig.add_axes([0.1, 0.1, 0.8, 0.8]) # main axes
        # y = np.sin(x)
        ax.plot(x, last_price_lst)
        # ax.set_xlabel(‘angle’)
        ax.set_title('{0}_{1}'.format(instrument_id, trade_date))
        x_idx = range(0, len(last_price_lst), 600)
        xtick_labels = []
        for _idx in x_idx:
            xtick_labels.append(min_lst[_idx])

        # ax.set_xticks(x_idx)
        # ax.set_xticklabels(xtick_labels)
        plt.xticks(x_idx, xtick_labels, rotation=60, FontSize=6)
        
        # ax.set_yticks([-1,0,1])
        plt.savefig('{0}_{1}.png'.format(instrument_id, trade_date))



if __name__ == "__main__":
#     subprocess.call("cd ~/projects/CTPTrader", shell=True)
#     subprocess.call("pwd", shell=True)

#     subprocess.call("ls", shell=True)
    # subprocess.call("./main 1 hc2110 20210518")
    get_data("rb2110", "20210524")



        
