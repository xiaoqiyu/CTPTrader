/**
 * Demo for using Benchmarking using Google's benchmark platform:
 * https://github.com/google/benchmark
 */
#include <stdlib.h> /* qsort */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "benchmark/benchmark.h"
#include "src/lib/sort/sort.h"

template <class T>
void Swap(T& i, T& j) {
  T temp = i;
  i = j;
  j = temp;
}
class Data {
 public:
  Data(int size) {
    // Sort(size);
    // ReverseSort(size);

    ConstructRandomVector(size);
  }

  /**
   * Creates a reversely sorted vector
   */
  void ReverseSort(int size) {
    v.resize(size);

    for (int i = 0; i < size; ++i) {
      v[i] = (size - i);
    }
  }

  /**
   * Creates a  sorted vector
   */
  void Sort(int size) {
    v.resize(size);

    for (int i = 0; i < size; ++i) {
      v[i] = i;
    }
  }

  /**
   * Creates a random vector
   */
  void ConstructRandomVector(int size) {
    std::srand(100);
    v.resize(size);
    std::generate(v.begin(), v.end(), std::rand);
  }

  std::vector<int> v;
};

const int g_size = 10000000;

int Sort::QUICKSORT_THREASHOLD;
int Sort::MERGESORT_THREASHOLD;
int Sort::INTROSORT_THREASHOLD;

Data init(int size = g_size) {
  Data d(size);

  Sort::QUICKSORT_THREASHOLD = g_size / std::thread::hardware_concurrency();
  Sort::MERGESORT_THREASHOLD = g_size / std::thread::hardware_concurrency();
  Sort::INTROSORT_THREASHOLD = g_size / std::thread::hardware_concurrency();
  return d;
}

static void BM_SelectionSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();
    Sort::SelectionSort(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_HeapSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();
    Sort::HeapSort(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

static void BM_InsertionSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();
    Sort::InsertionSort(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

static void BM_BubbleSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::BubbleSort(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_BubbleSortImproved(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::BubbleSortImproved(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

static void BM_MergeSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::MergeSort(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

static void BM_MergeSortPar(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::MergeSortPar(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

static void BM_QuickSort_iterative(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::QuickSort_iterative(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_QuickSort_oneCall(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::QuickSort_oneCall(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_QuickSort_twoCalls(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::QuickSort_twoCalls(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_QuickSortPar(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::QuickSortPar(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_IntroSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::Introsort(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

static void BM_IntroSortPar(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::IntrosortPar(d.v);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}
static void BM_StdSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    std::sort(d.v.begin(), d.v.end());
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

static void BM_IsSorted(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    Sort::IsSorted(d.v, 0, d.v.size() - 1);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
  state.SetComplexityN(state.range(0));
}

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
static void BM_StdQSort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto d = init(state.range(0));
    state.ResumeTiming();

    std::qsort(&d.v[0], d.v.size(), sizeof(int), compare);
  }
  state.SetItemsProcessed(state.iterations() * g_size);
}

// Below are various benchmark registrations for measuring sort algorithms:

BENCHMARK(BM_QuickSort_twoCalls)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 25)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_HeapSort)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 25)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_MergeSort)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 25)
    ->Complexity(benchmark::oNLogN);

// Compare with std::sort with quicksort and introsort:
// BENCHMARK(BM_StdSort)
//     ->RangeMultiplier(2)
//     ->Range(1 << 10, 1 << 25)
//     ->Complexity(benchmark::oNLogN);

// BENCHMARK(BM_IntroSort)
//     ->RangeMultiplier(2)
//     ->Range(1 << 10, 1 << 25)
//     ->Complexity(benchmark::oNLogN);

// BENCHMARK(BM_IntroSortPar)
//     ->RangeMultiplier(2)
//     ->Range(1 << 10, 1 << 25)
//     ->Complexity(benchmark::oNLogN);

// BENCHMARK(BM_QuickSort_twoCalls)
//     ->RangeMultiplier(2)
//     ->Range(1 << 5, 1 << 25)
//     ->Complexity(benchmark::oNLogN);
// BENCHMARK(BM_QuickSort_iterative)
//     ->RangeMultiplier(2)
//     ->Range(1 << 5, 1 << 25)
//     ->Complexity(benchmark::oNLogN);

// BENCHMARK(BM_QuickSort_oneCall)
//     ->RangeMultiplier(2)
//     ->Range(1 << 5, 1 << 25)
//     ->Complexity(benchmark::oNLogN);

// BENCHMARK(BM_QuickSortPar)
//     ->RangeMultiplier(2)
//     ->Range(1 << 5, 1 << 25)
//     ->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();