# third_party/usr_local.BUILD
# Demos how to use third party include/lib files
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "simnow",
  hdrs = [
     "include/INIReader.h",
     "include/ThostFtdcMdApi.h",
     "include/ThostFtdcTraderApi.h",
     "include/ThostFtdcUserApiDataType.h",
     "include/ThostFtdcUserApiStruct.h",
  ],
  srcs = [
    "lib/libthostmduserapi_se.so",
    "lib/libthosttraderapi_se.so",
  ],
  includes = [
    "include",
  ],
  visibility = ["//visibility:public"],
)

