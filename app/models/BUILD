package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = [
		"main.cpp",
        "data_analysis.h",
        "data_analysis.cpp",
        "recordio.h",
        "recordio.cpp",
        "recordio_range.h"
	],
     deps = [
            "@com_github_gflags_gflags//:gflags",
            "@zlib//:zlib",
            "//base:build_info",
            "//base:init",
            "@com_github_google_glog//:glog",
            "//third_party/ctp:ctp",
		],
)
