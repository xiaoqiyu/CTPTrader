package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
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
        "models/data_analysis.h",
        "models/data_analysis.cpp",
        "timer.h",
		"TStrategy.h"
	],
    deps = [
        "//external:gflags",
        "//external:zlib",
        "//base:build_info",
        "//base:init",
        "//external:glog",
        "//third_party/ctp:ctp",
	],
)
