load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "com_google_googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

git_repository(
    name = "glog",
    remote = "https://github.com/google/glog.git",
    tag = "v0.4.0",
)

git_repository(
    name = "com_google_absl",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20200225.2",
)

git_repository(
    name = "com_google_benchmark",
    remote = "https://github.com/google/benchmark.git",
    tag = "v1.5.1",
)

git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = "v2.2.2",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "zlib",
    build_file = "zlib.BUILD",
    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
    strip_prefix = "zlib-1.2.11",
    urls = ["https://zlib.net/zlib-1.2.11.tar.gz"],
)

