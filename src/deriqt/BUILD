load("@rules_cc//cc:defs.bzl", "cc_binary")

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
	],
    deps = [
	    "//src/lib/ctp:ctp",
        "@com_github_gflags_gflags//:gflags",
        "@glog//:glog",
        "@zlib//:zlib",
	],
)
