# third_party/usr_local.BUILD
# Demos how to use third party include/lib files
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "gmsimtrade",
  hdrs = [
     "include/gmtrade_def.h",
     "include/gmtrade.h",
     "include/UserStruct.h"

  ],
  srcs = [
    "lib/libgmtrade.so",
  ],
  includes = [
    "include",
  ],
  visibility = ["//visibility:public"],
)

