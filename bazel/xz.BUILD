package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # BSD/MIT-like license (for xz)

load("@//app/bazel:files.bzl", "touch")

cc_library(
    name = "lzma",
    srcs = glob([
        "src/liblzma/*/*.c",
        "src/liblzma/*/*.h",
        "src/liblzma/*/*/*.c",
        "src/liblzma/*/*/*.h",
        "src/common/*.c",
        "src/common/*.h",
    ], exclude = [
        "src/liblzma/check/crc32_small.c",
        "src/liblzma/check/crc32_tablegen.c",
        "src/liblzma/check/crc64_small.c",
        "src/liblzma/check/crc64_fast.c",
        "src/liblzma/rangecoder/price_tablegen.c",
        "src/liblzma/lzma/fastpos_tablegen.c",
    ]) + [
        "gen/config.h",
        ],
    hdrs = [
        "src/liblzma/api/lzma.h",
    ],
    includes = ["src/liblzma/api"],
    copts = [
        "-Iexternal/xz/src/common",
        "-Iexternal/xz/src/liblzma/check",
        "-Iexternal/xz/src/liblzma/common",
        "-Iexternal/xz/src/liblzma/delta",
        "-Iexternal/xz/src/liblzma/lz",
        "-Iexternal/xz/src/liblzma/lzma",
        "-Iexternal/xz/src/liblzma/rangecoder",
        "-Iexternal/xz/src/liblzma/simple",
        "-Iexternal/xz/src/liblzma/api",
        "-I$(GENDIR)/external/xz/gen/",
        "-DHAVE_INTTYPES_H=1",
        "-DHAVE_LIMITS_H=1",
        "-DHAVE_STDBOOL_H=1",
        "-DHAVE_STDINT_H=1",
        "-DHAVE_STDLIB_H=1",
        "-DHAVE_STRING_H=1",
        "-DHAVE_SYS_TYPES_H=1",
        "-DHAVE_UNISTD_H=1",
        "-DMYTHREAD_POSIX=1",
        "-DHAVE_CONFIG_H=1",
        "-Wno-unused-function", # Surpress known warnings
        ],
)

touch([
    "gen/config.h",
    ])
