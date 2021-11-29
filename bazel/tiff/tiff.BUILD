licenses(["notice"])  # BSD/MIT-like license

exports_files(["LICENSE"])

genrule(
    name = "tiffconf_h",
    srcs = ["@//app/bazel/tiff:tiffconf.h"],
    outs = ["libtiff/tiffconf.h"],
    cmd = "cp $< $@",
)

genrule(
    name = "tif_config_h",
    srcs = ["@//app/bazel/tiff:tif_config.h"],
    outs = ["libtiff/tif_config.h"],
    cmd = "cp $< $@",
)

cc_library(
    name = "tiff",
    srcs = glob([
        "libtiff/*.c",
        "libtiff/*.h",
        ], exclude=[
        "libtiff/tif_win32.c",
        ]) + [
        "libtiff/tif_config.h",
        "libtiff/tiffconf.h",
        ],
    hdrs = [
        "libtiff/tiff.h",
        "libtiff/tiffconf.h",
        "libtiff/tiffio.h",
        "libtiff/tiffvers.h",
        ],
    copts = [
        "-DCCITT_SUPPORT=1",
        "-DCHECK_JPEG_YCBCR_SUBSAMPLING=1",
        "-DCXX_SUPPORT=1",
        "-DDEFAULT_EXTRASAMPLE_AS_ALPHA=1",
        "-DHAVE_FCNTL_H=1",
        "-DHAVE_GETOPT=1",
        "-DHAVE_INTTYPES_H=1",
        "-DHAVE_STDINT_H=1",
        "-DHAVE_STDLIB_H=1",
        "-DHAVE_STRING_H=1",
        "-DHAVE_UNISTD_H=1",
        "-DHAVE_CONFIG_H",
        '-DTIFF_INT32_FORMAT=\\"%d\\"',
        '-DTIFF_INT64_FORMAT=\\"%ld\\"',
        '-DTIFF_PTRDIFF_FORMAT=\\"%ld\\"',
        '-DTIFF_SIZE_FORMAT=\\"%lu\\"',
        '-DTIFF_SSIZE_FORMAT=\\"%ld\\"',
        '-DTIFF_UINT32_FORMAT=\\"%u\\"',
        '-DTIFF_UINT64_FORMAT=\\"%lu\\"',
        "-Wno-unused-but-set-variable",
        ],
    includes = [
        "libtiff",
        ],
    deps = [
        "@libjpeg//:jpeg",
        ],
    visibility = ["//visibility:public"],
)
