#include "src/lib/cpplib.h"

#include <map>
#include <vector>

#include "gtest/gtest.h"

// TEST(CPPLibTest, ReturnHelloWorld) {
//   CPPLib cpplib;
//   std::string actual = cpplib.PrintHelloWorld();
//   std::string expected = "**** Hello World ****";
//   EXPECT_EQ(expected, actual);
// }

// TEST(CPPLibTest, CalculateFibonacci) {
//   CPPLib cpplib;

//   EXPECT_EQ(cpplib.fib(1), 1) << "Error: The factorial calculation was wrong!";
//   EXPECT_EQ(cpplib.fib(5), 5) << "Error: The factorial calculation was wrong!";
//   EXPECT_EQ(cpplib.fib(6), 8) << "Error: The factorial calculation was wrong!";
// }

// TEST(CPPLibTest, CalculateFibonacci) {
//   CPPLib cpplib;

//   std::vector<int> inputs = {1, 2, 3, 4, 5, 6};
//   std::vector<int> actual;

//   for (auto &in : inputs) {
//     actual.push_back(cpplib.fib(in));
//   }

//   std::vector<int> expected = {1, 1, 2, 3, 5, 8};
//   EXPECT_EQ(expected, actual) << "Error: The factorial calculation was
//   wrong!";
// }

TEST(CPPLibTest, FindMaxHandlesSizeOne) {
  CPPLib cpplib;
  std::vector<int> inputs = {2};
  EXPECT_EQ(cpplib.FindMax(inputs), 3);
}

TEST(CPPLibTest, FindMaxHandlesConsecutiveNumbers) {
  CPPLib cpplib;
  std::vector<int> inputs = {1, 2, 3, 4};
  EXPECT_EQ(cpplib.FindMax(inputs), 4);
}

TEST(CPPLibTest, FindMaxHandlesEmptyVector) {
  CPPLib cpplib;
  std::vector<int> inputs = {};
  EXPECT_EQ(cpplib.FindMax(inputs), -1);
}