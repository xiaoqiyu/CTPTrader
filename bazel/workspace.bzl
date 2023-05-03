# brpc external dependencies

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def brpc_workspace():
    #native.bind(
    #    name = "zlib",
    #    actual = "@net_zlib_zlib//:zlib",
    #)

    http_archive(
        name = "com_google_protobuf",
        strip_prefix = "protobuf-3.8.0",
        sha256 = "1e622ce4b84b88b6d2cdf1db38d1a634fe2392d74f0b7b74ff98f3a51838ee53",
        type = "zip",
        url = "https://github.com/protocolbuffers/protobuf/archive/v3.8.0.zip",
    )

    http_archive(
        name = "com_github_gflags_gflags",
        url = "https://github.com/gflags/gflags/archive/46f73f88b18aee341538c0dfc22b1710a6abedef.tar.gz",
        sha256 = "a8263376b409900dd46830e4e34803a170484707327854cc252fc5865275a57d",
        strip_prefix = "gflags-46f73f88b18aee341538c0dfc22b1710a6abedef",
    )

    native.bind(
        name = "gflags",
        actual = "@com_github_gflags_gflags//:gflags",
    )

    http_archive(
        name = "com_github_google_leveldb",
        url = "https://github.com/google/leveldb/archive/a53934a3ae1244679f812d998a4f16f2c7f309a6.tar.gz",
        sha256 = "3912ac36dbb264a62797d68687711c8024919640d89b6733f9342ada1d16cda1",
        strip_prefix = "leveldb-a53934a3ae1244679f812d998a4f16f2c7f309a6",
        build_file = str(Label("//bazel:leveldb.BUILD")),
    )

    http_archive(
        name = "com_github_google_glog",
        url = "https://github.com/google/glog/archive/a6a166db069520dbbd653c97c2e5b12e08a8bb26.tar.gz",
        sha256 = "367324e9ba0458b43583c7d773dc42b327e277353d03d4a9706104e2c15e8db8",
        strip_prefix = "glog-a6a166db069520dbbd653c97c2e5b12e08a8bb26",
        build_file = str(Label("//bazel:glog.BUILD")),
    )

    http_archive(
        name = "com_google_googletest",
        strip_prefix = "googletest-0fe96607d85cf3a25ac40da369db62bbee2939a5",
        url = "https://github.com/google/googletest/archive/0fe96607d85cf3a25ac40da369db62bbee2939a5.tar.gz",
    )

    http_archive(
        name = "yaml_cpp",
        build_file = str(Label("//bazel:yaml_cpp.BUILD")),
        strip_prefix = "yaml-cpp-yaml-cpp-0.6.2",
        url = "https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-0.6.2.tar.gz",
        sha256 = "e4d8560e163c3d875fd5d9e5542b5fd5bec810febdcba61481fe5fc4e6b1fd05",
    )

    http_archive(
        name = "tinyxml2",
        build_file = str(Label("//bazel:tinyxml2.BUILD")),
        strip_prefix = "tinyxml2-6.2.0",
        url = "https://github.com/leethomason/tinyxml2/archive/6.2.0.tar.gz",
        sha256 = "cdf0c2179ae7a7931dba52463741cf59024198bbf9673bf08415bcb46344110f",
    )

    # Abseil
    http_archive(
        name = "com_google_absl",
	    sha256 = "0db0d26f43ba6806a8a3338da3e646bb581f0ca5359b3a201d8fb8e4752fd5f8",
        urls = ["https://github.com/abseil/abseil-cpp/archive/20200225.1.tar.gz"],
        strip_prefix = "abseil-cpp-20200225.1",
    )

    http_archive(
        name = "openssl",
        url = "https://github.com/openssl/openssl/archive/OpenSSL_1_1_0g.tar.gz",
        sha256 = "8e9516b8635bb9113c51a7b5b27f9027692a56b104e75b709e588c3ffd6a0422",
        strip_prefix = "openssl-OpenSSL_1_1_0g",
        build_file = str(Label("//bazel:openssl.BUILD")),
    )

    http_archive(
        name = "curl",
        url = "https://curl.haxx.se/download/curl-7.60.0.tar.gz",
        sha256 = "e9c37986337743f37fd14fe8737f246e97aec94b39d1b71e8a5973f72a9fc4f5",
        strip_prefix = "curl-7.60.0",
        build_file = str(Label("//bazel:curl.BUILD")),
    )

    #http_archive(
    #    name = "zlib",
    #    url = "https://zlib.net/zlib-1.2.11.tar.gz",
    #    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
    #    strip_prefix = "zlib-1.2.11",
    #    build_file = str(Label("//bazel:zlib.BUILD")),
    #)

    http_archive(
        name = "imagemagick",
        url = "https://github.com/ImageMagick/ImageMagick/archive/7.0.8-7.tar.gz",
        sha256 = "fadb36b59f310e9eee5249ecb2326b323a64da6cc716dd6d08ece8ea2c780b81",
        strip_prefix = "ImageMagick-7.0.8-7",
        build_file = str(Label("//bazel/imagemagick:imagemagick.BUILD")),
    )

    #http_archive(
    #    name = "bzip2",
    #    urls = [
    #       "https://fossies.org/linux/misc/bzip2-1.0.6.tar.gz",
    #    ],
    #    sha256 = "a2848f34fcd5d6cf47def00461fcb528a0484d8edef8208d6d2e2909dc61d9cd",
    #    strip_prefix = "bzip2-1.0.6",
    #    build_file = str(Label("//bazel:bzip2.BUILD")),
    #)

    #http_archive(
    #    name = "xz",
    #    urls = [
    #      "https://tukaani.org/xz/xz-5.2.4.tar.xz",
    #      "https://sourceforge.net/projects/lzmautils/files/xz-5.2.4.tar.xz/download",
    #    ],
    #    type = "tar.xz",
    #    sha256 = "9717ae363760dedf573dad241420c5fea86256b65bc21d2cf71b2b12f0544f4b",
    #    strip_prefix = "xz-5.2.4",
    #    build_file = str(Label("//bazel:xz.BUILD")),
    #)

    http_archive(
        name = "com_github_antonovvk_bazel_rules",
        sha256 = "ba75b07d3fd297375a6688e9a16583eb616e7a74b3d5e8791e7a222cf36ab26e",
        strip_prefix = "bazel_rules-98ddd7e4f7c63ea0868f08bcc228463dac2f9f12",
        urls = [
          "https://mirror.bazel.build/github.com/antonovvk/bazel_rules/archive/98ddd7e4f7c63ea0868f08bcc228463dac2f9f12.tar.gz",
          "https://github.com/antonovvk/bazel_rules/archive/98ddd7e4f7c63ea0868f08bcc228463dac2f9f12.tar.gz",
        ],
    )

    http_archive(
        name = "org_freetype_freetype2",
        build_file = str(Label("//bazel:freetype2.BUILD")),
        sha256 = "33a28fabac471891d0523033e99c0005b95e5618dc8ffa7fa47f9dadcacb1c9b",
        strip_prefix = "freetype-2.8",
        urls = [
          "https://mirror.bazel.build/download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz",
          "http://download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz",
        ],
    )

    http_archive(
        name = "org_libgd_libgd",
        build_file = str(Label("//bazel:gd.BUILD")),
        sha256 = "a66111c9b4a04e818e9e2a37d7ae8d4aae0939a100a36b0ffb52c706a09074b5",
        strip_prefix = "libgd-2.2.5",
        urls = [
          "https://mirror.bazel.build/github.com/libgd/libgd/releases/download/gd-2.2.5/libgd-2.2.5.tar.gz",
          "https://github.com/libgd/libgd/releases/download/gd-2.2.5/libgd-2.2.5.tar.gz",
        ],
    )

    http_archive(
        name = "org_freedesktop_fontconfig",
        build_file = str(Label("//bazel/fontconfig:fontconfig.BUILD")),
        sha256 = "fd5a6a663f4c4a00e196523902626654dd0c4a78686cbc6e472f338e50fdf806",
        strip_prefix = "fontconfig-2.12.4",
        urls = [
          "https://mirror.bazel.build/www.freedesktop.org/software/fontconfig/release/fontconfig-2.12.4.tar.gz",
          "https://www.freedesktop.org/software/fontconfig/release/fontconfig-2.12.4.tar.gz",
        ],
    )

    http_archive(
        name = "com_github_libexpat_libexpat",
        build_file = str(Label("//bazel:expat.BUILD")),
        sha256 = "b5dcb503e40f615a0296a18acc6d975f2f1a3d01c7b3a4b3bb69de27bc9475c3",
        strip_prefix = "libexpat-R_2_2_4/expat",
        urls = [
          "https://mirror.bazel.build/github.com/libexpat/libexpat/archive/R_2_2_4.tar.gz",
          "https://github.com/libexpat/libexpat/archive/R_2_2_4.tar.gz",
        ],
    )

    http_archive(
        name = "fftw",
        urls = [
          "http://www.fftw.org/fftw-3.3.6-pl2.tar.gz",
        ],
        sha256 = "a5de35c5c824a78a058ca54278c706cdf3d4abba1c56b63531c2cb05f5d57da2",
        strip_prefix = "fftw-3.3.6-pl2",
        build_file = str(Label("//bazel:fftw.BUILD")),
    )

    http_archive(
        name = "libjpeg",
        build_file = str(Label("//bazel:libjpeg.BUILD")),
        sha256 = "240fd398da741669bf3c90366f58452ea59041cacc741a489b99f2f6a0bad052",
        strip_prefix = "jpeg-9b",
        urls = [
          "https://mirror.bazel.build/www.ijg.org/files/jpegsrc.v9b.tar.gz",
          "http://www.ijg.org/files/jpegsrc.v9b.tar.gz",
        ],
    )

    http_archive(
        name = "org_libpng_libpng",
        build_file = str(Label("//bazel:libpng.BUILD")),
        sha256 = "7f415186d38ca71c23058386d7cf5135c8beda821ee1beecdc2a7a26c0356615",
        strip_prefix = "libpng-1.2.57",
        urls = [
          "https://mirror.bazel.build/github.com/glennrp/libpng/archive/v1.2.57.tar.gz",
          "https://github.com/glennrp/libpng/archive/v1.2.57.tar.gz",
        ],
    )

    http_archive(
        name = "org_lua_lua",
        build_file = str(Label("//bazel:lua.BUILD")),
        sha256 = "b9e2e4aad6789b3b63a056d442f7b39f0ecfca3ae0f1fc0ae4e9614401b69f4b",
        strip_prefix = "lua-5.2.4",
        urls = [
          "https://mirror.bazel.build/www.lua.org/ftp/lua-5.2.4.tar.gz",
          "https://www.lua.org/ftp/lua-5.2.4.tar.gz",
        ],
    )

    http_archive(
        name = "gif",
        urls = [
          "http://mirror.bazel.build/ufpr.dl.sourceforge.net/project/giflib/giflib-5.1.4.tar.gz",
          "http://pilotfiber.dl.sourceforge.net/project/giflib/giflib-5.1.4.tar.gz",
        ],
        sha256 = "34a7377ba834397db019e8eb122e551a49c98f49df75ec3fcc92b9a794a4f6d1",
        strip_prefix = "giflib-5.1.4",
        build_file = str(Label("//bazel:gif.BUILD")),
    )

    http_archive(
        name = "tiff",
        urls = [
          "http://download.osgeo.org/libtiff/tiff-4.0.9.tar.gz",
        ],
        type = "tar.gz",
        sha256 = "6e7bdeec2c310734e734d19aae3a71ebe37a4d842e0e23dbb1b8921c0026cfcd",
        strip_prefix = "tiff-4.0.9",
        build_file = str(Label("//bazel/tiff:tiff.BUILD")),
    )

    http_archive(
        name = "nasm",
        urls = [
          "http://mirror.bazel.build/www.nasm.us/pub/nasm/releasebuilds/2.12.02/nasm-2.12.02.tar.bz2",
          "http://pkgs.fedoraproject.org/repo/pkgs/nasm/nasm-2.12.02.tar.bz2/d15843c3fb7db39af80571ee27ec6fad/nasm-2.12.02.tar.bz2",
        ],
        sha256 = "00b0891c678c065446ca59bcee64719d0096d54d6886e6e472aeee2e170ae324",
        strip_prefix = "nasm-2.12.02",
        build_file = str(Label("//bazel:nasm.BUILD")),
    )

    http_archive(
        name = "com_github_sparsehash",
        build_file = str(Label("//bazel/sparsehash:BUILD.sparsehash")),
        sha256 = "05e986a5c7327796dad742182b2d10805a8d4f511ad090da0490f146c1ff7a8c",
        strip_prefix = "sparsehash-sparsehash-2.0.3/",
        url = "https://github.com/sparsehash/sparsehash/archive/sparsehash-2.0.3.tar.gz",
    )

    http_archive(
        name = "com_github_rapidjson",
        url = "https://github.com/Tencent/rapidjson/archive/master.zip",
        sha256 = "74ea2e346078a8dad93d52fb92694492a58f51dc9e41d344b07e52127870a4f2",
        strip_prefix = "rapidjson-master",
        build_file = str(Label("//bazel:rapidjson.BUILD")),
    )

    http_archive(
        name = "double_conversion",
        url = "https://github.com/google/double-conversion/archive/4abe326.tar.gz",
        strip_prefix = "double-conversion-4abe3267170fa52f39460460456990dbae803f4d",
        sha256 = "eade523d182260ba25fd5f314cee18297075e4aaf49b59ab80ad5998f371491e",
        build_file = str(Label("//bazel:double-conversion.BUILD")),
    )

    http_archive(
        name = "folly",
        url = "https://github.com/facebook/folly/archive/v2017.09.11.00.tar.gz",
        strip_prefix = "folly-2017.09.11.00",
        sha256 = "926197dbf7930ccfe7ca3a515fc457ba812b99c8da6e486bd7c811d1fd5ff452",
        build_file = str(Label("//bazel/folly:folly.BUILD")),
    )

    http_archive(
        name = "jemalloc",
        url = "https://github.com/jemalloc/jemalloc/archive/4.5.0.tar.gz",
        strip_prefix = "jemalloc-4.5.0",
        sha256 = "e885b65b95426945655ee91a30f563c9679770c92946bcdd0795f6b78c06c221",
        build_file = str(Label("//bazel/jemalloc:jemalloc.BUILD")),
    )

    http_archive(
        name = "libevent",
        url = "https://github.com/libevent/libevent/archive/release-2.0.22-stable.tar.gz",
        strip_prefix = "libevent-release-2.0.22-stable",
        sha256 = "ab89639b0819befb1d8b293d52047c6955f8d1c9150c2b22a0e6247930eb9128",
        build_file = str(Label("//bazel/libevent:libevent.BUILD")),
    )

    http_archive(
        name = "snappy",
        url = "https://github.com/google/snappy/archive/ed3b7b2.tar.gz",
        strip_prefix = "snappy-ed3b7b242bd24de2ca6750c73f64bee5b7505944",
        sha256 = "88a644b224f54edcd57d01074c2d6fd6858888e915c21344b8622c133c35a337",
        build_file = str(Label("//bazel/snappy:snappy.BUILD")),
    )

    http_archive(
        name = "libtorch_archive",
        strip_prefix = "libtorch",
        #sha256 = "f5a33910a2d2932b3224788dfdfab5ba7dd972ec8a3488bf92be63ae30a54591",
        type = "zip",
        urls = ["https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-2.0.0%2Bcpu.zip"],
        build_file = str(Label("//bazel:libtorch.BUILD")),
    )
