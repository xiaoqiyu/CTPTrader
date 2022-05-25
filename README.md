# CTPTrader Includes:
1. Connected to CTP Market Front and Trade Front;
2. Subscribe depth market data, cache and calculate factor online;
3. From factor, calculate trading signal, and place the order;
4. Maintain order/transaction/positions;
5. The project support 3 modes:
   - mode 0: subscribe tick data
   - mode 1: simulation through GoldMine
   - mode 2: live trade through CTP
6. Strategy Evaluations;

# Run a strategy
1. config file
    - test.ini: account login information
    - daily_cache.ini: contract statics updated daily
    - '{}_{}.ini'.format(strategy_name, product_id), e.g. 'future_trend_rb.ini', params for running the strategy, each sub strategy in in one subsection
2.  Strategy run demo: "GLOG_logtostderr=1 ./bazel-bin/app/deriqt/CTPTrader 2 rb  /xx/xx/../test.ini"
    
    
    2.1 entrance point: check demo main.cpp 
    
    
    2.2 Market process:
    - Start a QTStrategyBase objStrategy;
    - objStrategy.init(): init of the ctp trade and market handler, and other resource allocation
    - objStrategy.start(): start subscribe the depth market, cache, calculate factor, and push to share mem Q
    - objStrategy.stop(): join thread
    - objStrategy.release(): release resource 


    2.3 Trade process: 
    - Start a QTStrategyBase objStrategy
    - objStrategy.init(): init of the ctp trade handler, and other resource allocation
    - objStrategy.start(): start listen to factor in share mem Q, calculate signal, and place order 
        - ctp main thread
        - task_thread: process ctp callback
        - signal_thread: get factor and calculate signal, push order to order queue
        - risk_monitor_thread: check account risk factor 
    - objStrategy.stop(): join thread
    - objStrategy.release(): release resource 

# How a strategy work
1. depth market to factor, share memory of ring buffer from md to td
2. factor to signal
3. signal to place order
4. risk monitor

# When a strategy terminate
1. close positions
2. end market subscribe, factor/signal/risk thread
3. ctp release


# 项目包括
1. 连接CTP的行情前置和交易前置；
2. 订阅深度行情，存储行情以及实时计算因子；
3. 跟进因子计算交易信号，根据信号下单；
4. 维护委托，成交以及持仓情况；
5. 项目支持三种模式：
    - 模式0： 订阅深度行情；
    - 模式1： 通过掘金进行仿真交易
    - 模式2： 通过CTP进行实盘交易
6. 策略绩效分析
