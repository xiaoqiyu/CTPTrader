#ifndef SORT_H
#define SORT_H

#include "glog/logging.h"
#include "glog/stl_logging.h"

#include <algorithm>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <vector>
template <class T>
class Search {
 public:
  static T BinarySearch(std::vector<T> &nums, T n);
  static T TernarySearch(std::vector<T> &nums, T n);
  static T ExponentialSearch(std::vector<T> &nums, T n);
  static T BinarySearchPar(std::vector<T> &nums, T n);

  static T BinarySearchImp(std::vector<T> &nums, size_t l, size_t r, T n);
  static T TernarySearchImp(std::vector<T> &nums, size_t l, size_t r, T n);
  static void BinarySearchRefImp(std::vector<T> &nums, size_t l, size_t r, T n,
                                 T &result);

  static int number_of_threads;
};

template <class T>
T Search<T>::BinarySearch(std::vector<T> &nums, T n) {
  return BinarySearchImp(nums, 0, nums.size() - 1, n);
}

template <class T>
T Search<T>::BinarySearchImp(std::vector<T> &nums, size_t l, size_t r, T n) {
  if (l > r || nums.size() == 0) {
    return -1;
  }

  size_t mid = l + (r - l) / 2;
  if (nums[mid] == n) {
    return mid;
  }

  if (nums[mid] > n) {
    return BinarySearchImp(nums, l, mid - 1, n);
  } else {
    return BinarySearchImp(nums, mid + 1, r, n);
  }
};

template <class T>

void Search<T>::BinarySearchRefImp(std::vector<T> &nums, size_t l, size_t r,
                                   T n, T &result) {
  if (l > r || nums.size() == 0) {
    result = -1;

    return;
  }

  size_t mid = l + (r - l) / 2;

  if (nums[mid] == n) {
    result = mid;

    return;
  }

  if (nums[mid] > n) {
    BinarySearchRefImp(nums, l, mid - 1, n, result);
  } else {
    BinarySearchRefImp(nums, mid + 1, r, n, result);
  }
};

template <class T>

T Search<T>::BinarySearchPar(std::vector<T> &nums, T n) {
  if (nums.size() == 0) {
    return -1;
  }

  size_t step = std::ceil((float)nums.size() / (float)number_of_threads);

  std::vector<T> results(number_of_threads, -1);
  std::vector<std::thread> threads;

  for (unsigned long i = 0; i < number_of_threads; i++) {
    size_t low = i * step;
    size_t high = std::min((i + 1) * step - 1, (size_t)nums.size() - 1);
    high = std::max((size_t)0, high);
    // std::cout << "low: " << low << ", high: " << high << std::endl;

    CHECK(high < nums.size());
    if (low <= high) {
      threads.push_back(std::thread([&nums, low, high, n, i, &results]() {
        Search<T>::BinarySearchRefImp(nums, low, high, n, results[i]);
      }));
    }
  }
  // std::cout << "Joining!" << std::endl;
  for (auto &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }
  // LOG(INFO) << "results: " << results;
  for (auto &r : results) {
    if (r != -1) {
      return r;
    }
  }

  return -1;
}

template <class T>
T Search<T>::TernarySearch(std::vector<T> &nums, T n) {
  return TernarySearchImp(nums, 0, nums.size() - 1, n);
}

template <class T>
T Search<T>::TernarySearchImp(std::vector<T> &nums, size_t l, size_t r, T n) {
  if (l > r || nums.size() == 0) {
    return -1;
  }

  // Find the mid1 and mid2
  size_t mid1 = l + (r - l) / 3;
  size_t mid2 = r - (r - l) / 3;

  // Check if key is present at any mid
  if (nums[mid1] == n) {
    return mid1;
  }
  if (nums[mid2] == n) {
    return mid2;
  }

  if (n < nums[mid1]) {
    return BinarySearchImp(nums, l, mid1 - 1, n);
  } else if (n > nums[mid2]) {
    return BinarySearchImp(nums, mid2 + 1, r, n);
  } else {
    return BinarySearchImp(nums, mid1 + 1, mid2 - 1, n);
  }
};

template <class T>
T Search<T>::ExponentialSearch(std::vector<T> &nums, T n) {
  if (nums.size() == 0) {
    return -1;
  }

  size_t bound = 1;
  while (bound < nums.size() && nums[bound] < n) {
    bound *= 2;
  }
  // std::cout << "bound: " << bound << std::endl;
  return Search<T>::BinarySearchImp(
      nums, bound / 2, std::min((size_t)bound + 1, nums.size() - 1), n);
}

#endif