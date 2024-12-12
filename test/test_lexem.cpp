#include "arithmetic.h"
#include "Vector.h"
#include <gtest.h>

TEST(Operation, can_create_operation0)
{
	ASSERT_NO_THROW(operation a('-', 0));
}

TEST(Operation, can_create_operation1)
{
	ASSERT_NO_THROW(operation a('+', 0));
}

TEST(Operation, can_create_operation2)
{
	ASSERT_NO_THROW(operation a('*', 0));
}

TEST(Operation, can_create_operation3)
{
	ASSERT_NO_THROW(operation a('/', 0));
}

TEST(Operation, can_create_operation4)
{
	ASSERT_NO_THROW(operation a('(', 0));
}

TEST(Operation, can_create_operation5)
{
	ASSERT_NO_THROW(operation a(')', 0));
}

TEST(Operation, can_create_operation6)
{
	ASSERT_NO_THROW(operation a('s', 0));
}

TEST(Operation, can_create_operation7)
{
	ASSERT_NO_THROW(operation a('c', 0));
}

TEST(Operation, can_create_operation8)
{
	ASSERT_NO_THROW(operation a('q', 0));
}

TEST(Operation, can_create_operation9)
{
	ASSERT_NO_THROW(operation a('l', 0));
}

TEST(Operation, can_create_operation10)
{
	ASSERT_NO_THROW(operation a('d', 0));
}

TEST(Operation, can_create_operation11)
{
	ASSERT_NO_THROW(operation a('~', 0));
}

TEST(Operation, check_create_operation0)
{
	operation a('-', 0);
	EXPECT_EQ('-', a.getOperation());
}

TEST(Operation, check_priority_operation0)
{
	operation a('-', 0);
	EXPECT_EQ(2, a.getPriority());
}

TEST(Operation, check_priority_operation1)
{
	operation a('+', 0);
	EXPECT_EQ(2, a.getPriority());
}

TEST(Operation, check_priority_operation2)
{
	operation a('*', 0);
	EXPECT_EQ(1, a.getPriority());
}

TEST(Operation, check_priority_operation3)
{
	operation a('/', 0);
	EXPECT_EQ(1, a.getPriority());
}

TEST(Operation, check_priority_operation4)
{
	operation a('(', 0);
	EXPECT_EQ(3, a.getPriority());
}

TEST(Operation, check_priority_operation5)
{
	operation a(')', 0);
	EXPECT_EQ(3, a.getPriority());
}

TEST(Operation, check_priority_operation6)
{
	operation a('s', 0);
	EXPECT_EQ(-1, a.getPriority());
}

TEST(Operation, check_priority_operation7)
{
	operation a('c', 0);
	EXPECT_EQ(-1, a.getPriority());
}

TEST(Operation, check_priority_operation8)
{
	operation a('q', 0);
	EXPECT_EQ(-1, a.getPriority());
}

TEST(Operation, check_priority_operation9)
{
	operation a('l', 0);
	EXPECT_EQ(-1, a.getPriority());
}

TEST(Operation, check_priority_operation10)
{
	operation a('d', 0);
	EXPECT_EQ(-1, a.getPriority());
}

TEST(Operation, check_priority_operation11)
{
	operation a('~', 0);
	EXPECT_EQ(0, a.getPriority());
}

TEST(Operation, check_correct_what)
{
	operation a('d', 0);
	EXPECT_EQ(1, a.what());
}

TEST(Operand, can_create_operand)
{
	ASSERT_NO_THROW(operand a(13e-1, 0));
}

TEST(Operand, check_value)
{
	operand a(13e-1, 0);
	EXPECT_EQ(true, abs(13e-1 - a.getValue()) < 1e-14);
}

TEST(Operand, check_correct_what)
{
	operand a(13e-1, 0);
	EXPECT_EQ(0, a.what());
}

TEST(Varible, can_create_varible)
{
	ASSERT_NO_THROW(varible a("x23", 0));
}

TEST(Varible, check_correct_what_before_init_value)
{
	varible a("x23", 0);
	EXPECT_EQ(-1, a.what());
}

TEST(Varible, can_init_varible)
{
	varible a("x23", 0);
	ASSERT_NO_THROW(a.initValue(345e-1));
}

TEST(Varible, check_after_init_varible)
{
	varible a("x23", 0);
	a.initValue(345e-1);
	EXPECT_EQ(true, abs(345e-1 - a.getValue()) < 1e-14);
}

TEST(Varible, check_correct_what_after_init_value)
{
	varible a("x23", 0);
	a.initValue(345e-1);
	EXPECT_EQ(0, a.what());
}

TEST(Varible, can_get_name_varible)
{
	varible a("x23", 0);
	EXPECT_EQ("x23", a.getName());
}

TEST(Lexem, can_get_initial_position_operation)
{
	operation a('l', 5);
	EXPECT_EQ(a.getInitPos(), 5);
}

TEST(Lexem, can_get_initial_position_operand)
{
	operand a(2345, 1);
	EXPECT_EQ(a.getInitPos(), 1);
}

TEST(Lexem, can_get_initial_position_varible)
{
	varible a("x234", 3);
	EXPECT_EQ(a.getInitPos(), 3);
}

TEST(VectorLexem, can_create_vector_lexem)
{
	ASSERT_NO_THROW(Vector<lexem*> lx);
}

TEST(VectorLexem, check_create_vector_lexem)
{
	Vector<lexem*> lx;
	lx.push_back(new operand(13e-1, 0));
	lx.push_back(new operation('-', 0));
	lx.push_back(new varible("x12", 0));
	EXPECT_EQ(0, lx[0]->what());
	EXPECT_EQ(1, lx[1]->what());
	EXPECT_EQ(-1, lx[2]->what());
	deleteLx(lx);
}