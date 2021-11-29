package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # BSD/MIT-like license (for bzip2)

cc_library(
    name = "bzip2",
    srcs = [
        "blocksort.c",
        "bzlib.c",
        "compress.c",
        "crctable.c",
        "decompress.c",
        "huffman.c",
        "randtable.c",
        "bzlib.h",
        "bzlib_private.h",
    ],
    hdrs = ["bzlib.h"],
    copts = [
        ],
    includes = ["."],
)

cc_binary(
    name = "bin/bzip2",
    srcs = [
        "bzip2.c",
        ],
    deps = [
        ":bzip2"
        ],
    copts = [
        "-Wno-unused-result",
        "-Wno-unused-but-set-variable",
        ],
)
