/**
 * Demo for using Benchmarking using Google's benchmark platform:
 * https://github.com/google/benchmark
 */
#include "benchmark/benchmark.h"
#include <stdlib.h> /* qsort */

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

#include "src/lib/search/search.h"

const long g_size = 1000000000000;
template <class T>
int Search<T>::number_of_threads = 10;

class Data {
 public:
  Data(long size) { ConstructSortedVector(size); }

  void ConstructRandomVector(long size) {
    std::srand(10);
    v.resize(size);
    std::generate(v.begin(), v.end(), std::rand);
    std::sort(v.begin(), v.end());
  }

  void ConstructSortedVector(long size) {
    v.resize(size);
    std::iota(v.begin(), v.end(), 0);
  }

  std::vector<unsigned long> v;
};

Data init(long size = g_size) {
  Data d(size);
  return d;
}

static void BM_BinarySearch(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();
    Search<unsigned long>::BinarySearch(d.v, d.v[100]);
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}

static void BM_ExponentialSearch(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();
    Search<unsigned long>::ExponentialSearch(d.v, d.v[100]);
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}

static void BM_TernarySearch(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();
    Search<unsigned long>::TernarySearch(d.v, d.v[10000]);
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}

static void BM_BinarySearchPar(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    Search<unsigned long>::number_of_threads = state.range(1);

    state.ResumeTiming();
    Search<unsigned long>::BinarySearchPar(d.v, d.v[100]);
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
  state.SetComplexityN(state.range(0));
}


// Compare binary search, ternary search, and exponential search
BENCHMARK(BM_BinarySearch)
    ->RangeMultiplier(2)
    ->Range(1 << 15, 1 << 18)
    ->Complexity(benchmark::oLogN);

// BENCHMARK(BM_TernarySearch)
//     ->RangeMultiplier(2)
//     ->Range(1 << 15, 1 << 18)
//     ->Complexity(benchmark::oLogN);

BENCHMARK(BM_ExponentialSearch)
    ->RangeMultiplier(2)
    ->Range(1 << 15, 1 << 18)
    ->Complexity(benchmark::oLogN);

BENCHMARK(BM_BinarySearchPar)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 15, 1 << 18}, {2, 2}})
    ->Complexity(benchmark::oLogN);

//-----------------------------------------------------
// Comparison of BinarySearch and BinarySearchPar changing number of threads
// Run with:
// bazel run --cxxopt='-std=c++17' -c opt src/benchmark/main_benchmark_search -- --benchmark_format=csv | tee bs_vs_bs_par_10k.csv 
// BENCHMARK(BM_BinarySearch)->Arg(g_size);
// BENCHMARK(BM_BinarySearchPar)
//     ->UseRealTime()
//     ->Args({g_size, 2})
//     ->Args({g_size, 3})
//     ->Args({g_size, 4})
//     ->Args({g_size, 5})
//     ->Args({g_size, 6})
//     ->Args({g_size, 7})
//     ->Args({g_size, 8})
//     ->Args({g_size, 9})
//     ->Args({g_size, 10});
//-----------------------------------------------------

BENCHMARK_MAIN();