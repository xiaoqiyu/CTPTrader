package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "CTPTrader",
    srcs = [
	    "CTPMdHandler.cpp",
	    "CTPMdHandler.h",
	    "CTPTraderHandler.cpp",
	    "CTPTraderHandler.h",
	    "DataStrategy.cpp",
	    "DataStrategy.h",
	    "define.h",
	    "helper.h",
	    "main.cpp",
	    "QTStrategyBase.cpp",
	    "QTStrategyBase.h",
	    "recordio.cpp",
	    "recordio.h",
	    "recordio_range.h",
	    "TickToKlineHelper.cpp",
	    "TickToKlineHelper.h",
        "timer.h",
		"TStrategy.h",
		"GMSimTrader.h",
		"GMSimTrader.cpp"
	],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@zlib//:zlib",
        "//base:build_info",
        "//base:init",
        "@com_github_google_glog//:glog",
        "//third_party/ctp:ctp",
		"//third_party/gmsimtrade:gmsimtrade",
		"@boost//:lockfree",
		"@boost//:interprocess",
		"@boost//:system",
		"@boost//:thread",
	],



)
