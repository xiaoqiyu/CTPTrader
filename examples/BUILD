package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "hello",
  srcs = [
    "hello.cc"
  ],
  deps = [
    "//base:build_info",
    "//base:init",
    "@com_github_google_glog//:glog",
  ],
  stamp = 1,
)

cc_test(
  name = "hello_test",
  srcs = [
    "hello_test.cc",
  ],
  deps = [
    "@com_google_googletest//:gtest_main",
  ],
)
