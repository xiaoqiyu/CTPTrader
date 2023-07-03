package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "consumer",
    srcs = [
	    "consumer.cpp",
	],
    deps = [
		"@boost//:lockfree",
		"@boost//:interprocess",
		"@boost//:system",
		"@boost//:thread",
		"@boost//:circular_buffer",
	],
	linkopts = [
        "-lrt"
    ],
)

cc_binary(
    name = "producer",
    srcs = [
		"producer.cpp",
	],
    deps = [
		"@boost//:lockfree",
		"@boost//:interprocess",
		"@boost//:system",
		"@boost//:thread",
		"@boost//:circular_buffer",
	],
	linkopts = [
        "-lrt"
    ],
)

