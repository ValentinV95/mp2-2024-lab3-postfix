#pragma once
#include <gtest.h>
#include "lexem.h"

TEST(operation, can_be_created)
{
	ASSERT_NO_THROW(operation a);
}

TEST(operation, is_statement)
{
	operation a;
	EXPECT_TRUE(a.IsStmt());
}

TEST(operation, can_be_created_with_id)
{
	ASSERT_NO_THROW(operation a(4));
}

TEST(operation, throws_when_created_with_inappropriate_id)
{
	ASSERT_ANY_THROW(operation a(-1));
	ASSERT_ANY_THROW(operation b(30));
}

TEST(operation, can_get_its_fields)
{
	operation a(10);
	EXPECT_EQ(10, a.GetId());
	EXPECT_EQ(4, a.GetPriority());
	EXPECT_EQ(1, a.GetArity());
	EXPECT_EQ("sin", a.GetName());
}

TEST(operation, getting_name_from_default_constructed_throws)
{
	operation a;
	ASSERT_ANY_THROW(a.GetName());
}

TEST(operation, can_be_copied)
{
	operation a(4);
	ASSERT_NO_THROW(operation b(a));
}

TEST(operation, copied_equals_to_source)
{
	operation a(4), b(a);
	EXPECT_EQ(a.GetPriority(), b.GetPriority());
	EXPECT_EQ(a.GetId(), b.GetId());
	EXPECT_EQ(a.GetName(), b.GetName());
	EXPECT_EQ(a.GetArity(), b.GetArity());
}

TEST(operation, can_identify_operation_by_string)
{
	size_t id;
	ASSERT_NO_THROW(id = operation::StmtId("acos"));
	EXPECT_EQ(15, id);
}

TEST(operation, indicates_when_string_is_not_an_operation)
{
	size_t id;
	id = operation::StmtId("ceil");
	EXPECT_EQ(-1, id);
}

/* Don't now if folowing Test needed:
TEST(operation, pointer_can_be_assigned_to_base_class_pointer)
{
	lexem* A;
	operation* B = new operation(2);
	ASSERT_NO_THROW(A = B);
	delete B;
}

TEST(operation, being_assigned_to_basic_class_pointer_can_be_casted_to_itself)
{
	operation* B = new operation(2),* C;
	lexem* A = B;
	ASSERT_NO_THROW(C = dynamic_cast<operation*>(A));
}
*/

