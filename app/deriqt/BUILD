package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "CTPTrader",
    srcs = [
	    "CTPMdHandler.cpp",
	    "CTPMdHandler.h",
	    "CTPTraderHandler.cpp",
	    "CTPTraderHandler.h",
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
		"OrderSignal.h",
		"OrderSignal.cpp",
		"Factor.h",
		"Factor.cpp",
		"UserStruct.h"
	],
	copts = [
	"-D_GLIBCXX_USE_CXX11_ABI=1",
	"-std=c++14",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@zlib//:zlib",
        "//base:build_info",
        "//base:init",
        "@com_github_google_glog//:glog",
        "//third_party/ctp:ctp",
		"@boost//:lockfree",
		"@boost//:interprocess",
		"@boost//:system",
		"@boost//:thread",
		"@boost//:circular_buffer",
		 "@libtorch_archive//:torch_cpu_c",
	],
	linkopts = [
    "-lrt",
	"-lpthread"
],
)


cc_binary(
    name = "SimNow",
    srcs = [
		"CTPMdHandler.cpp",
		"CTPMdHandler.h",
		"CTPTraderHandler.cpp",
		"CTPTraderHandler.h",
		"DataStrategy.cpp",
		#"DataStrategy.h",
		"define.h",
		"helper.h",
		"QTStrategyBase.cpp",
		"QTStrategyBase.h",
		"recordio.cpp",
		"recordio.h",
		"recordio_range.h",
		"TickToKlineHelper.cpp",
		"TickToKlineHelper.h",
		"timer.h",
		#"TStrategy.h",
		"GMSimTrader.h",
		"GMSimTrader.cpp",
		"OrderSignal.h",
		"OrderSignal.cpp",
		"Factor.h",
		"Factor.cpp",
		"UserStruct.h",
		"simnow_order.h",
		"simnow_order.cpp"

	],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@zlib//:zlib",
        "//base:build_info",
        "//base:init",
        "@com_github_google_glog//:glog",
        "//third_party/simnow:simnow",
		"//third_party/gmsimtrade:gmsimtrade",
		"@boost//:lockfree",
		"@boost//:interprocess",
		"@boost//:system",
		"@boost//:thread",
		"@boost//:circular_buffer",
	],
	linkopts = [
    "-lrt"
],
)

