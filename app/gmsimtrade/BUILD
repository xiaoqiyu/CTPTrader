package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "simtrade",
    srcs = [
		"main.cpp",
        "GMSimTrader.h",
        "GMSimTrader.cpp",
        "define.h",
        "recordio.h",
        "recordio.cpp",
        "recordio_range.h",
	],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@zlib//:zlib",
        "//base:build_info",
        "//base:init",
        "@com_github_google_glog//:glog",
        "//third_party/gmsimtrade:gmsimtrade",
	],
)
