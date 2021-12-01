package(default_visibility = ["//visibility:public"])

licenses(["restricted"])  # GPL (for fftw)

load("@//bazel:files.bzl", "touch")


fake_headers = [
    "dft/simd/common/*.c",
    "rdft/simd/common/*.c",
    ]

cc_library(
    name = "fftw",
    srcs = glob([
        "kernel/**/*.c",
        "kernel/**/*.h",
        "api/*.c",
        "*dft/*.h",
        "*dft/*.c",
        "*dft/scalar/**/*.h",
        "*dft/scalar/**/*.c",
        "*dft/simd/*.h",
        "*dft/simd/*.c",
        "*dft/simd/common/*.h",
        "*dft/simd/common/*.c",
        "*dft/simd/generic-simd256/*.c",
        "simd-support/*.h",
        "simd-support/*.c",
        ], exclude=fake_headers) + [
        "gen/config.h",
        ],
    hdrs = glob([
        "api/*.h",
        ] + fake_headers),
    includes = [
        "api",
        "kernel",
        ],
    copts = [
        "-DFFTW_CC=\\\"Astraeus\\\"",
        "-DHAVE_GENERIC_SIMD256=1",
        "-DHAVE_MALLOC_H=1",
        "-DHAVE_MEMALIGN=1",
        "-DHAVE_STDLIB_H=1",
        "-DHAVE_STDINT_H=1",
        "-DHAVE_STRING_H=1",
        "-DHAVE_SYS_TIME_H=1",
        "-DHAVE_GETTIMEOFDAY=1",
        "-DHAVE_UINTPTR_T=1",
        "-Iexternal/fftw/dft",
        "-Iexternal/fftw/dft/scalar",
        "-Iexternal/fftw/dft/simd",
        "-Iexternal/fftw/libbench2",
        "-Iexternal/fftw/rdft",
        "-Iexternal/fftw/rdft/scalar",
        "-Iexternal/fftw/rdft/simd",
        "-Iexternal/fftw/reodft",
        "-Iexternal/fftw/simd-support",
        "-I$(GENDIR)/external/fftw/gen/",
        "-Wno-psabi",
        "-Wno-unused-variable",
        "-DPACKAGE=\\\"fftw\\\"",
        "-DPACKAGE_VERSION=\\\"Astraeus\\\"",
        "-DVERSION=\\\"Astraeus\\\"",
        ],
)
touch([
    "gen/config.h",
    ])

