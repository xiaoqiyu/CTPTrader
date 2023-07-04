cc_binary(
    name = "example",
    srcs = ["example.cpp"],
    copts = [
	"-D_GLIBCXX_USE_CXX11_ABI=1",
	"-std=c++14",
    ],
    linkopts = [
        "-lpthread",
    ],
    deps = [
        "@libtorch_archive//:torch_cpu_c",
    ],
)

cc_binary(
    name = "example1",
    srcs = ["example1.cpp"],
    copts = [
	"-D_GLIBCXX_USE_CXX11_ABI=1",
	"-std=c++14",
    ],
    linkopts = [
        "-lpthread",
    ],
    deps = [
        "@libtorch_archive//:torch",
    ],
)
