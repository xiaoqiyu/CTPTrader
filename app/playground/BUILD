package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "consumer",
    srcs = [
		"consumer.cpp"
	],
    deps = [
        "@boost//:lockfree",
        "@boost//:interprocess",
        "@boost//:system",
        "@boost//:thread",
	],
    linkopts = [
        "-lrt"
    ],
)

cc_binary(
    name = "producer",
    srcs = [
		"producer.cpp"
	],
    deps = [
        "@boost//:lockfree",
        "@boost//:interprocess",
        "@boost//:system",
        "@boost//:thread",
	],
    linkopts = [
        "-lrt"
    ],
)

cc_binary(
    name = "main",
    srcs = [
		"main.cpp"
	],
    deps = [
        "@boost//:lockfree",
        "@boost//:interprocess",
        "@boost//:system",
        "@boost//:thread",
	],
    linkopts = [
        "-lrt"
    ],
)

