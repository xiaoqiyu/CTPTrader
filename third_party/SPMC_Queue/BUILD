# third_party/usr_local.BUILD
# Demos how to use third party include/lib files
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "SPMC_Queue",
  hdrs = [
     "SPMCQueue.h",
  ],
  srcs = [
    "SPMCQueue.h",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "multhread",
  srcs = [
    "example/multhread.cc",
    "example/Statistic.h"
  ],
  deps = [
    ":SPMC_Queue",
  ],
  includes = [
    "example",
  ],
  linkopts = [
    "-pthread"
  ],
)

cc_binary(
  name = "shm_reader",
  srcs = [
    "example/shm_reader.cc",
    "example/shm.h"
  ],
  deps = [
    ":SPMC_Queue",
  ],
  includes = [
    "example",
  ],
  linkopts = [
    "-lrt"
  ],
)

cc_binary(
  name = "shm_writer",
  srcs = [
    "example/shm_writer.cc",
    "example/shm.h"
  ],
  deps = [
    ":SPMC_Queue",
  ],
  includes = [
    "example",
  ],
  linkopts = [
    "-lrt"
  ],
)

cc_binary(
  name = "multhread_composite_struct",
  srcs = [
    "example/multhread.cc",
    "example/Statistic.h"
  ],
  deps = [
    ":SPMC_Queue",
  ],
  includes = [
    "example",
  ],
  linkopts = [
    "-pthread"
  ],
)
