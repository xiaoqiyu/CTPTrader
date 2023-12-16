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
5. Update local order tabel:
    - In order callback,for first order callback, insert table with order_id1
    - In order callback,when order_id1 exist, create order_id2(accept by exchange), remove order_id1 from table, and insert order_id2 into table
    - In order callback,when order is canceled, remove the order from order table
    - In trade callback,when order is completed traded, remove the order from order table

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


# 报单以及订单管理：

verify_order_condition_ctp:
1. 信号触发的时间如果超过 signal_delay，则忽略
2. long signal:
- 当前有该合约/品种的持仓
- 空头持仓：买入平仓，量为当前的持仓数量(TodayPosition),价格为开仓成本-止盈
- 多头持仓：买入开仓，量为该品种限制仓位-当前该品种已持有仓位，价格为市价(up_limit)
- 当前该品种没有持仓
- 买入开仓，量为该品种限制仓位，价格为市价（up_limit）
3. short signal:
- 当前有该品种持仓
- 多头持仓：卖出平仓，量为当前的持仓数量（TodayPosition），价格为开仓成本+止盈
- 空头持仓：卖出开仓，量为该品种限制仓位-当前该品种已持有仓位，价格为市价(down_limit)
- 当前该品种没有持仓
- 卖出开仓，量为该品种限制仓位，价格为市价（down_limit）
4. stop signal:
- 返回 OrderVerify_valid,到下单

如果订单valid,则用tradehandler 报单，然后lock,等待 order_complete_
本地订单表维护：
- order_id1: "FrontID(登录成功返回）_SessionID（登录成功返回）_OrderRef（报单请求 填入，本地维护）"
- order_id2: "ExchangeID_OrderSysID（交易所返回）"
订单回报更新流程（本地订单表维护：m_all_order）：
- 如果订单返回是策略登录前的（当日之前的报单），则忽略，不做重复更新
- 收到第一个callback,CTP风控通过，在本地订单表m_all_orders插入该订单，id 为order_id1
- 收到第二个callback,交易所验证通过，更新交易所返回OrderSysID,如果订单返回是cancle,报单不成功，则删除本地订单表中order_id1,并释放order_complete_锁，
如果返回是接受，则更新本地订单id从order_id1到order_id2和相应的订单状态
- 收到第三个callback,成交信息，如果状态是cancle，则删除本地订单order_id2, 释放order_complete锁（如果是成交的在成交回报中更新）