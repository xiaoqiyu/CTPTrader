# Description:
#   ImageMagick® is a software suite to create, edit, compose, or convert bitmap images.

licenses(["notice"])  # Apache 2.0 license

genrule(
    name = "config_h",
    srcs = ["@//bazel/imagemagick:config.h"],
    outs = ["config/config.h"],
    cmd = "cp $< $@",
)

genrule(
    name = "magick-baseconfig_h",
    srcs = ["@//bazel/imagemagick:magick-baseconfig.h"],
    outs = ["MagickCore/magick-baseconfig.h"],
    cmd = "cp $< $@",
)

genrule(
    name = "version_h",
    srcs = ["@//bazel/imagemagick:version.h"],
    outs = ["MagickCore/version.h"],
    cmd = "cp $< $@",
)

copts = [
    "-DMAGICKCORE_QUANTUM_DEPTH=16",
    "-DMAGICKCORE_HDRI_ENABLE=0",
    "-DHAVE_CONFIG_H",
    ]

cc_library(
    name = "libmagick",
    srcs = glob([
        "coders/*.c",
        "coders/*.h",
        "filters/*.c",
        "filters/*.h",
        "MagickCore/*.c",
        "MagickCore/*.h",
        "MagickWand/*.c",
        "MagickWand/*.h",
    ]) + [
        ":config_h",
        ":magick-baseconfig_h",
        ":version_h",
    ],
    hdrs = [
        "MagickCore/magick-baseconfig.h",
    ],
    copts = copts,
    deps = [
        #"@bzip2//:bzip2",
        "@zlib//:zlib",
        "@org_bzip_bzip2//:bz2lib",
        "@fftw//:fftw",
        "@gif//:gif",
        "@tiff//:tiff",
        "@libjpeg//:jpeg",
        "@org_libpng_libpng//:libpng",
        #"@xz//:lzma",
        "@org_lzma_lzma//:lzma",
        ],
    includes = ["."],
    linkopts = [
        "-lpthread",
        ],
    visibility = ["//visibility:public"],
    )


tools=[
    "animate", "compare", "composite", "conjure", "convert", "display", "identify", "import", "magick", "magick-script", "mogrify", "stream",
    ]

[cc_binary(
    name = "bin/{}".format(tool),
    srcs = glob([
        "utilities/{}.c".format(tool),
        "MagickCore/*.h",
        "MagickWand/*.h",
        ]),
    copts = copts,
    deps = [
        ":libmagick",
        ],
    ) for tool in tools]
