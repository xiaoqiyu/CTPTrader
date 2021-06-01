
#include "sort.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <random>
#include <vector>

template <class T>
void Swap(T &i, T &j) {
  T temp = i;
  i = j;
  j = temp;
}

bool Sort::IsSorted(std::vector<int> &nums, int low, int high) {
  for (int i = low + 1; i <= high; ++i) {
    if (nums[i - 1] > nums[i]) {
      return false;
    }
  }
  return true;
}

int Sort::FindMinIndex(const std::vector<int> &input, int start_index) {
  int min_index = start_index;
  int cur_min = input[start_index];
  for (size_t i = start_index; i < input.size(); i++) {
    if (input[i] < cur_min) {
      cur_min = input[i];
      min_index = i;
    }
  }
  return min_index;
}

void Sort::SelectionSort(std::vector<int> &input) {
  for (int i = 0; i < int(input.size() - 1); i++) {
    int min_index = FindMinIndex(input, i);
    Swap(input[i], input[min_index]);
  }
}

void Sort::BubbleSort(std::vector<int> &input) {
  bool go;
  do {
    go = false;
    for (int i = 0; i < int(input.size() - 1); i++) {
      if (input[i] > input[i + 1]) {
        Swap(input[i], input[i + 1]);
        go = true;
      }
    }
  } while (go);
}

void Sort::BubbleSortImproved(std::vector<int> &input) {
  int n = input.size();

  for (int i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < n - 1 - i; j++) {
      if (input[j] > input[j + 1]) {
        Swap(input[j], input[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
}
// To heapify a subtree rooted with node i which is
// an index in arr

void Sort::Heapify(std::vector<int> &arr, int n, int i) {
  int largest = i;    // Initialize largest as root
  int l = 2 * i + 1;  // left = 2*i + 1
  int r = 2 * i + 2;  // right = 2*i + 2

  // If left child is larger than root
  if (l < n && arr[l] > arr[largest]) largest = l;

  // If right child is larger than largest so far
  if (r < n && arr[r] > arr[largest]) largest = r;

  // If largest is not root
  if (largest != i) {
    Swap(arr[i], arr[largest]);

    // Recursively heapify the affected sub-tree
    Heapify(arr, n, largest);
  }
}

// main function to do heap sort
void Sort::HeapSort(std::vector<int> &arr) {
  int n = arr.size();
  // Build heap (rearrange array)
  for (int i = n / 2 - 1; i >= 0; i--) {
    Heapify(arr, n, i);
  }

  // One by one extract an element from heap
  for (int i = n - 1; i > 0; i--) {
    // Move current root to end
    Swap(arr[0], arr[i]);

    // call max heapify on the reduced heap
    Heapify(arr, i, 0);
  }
}

int Sort::GetMinValueAndIncrementItsIndex(std::vector<int> &input,
                                          int &left_index, int &right_index,
                                          const int left_max_index,
                                          const int right_max_index) {
  if (left_index > left_max_index) {
    return input[right_index++];
  }
  if (right_index > right_max_index) {
    return input[left_index++];
  }
  if (input[left_index] <= input[right_index]) {
    return input[left_index++];
  } else {
    return input[right_index++];
  }
}

void Sort::Merge(std::vector<int> &input, int l, int m, int r) {
  // We only copy from l to r (including r)
  std::vector<int> input_copy(input.begin() + l, input.begin() + r + 1);

  int left_index = 0;
  int right_index = m + 1 - l;  // adjust m+1 by subtracting l from it
  int left_max_index = m - l;   // Last index of left half
  int right_max_index = r - l;  // Last index of right half
  for (int i = l; i <= r; i++) {
    input[i] = GetMinValueAndIncrementItsIndex(
        input_copy, left_index, right_index, left_max_index, right_max_index);
  }
}

// l: first index, r: last index (included)
void Sort::MergeSortHelp(std::vector<int> &input, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;

    // Sort first and second halves
    MergeSortHelp(input, l, m);
    MergeSortHelp(input, m + 1, r);

    Merge(input, l, m, r);
  }
}

// Calls MergeSortHelp with l=0, r=input.size() -1
void Sort::MergeSort(std::vector<int> &input) {
  MergeSortHelp(input, 0, int(input.size() - 1));
}

void Sort::MergeSortParHelp(std::vector<int> &input, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;

    // Sort first and second halves
    // We do multithreading if the size is big enough
    if (r - l > MERGESORT_THREASHOLD) {
      auto t1 = std::thread(MergeSortParHelp, std::ref(input), l, m);
      auto t2 = std::thread(MergeSortParHelp, std::ref(input), m + 1, r);
      t1.join();
      t2.join();
    } else {
      MergeSortHelp(input, l, m);
      MergeSortHelp(input, m + 1, r);
    }
    Merge(input, l, m, r);
  }
}

// Calls MergeSortHelp with l=0, r=input.size() -1
void Sort::MergeSortPar(std::vector<int> &input) {
  MergeSortParHelp(input, 0, int(input.size() - 1));
}

//-----------------------------------------------------
void Sort::InsertionSortImp(std::vector<int> &arr, int left, int right) {
  for (int i = left + 1; i <= right; i++) {
    int key = arr[i];
    int j = i - 1;

    /* Move elements of arr[0..i-1], that are
       greater than key, to one position ahead
       of their current position */
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }

  return;
}

// Generates Random Pivot, swaps pivot with
// end element and calls the partition function
// In Hoare partition the low element is selected
// as first pivot
int Partition_r(std::vector<int> &input, int low, int high) {
  // Generate a random number in between
  auto GenRandomValue = std::bind(std::uniform_int_distribution<>(low, high),
                                  std::default_random_engine());

  int random = GenRandomValue();

  // Swap A[random] with A[high]
  Swap(input[random], input[low]);

  return Sort::Partition(input, low, high);
}

int Sort::Partition(std::vector<int> &input, int low, int high) {
  int median_index = MedianOfThree(input, low, (low + high) / 2, high - 1);
  int pivot = input[median_index];

  // Swap(input[low], input[median_index]);
  // int pivot = input[low];
  // int pivot = input[low + (high - low) / 2];

  // auto GenRandomValue = std::bind(std::uniform_int_distribution<>(low, high),
  //                                 std::default_random_engine());

  // int pivot = input[GenRandomValue()];

  int i = low;
  int j = high;
  while (true) {
    while (input[i] < pivot) {
      i++;
    }

    while (input[j] > pivot) {
      j--;
    }

    if (i >= j) {
      return j;
    }
    Swap(input[i], input[j]);
    i++;
    j--;
  }
}
/* The main function that implements quickSortImp
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void Sort::QuickSortImp_twoCalls(std::vector<int> &input, int low, int high) {
  if (low < high) {
    /* pi is partitioning index, arr[p] is now
     at right place */
    int pi = Partition(input, low, high);

    // Separately sort elements before
    // partition and after partition
    QuickSortImp_twoCalls(input, low, pi);
    QuickSortImp_twoCalls(input, pi + 1, high);
  }
}

void Sort::QuickSortImp_oneCall(std::vector<int> &input, int low, int high) {
  while (low < high) {
    int pi = Partition(input, low, high);

    // If left part is smaller, then recur for left
    if (pi - low > high - pi) {
      QuickSortImp_oneCall(input, low, pi);

      // Adjust index for the second call
      low = pi + 1;
    }
    // Else recur for right part
    else {
      QuickSortImp_oneCall(input, pi + 1, high);

      // Adjust index for the second call
      high = pi;
    }
  }
}

void Sort::QuickSortImp_iterative(std::vector<int> &input, int low, int high) {
  if (high <= low) {
    return;
  }
  // Create an auxiliary stack
  std::vector<int> stack(high - low + 1);

  // initialize top of stack
  int top = -1;

  // push initial values of l and h to stack
  stack[++top] = low;
  stack[++top] = high;

  // Keep popping from stack while is not empty
  while (top >= 0) {
    // Pop h and l
    high = stack[top--];
    low = stack[top--];

    // Set pivot element at its correct position
    // in sorted array
    int p = Partition(input, low, high);

    // If there are elements on left side of pivot,
    // then push left side to stack
    if (p > low) {
      stack[++top] = low;
      stack[++top] = p;
    }

    // If there are elements on right side of pivot,
    // then push right side to stack
    if (p + 1 < high) {
      stack[++top] = p + 1;
      stack[++top] = high;
    }
  }
}

void Sort::QuickSortParImp(std::vector<int> &input, int low, int high) {
  if (low < high) {
    /* pi is partitioning index, arr[p] is now
    at right place */
    int pi = Partition(input, low, high);
    // If the size was high enough, we use multi threading
    if (high - low > QUICKSORT_THREASHOLD) {
      // Separately sort elements before
      // partition and after partition
      auto t1 = std::thread(QuickSortParImp, std::ref(input), low, pi);
      auto t2 = std::thread(QuickSortParImp, std::ref(input), pi + 1, high);
      t1.join();
      t2.join();
    } else {
      QuickSortParImp(input, low, pi);
      QuickSortParImp(input, pi + 1, high);
    }
  }
}

//-----------------------------------------------------
// A function that find the middle of the
// values pointed by the pointers a, b, c
// and return that pointer
int Sort::MedianOfThree(std::vector<int> &v, int a_i, int b_i, int c_i) {
  int a = v[a_i];
  int b = v[b_i];
  int c = v[c_i];

  // Checking for b
  if ((a < b && b < c) || (c < b && b < a)) {
    return b_i;
  }

  // Checking for a
  else if ((b < a && a < c) || (c < a && a < b)) {
    return a_i;
  }

  else {
    return c_i;
  }
}

void Sort::IntrosortUtil(std::vector<int> &arr, int begin, int end,
                         int depthLimit, bool par) {
  // Count the number of elements
  int size = end - begin;
  if (size > 0) {
    // If partition size is low then do insertion sort
    if (size < 16) {
      InsertionSortImp(arr, begin, end);
      return;
    }

    // If the depth is zero use heapsort
    if (depthLimit == 0) {
      std::make_heap(arr.begin() + begin, arr.begin() + end + 1);
      std::sort_heap(arr.begin() + begin, arr.begin() + end + 1);
      return;
    }

    // Else use a median-of-three concept to
    // find a good pivot
    int partitionPoint = Sort::Partition(arr, begin, end);

    // Create an std::function for each half to be called either serially or
    // concurrently
    auto first_half = [&]() {
      if (!IsSorted(arr, begin, partitionPoint)) {
        IntrosortUtil(arr, begin, partitionPoint, depthLimit - 1, par);
      }
    };
    auto second_half = [&]() {
      if (!IsSorted(arr, partitionPoint + 1, end)) {
        IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1, par);
      }
    };

    if (par && (size > INTROSORT_THREASHOLD)) {
      auto t1 = std::thread(first_half);
      auto t2 = std::thread(second_half);
      t1.join();
      t2.join();
    } else {
      first_half();
      second_half();
    }
  }
}

/* Implementation of introsort*/
void Sort::IntrosortImp(std::vector<int> &arr, int begin, int end, bool par) {
  int depthLimit = 2 * log(arr.size());

  // Perform a recursive Introsort
  IntrosortUtil(arr, begin, end, depthLimit, par);
  return;
}
