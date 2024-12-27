#include "gtest.h"
#include "Arithmetik.h"

// ����� �� ������������ ����������
TEST(ArithmetikTest, CalculateTest1) {
    Arithmetik arith("(2 + 3) * 4");
    
    double result = arith.calculate();
    EXPECT_EQ(result, (2 + 3) * 4); 
}
TEST(ArithmetikTest, CalculateTest2) {
    Arithmetik arith("2 + 3 - 4");

    double result = arith.calculate();
    EXPECT_EQ(result, 2 + 3 - 4);
}
TEST(ArithmetikTest, CalculateTest3) {
    Arithmetik arith("2 + 3 * 4");

    double result = arith.calculate();
    EXPECT_EQ(result, 2 + 3 * 4);
}
TEST(ArithmetikTest, CalculateTest4) {
    Arithmetik arith("2 * 4* 6 * 8 * 9 * 1");

    double result = arith.calculate();
    EXPECT_EQ(result, 2 * 4 * 6 * 8 * 9 * 1);
}
TEST(ArithmetikTest, CalculateTest5) {
    Arithmetik arith("2 - 3 * 4");

    double result = arith.calculate();
    EXPECT_EQ(result, 2 - 3 * 4);
}
TEST(ArithmetikTest, CalculateTest6) {
    Arithmetik arith("2 * 3  *(0-4)");

    double result = arith.calculate();
    EXPECT_EQ(result, 2 * 3 *(0-4));
}

// ���� �� ������� �� ����
TEST(ArithmetikTest, DivisionByZero) {
    Arithmetik arith("a / b");  // ������ �������
    arith.setVar(0, 5);
    arith.setVar(1, 0);  // ��������� b ������ ����

    EXPECT_ANY_THROW(arith.calculate());  // ������� ���������� ��� ������� �� ����
}