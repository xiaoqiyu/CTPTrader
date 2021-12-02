package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "simtrade",
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
        "@com_github_gflags_gflags//:gflags",
        "@zlib//:zlib",
        "//base:build_info",
        "//base:init",
        "@com_github_google_glog//:glog",
        "//third_party/gmsimtrade:gmsimtrade",
	],
)
