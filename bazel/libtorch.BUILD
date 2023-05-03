cc_library(
    name = "torch_cpu_c",
    srcs = [
        "lib/libtorch.so",
        "lib/libc10.so",
        "lib/libtorch_cpu.so",
    ],
    linkopts = [
        "-ltorch",
        "-ltorch_cpu",
        "-lc10",
        "-lpthread",
    ],
    hdrs = glob(["include/**/*.h"]),
    includes = [
        "include",
        "include/torch/csrc/api/include",
        "include/THC",
        "include/TH",
    ],
    copts = [
	"-D_GLIBCXX_USE_CXX11_ABI=1",
	"-std=c++14",
    ],
    visibility = ["//visibility:public"]
)
