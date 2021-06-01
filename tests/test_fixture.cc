#include <iostream>
#include <vector>

#include "gtest/gtest.h"

template <typename E>  // E is the element type.
class Queue {
 private:
  std::vector<E> _v;

 public:
  Queue() {}
  void Enqueue(const E& element) { _v.push_back(element); }
  // Throws the queue is empty.
  E Dequeue() {
    if (IsEmpty()) {
      throw;
    }
    auto tmp = _v[0];

    _v.erase(_v.begin());

    return tmp;
  }
  size_t size() const { return _v.size(); }
  bool IsEmpty() { return _v.empty(); }
};

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
    q1_.Enqueue(1);
    q2_.Enqueue(2);
    q2_.Enqueue(3);
  }

  void TearDown() override {std::cout << "Test ended!" << std::endl;}

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};

TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
  EXPECT_EQ(q0_.IsEmpty(), true);
}

TEST_F(QueueTest, DequeueWorks) {
  EXPECT_EQ(q1_.size(), 1);
  EXPECT_EQ(q1_.Dequeue(), 1);
  EXPECT_EQ(q1_.IsEmpty(), true);
}
