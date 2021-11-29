cc_library(
    name = "rapidjson",
    srcs = [],
    hdrs = glob([
        "include/rapidjson/*.h",
        "include/rapidjson/internal/*.h",
        "include/rapidjson/error/*.h",
    ]),
    includes = ["include/"],
    defines = ["RAPIDJSON_HAS_STDSTRING=1","RAPIDJSON_HAS_CXX11_RVALUE_REFS=1"],
    visibility = ["//visibility:public"],
    copts = [
        "-std=c++11",
    ],
)
