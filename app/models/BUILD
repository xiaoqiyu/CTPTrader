package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "ModelResearch",
    srcs = [
		"main.cpp",
        "data_analysis.h",
        "data_analysis.cpp",
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
