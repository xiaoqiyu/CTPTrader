#ifndef GMTRADE_H
#define GMTRADE_H

#include <stddef.h>
#include "gmtrade_def.h"

#ifdef WIN32
#ifdef GMSDKC_EXPORTS  
#define GM_TRADE_API __declspec(dllexport)
#else
#define GM_TRADE_API __declspec(dllimport)
#endif
#else
#define GM_TRADE_API
#endif

namespace gmtrade
{

	class GM_TRADE_API Trade
	{
	public:
		Trade(const char *token);
		Trade();
		virtual ~Trade();

	public: //基础函数

		//开始接收事件
		int start();

		//停止接收事件
		void stop();

		//设置用户token
		void set_token(const char *token);

		//设置服务地址
		void set_endpoint(const char *serv_addr);


	public: //交易函数

		int login(const char *account_ids);

		//查询指定交易账号状态
		int get_account_status(const char *account, AccountStatus &as);

		//查询所有交易账号状态
		DataArray<AccountStatus>* get_all_account_status();

		//按指定量委托
		Order order_volume(const char *symbol, int volume, int side, int order_type, int position_effect, double price = 0, const char *account = NULL);

		//按指定价值委托
		Order order_value(const char *symbol, double value, int side, int order_type, int position_effect, double price = 0, const char *account = NULL);

		//按总资产指定比例委托
		Order order_percent(const char *symbol, double percent, int side, int order_type, int position_effect, double price = 0, const char *account = NULL);

		//调仓到目标持仓量
		Order order_target_volume(const char *symbol, int volume, int position_side, int order_type, double price = 0, const char *account = NULL);

		//调仓到目标持仓额
		Order order_target_value(const char *symbol, double value, int position_side, int order_type, double price = 0, const char *account = NULL);

		//调仓到目标持仓比例（总资产的比例）
		Order order_target_percent(const char *symbol, double percent, int position_side, int order_type, double price = 0, const char *account = NULL);

		//平当前所有可平持仓
		DataArray<Order>* order_close_all();

		//委托撤单
		int order_cancel(const char *cl_ord_id, const char *account = NULL);

		//撤销所有委托
		int order_cancel_all();

		//委托下单
		Order place_order(const char *symbol, int volume, int side, int order_type, int position_effect, double price = 0, int order_duration = 0, int order_qualifier = 0, double stop_price = 0, const char *account = NULL);

		//查询资金
		int get_cash(Cash &cash, const char *accounts = NULL);

		//查询委托
		DataArray<Order>* get_orders(const char *account = NULL);

		//查询未结委托
		DataArray<Order>* get_unfinished_orders(const char *account = NULL);

		//查询成交
		DataArray<ExecRpt>* get_execution_reports(const char *account = NULL);

		//查询持仓
		DataArray<Position>* get_position(const char *account = NULL);


	public: //事件函数

		//委托变化
		virtual void on_order_status(Order *order);
		//执行回报
		virtual void on_execution_report(ExecRpt *rpt);
		//实盘账号状态变化
		virtual void on_account_status(AccountStatus *account_status);
		//错误产生
		virtual void on_error(int error_code, const char *error_msg);
		//数据已经连接上
		virtual void on_trade_data_connected();
		//交易连接断开了
		virtual void on_trade_data_disconnected();

	};

} //namespace gmtrade

#endif
