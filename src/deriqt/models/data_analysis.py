from pprint import pp
import matplotlib.pyplot as plt
from matplotlib.text import get_rotation
import numpy as np 
import pandas as pd
import os
import subprocess
import datetime

# fout<<p_mkt->InstrumentID<<","<<p_mkt->UpdateTime<<"."<<p_mkt->UpdateMillisec<<","
# <<p_mkt->Turnover<<","<<p_mkt->Volume<<","<<p_mkt->LastPrice<<","<<p_mkt->AveragePrice<<","
# <<p_mkt->AskPrice1<<","<<p_mkt->AskVolume1<<","<<p_mkt->BidPrice1<<","
# <<p_mkt->BidVolume1<<std::endl;

def check_records(ts_lst=[], start_ts="09:30:00", end_ts="10:15:00"):
    _start_ts = datetime.datetime.strptime(start_ts,'%H:%M:%S')
    _start_ts_const = datetime.datetime.strptime(start_ts,'%H:%M:%S')
    # print(_start_ts, start_ts,end_ts)
    _end_ts = datetime.datetime.strptime(end_ts,'%H:%M:%S')
    ts_record = {}
    while(_start_ts<=_end_ts):
        _start_ts = _start_ts+datetime.timedelta(seconds=1)
        _k = _start_ts.strftime('%H:%M:%S')
        ts_record.update({_k:0})
        # print(_k)
    for item in ts_lst:
        # print(item)

        _ts1 = datetime.datetime.strptime(item,'%H:%M:%S')
        # print(_ts1, _start_ts_const, _end_ts,_ts1>=_start_ts_const and _ts1<=_end_ts)
        if(_ts1>=_start_ts_const and _ts1<=_end_ts):
            # print("check ts")
            if item in ts_record:
                ts_record[item] += 1

    cnt0, cnt1, cnt2 = 0, 0, 0
    for _k,_v in ts_record.items():
        _k1 = datetime.datetime.strptime(_k,'%H:%M:%S')
        # print("record", _k, _k1,_start_ts, _v)
        # print(_k, _v)
        if _k1>=_start_ts_const and _k1<=_end_ts:
            if _v >2:
                # print(_k,_v)
                pass
            elif _v>=2:
                cnt2 += 1
                # print("record",_k, _v)
            elif _v>0:
                cnt1 += 1
            else:
                cnt0 += 1
                # print(_k,_v)
    print(cnt0, cnt1, cnt2, cnt0/(cnt0+cnt1+cnt2))


def get_data(instrument_id="", trade_date="", start_ts="09:03:00", end_ts="09:15:00"):
    _file_name = "cache/mkt_pycache/{0}_depth_market_data_{1}.txt".format(instrument_id, trade_date)
    try:
        f = open(_file_name)
    except Exception as ex:
        _cmd = "./bazel-bin/src/deriqt/main 1 "+instrument_id+" "+trade_date
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
        check_records(ts_lst=min_lst, start_ts=start_ts, end_ts=end_ts)
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
        plt.savefig('cache/analysis_pycache/{0}_{1}.png'.format(instrument_id, trade_date))


def get_file_lst(trade_date=''):
    lst = os.listdir("cache/")
    return [item for item in lst if trade_date in item]

if __name__ == "__main__":
#     subprocess.call("cd ~/projects/CTPTrader", shell=True)
#     subprocess.call("pwd", shell=True)

#     subprocess.call("ls", shell=True)
    # subprocess.call("./main 1 hc2110 20210518")
    # get_data("i2109", "20210601", start_ts="09:04:00", end_ts="10:15:00")
    # get_data("i2109", "20210601", start_ts="10:15:00", end_ts="11:30:00")
    get_data("y2109", "20210607", start_ts="13:30:00", end_ts="15:30:00")
    # check_records(ts_lst=["09:30:01.0","09:30:02.0"])
    # lst = get_file_lst('20210601')
    # import pprint
    # pprint.pprint(lst)
    # get_data(lst[0].split('_')[0], "20210601", start_ts="09:04:00", end_ts="10:15:00")
        
