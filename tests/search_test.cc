#include "src/lib/search/search.h"

#include <functional>
#include <numeric>
#include <thread>
#include <vector>

#include "gtest/gtest.h"

template <class T>
int Search<T>::number_of_threads = 10;

template <class F>
void TestSearch(F search_func) {
  std::vector<long> in;
  long n;
  size_t expected_index;
  // Check empty
  in = {};
  n = 10;
  expected_index = -1;
  auto result = search_func(in, n);
  EXPECT_EQ(expected_index, result);

  // Search array of existing single element
  in = {3};
  n = 3;
  expected_index = 0;
  EXPECT_EQ(expected_index, search_func(in, n));

  // Search array of non existing single element
  in = {3};
  n = 4;
  expected_index = -1;
  EXPECT_EQ(expected_index, search_func(in, n));

  // Check small vector
  in = {1, 3, 5, 77, 90};
  n = 77;
  expected_index = 3;
  EXPECT_EQ(expected_index, search_func(in, n));

  // Check small vector
  in = {1, 3, 5, 77, 90};
  n = 90;
  expected_index = 4;
  EXPECT_EQ(expected_index, search_func(in, n));

  // Random large vector, testing with multiple seeds
  for (size_t i = 0; i < 9; i++) {
    std::srand(i);  // use a constant seed to make the test repeatable
    in.resize(9);
    std::generate(in.begin(), in.end(), std::rand);
    std::sort(in.begin(), in.end());
    n = in[8];
    expected_index = 8;
    EXPECT_EQ(expected_index, search_func(in, n));
  }

  // Random large vector, testing with multiple seeds
  for (size_t i = 0; i < 1000; i++) {
    std::srand(i);  // use a constant seed to make the test repeatable
    in.resize(1000);
    std::generate(in.begin(), in.end(), std::rand);
    std::sort(in.begin(), in.end());
    n = in[i];
    expected_index = i;
    EXPECT_EQ(expected_index, search_func(in, n));
  }

  // very large vector
  in.resize(10000000);
  std::iota(in.begin(), in.end(), 0);
  n = in[0];
  expected_index = 0;
  EXPECT_EQ(expected_index, search_func(in, n));

  n = in[in.size() - 1];
  expected_index = in.size() - 1;
  EXPECT_EQ(expected_index, search_func(in, n));
}

TEST(SearchTest, ExponentialSearch) {
  TestSearch(Search<long>::ExponentialSearch);
}

TEST(SearchTest, BinarySearch) {
  TestSearch(Search<long>::BinarySearch);
}
TEST(SearchTest, TernarySearch) {
  TestSearch(Search<long>::TernarySearch);
}
TEST(SearchTest, BinarySearchPar) {
  TestSearch(Search<long>::BinarySearchPar);
}
