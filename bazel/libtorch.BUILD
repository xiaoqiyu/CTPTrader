cc_library(
    name = "torch_cpu_c",
    srcs = [
        "lib/libtorch.so",
        "lib/libc10.so",
        "lib/libtorch_cpu.so",
        "lib/libgomp-52f2fd74.so.1",
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

cc_library(
    name = "torch",
    srcs = [
        "lib/libc10.so",
        "lib/libc10_cuda.so",
        "lib/libtorch.so",
        "lib/libtorch_cpu.so",
        "lib/libtorch_cuda.so",
        "lib/libtorch_cuda_linalg.so",
        "lib/libtorch_global_deps.so",
        "lib/libnvfuser_codegen.so",
        "lib/libgomp-52f2fd74.so.1",
        "lib/libcudart-d0da41ae.so.11.0",
        "lib/libnvToolsExt-847d78f2.so.1",
        "lib/libcudnn.so.8",
        "lib/libcublas-3b81d170.so.11",
        "lib/libnvrtc-672ee683.so.11.2",
        "lib/libcublasLt-b6d14a74.so.11",
    ],
    linkopts = [
        "-ltorch",
        "-ltorch_cuda",
        "-lc10",
        "-lc10_cuda",
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
