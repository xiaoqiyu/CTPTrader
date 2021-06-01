load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "cpplib_test",
    srcs = ["cpplib_test.cc"],
    deps = [
        "//src/lib:CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "sort_test",
    srcs = ["sort_test.cc"],
    deps = [
        "//src/lib/sort:SortLib",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "search_test",
    srcs = ["search_test.cc"],
    deps = [
        "//src/lib/search:SearchLib",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_fixture",
    srcs = ["test_fixture.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "gmock",
    srcs = ["gmock.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "gmock2",
    srcs = ["gmock2.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
)
