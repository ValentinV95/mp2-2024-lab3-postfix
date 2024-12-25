// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "Arithmetik.h"

class ArithmetikTest : public ::testing::Test {
protected:
    Arithmetik arithmetik;

    void SetUp() override {

    }
};

TEST_F(ArithmetikTest, TestAddition) {
    arithmetik.setVar(0, 5);
    arithmetik.setVar(1, 3);
    arithmetik.calculate();
    EXPECT_DOUBLE_EQ(arithmetik.calculate(), 8);
}

TEST_F(ArithmetikTest, TestSubtraction) {
    arithmetik.setVar(0, 10);
    arithmetik.setVar(1, 4);
    EXPECT_DOUBLE_EQ(arithmetik.calculate(), 6);
}

TEST_F(ArithmetikTest, TestMultiplication) {
    arithmetik.setVar(0, 7);
    arithmetik.setVar(1, 6);
    EXPECT_DOUBLE_EQ(arithmetik.calculate(), 42);
}

TEST_F(ArithmetikTest, TestDivision) {
    arithmetik.setVar(0, 8);
    arithmetik.setVar(1, 2);
    EXPECT_DOUBLE_EQ(arithmetik.calculate(), 4);
}

TEST_F(ArithmetikTest, TestPower) {
    arithmetik.setVar(0, 2);
    arithmetik.setVar(1, 3);
    EXPECT_DOUBLE_EQ(arithmetik.calculate(), 8);
}
