

#include <iostream>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
// In this example we don't inherit from the original. Instead we replace it
// with mock.
class Turtle {
 public:
  MOCK_METHOD0(PenUp, void());
  MOCK_METHOD0(PenDown, void());
  MOCK_METHOD1(Forward, void(int distance));
  MOCK_METHOD1(Turn, void(int degrees));
  MOCK_METHOD2(GoTo, void(int x, int y));
  MOCK_CONST_METHOD0(GetX, int());
  MOCK_CONST_METHOD0(GetY, int());
  MOCK_CONST_METHOD3(SomeRandomFunction, int(int x, int y, int z));
};

class Painter {
  Turtle* turtle;

 public:
  Painter(Turtle* turtle) : turtle(turtle) {}

  bool DrawCircle(int x, int y, int r) {
    auto res = turtle->SomeRandomFunction(3, 2, 1);
    std::cout << "res: " << res << std::endl;
    res = turtle->SomeRandomFunction(2, 3, 1);
    std::cout << "res: " << res << std::endl;

    int next_y;
    turtle->GoTo(x, y + r);
    turtle->PenDown();
    turtle->PenUp();
    next_y = turtle->GetY();
    std::cout << "next_y: " << next_y << std::endl;

    turtle->GoTo(x, y - r);
    turtle->PenDown();
    turtle->PenUp();
    next_y = turtle->GetY();
    std::cout << "next_y: " << next_y << std::endl;

    next_y = turtle->GetY();
    std::cout << "next_y: " << next_y << std::endl;

    next_y = turtle->GetY();
    std::cout << "next_y: " << next_y << std::endl;

    next_y = turtle->GetY();
    std::cout << "next_y: " << next_y << std::endl;

    return true;
  }
};

// 1. Import the gMock names from the testing namespace such that you can use
// them unqualified (You only have to do it once per file). Remember that
// namespaces are a good idea.
// 2. Create some mock objects.
// 3. Specify your expectations on them (How many times will a method be called?
// With what arguments? What should it do? etc.).
// 4. Exercise some code that uses the mocks; optionally, check the result using
// googletest assertions. If a mock method is called more than expected or with
// wrong arguments, you'll get an error immediately.
// 5. When a mock is destructed, gMock will automatically check whether all
// expectations on it have been satisfied.

using ::testing::_;
using ::testing::AllArgs;  // #1
using ::testing::Args;     // #1
using ::testing::AtLeast;  // #1
using ::testing::Exactly;  // #1
using ::testing::InSequence;
using ::testing::Lt;  // #1
using ::testing::Ne;  // #1

using ::testing::NiceMock;
using ::testing::Return;  // #1

TEST(PainterTest, CanDrawCircle) {
  NiceMock<Turtle> turtle;
  EXPECT_CALL(turtle, PenDown()).Times(AtLeast(2));

  EXPECT_CALL(turtle, GoTo(0, 10)).Times(1);

  EXPECT_CALL(turtle, GoTo(0, -10)).Times(1);

  ON_CALL(turtle, SomeRandomFunction(_, _, _)).WillByDefault(Return(10));

  Painter painter(&turtle);

  EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}

TEST(PainterTest, CanDrawCircle2) {
  NiceMock<Turtle> turtle;        // #2
  EXPECT_CALL(turtle, PenDown())  // #3
      .Times(AtLeast(2));

  EXPECT_CALL(turtle, GoTo(0, 10))  // #3
      .Times(1);

  EXPECT_CALL(turtle, GoTo(0, -10))  // #3
      .Times(1);

  // For any argument values, return 20.
  ON_CALL(turtle, SomeRandomFunction(_, _, _)).WillByDefault(Return(20));

  // When arg0 < arg1, then return 10
  ON_CALL(turtle, SomeRandomFunction(_, _, _))
      .With(Args<0, 1>(Lt()))
      .WillByDefault(Return(10));

  Painter painter(&turtle);  // #4

  EXPECT_TRUE(painter.DrawCircle(0, 0, 10));  // #5
}
