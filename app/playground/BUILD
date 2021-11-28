package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = [
		"main.cpp",
        "recordio.h",
        "recordio.cpp",
        "recordio_range.h",
        "GMSimTrader.h",
        "GMSimTrader.cpp",
        "define.h",
        
	],
    deps = [
        "//external:gflags",
        "//external:zlib",
        "//base:build_info",
        "//base:init",
        "//external:glog",
        "//third_party/gmsimtrade:gmsimtrade",
        "//third_party/boost:system",
        "//third_party/boost:thread",
	],
)
