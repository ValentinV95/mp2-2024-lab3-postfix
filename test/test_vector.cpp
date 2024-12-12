#include "Vector.h"
#include <gtest.h>

TEST(Vector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(Vector<int> v(5));
}

TEST(Vector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(Vector<int> v(-5));
}

TEST(Vector, can_create_copied_vector)
{
	Vector<int> v(10);
	ASSERT_NO_THROW(Vector<int> v1(v));
}

TEST(Vector, copied_vector_is_equal_to_source_one)
{
	Vector<int> v(5);
	for (int i = 0; i < 5; i++)
	{
		v[i] = i;
	}
	Vector<int> v2 = v;
	EXPECT_EQ(v, v2);
}

TEST(Vector, copied_vector_has_its_own_memory)
{
	Vector<int> v(5);
	for (int i = 0; i < 5; i++)
	{
		v[i] = i;
	}
	Vector<int> v2 = v;
	v2[0] = 100;
	EXPECT_NE(v[0], v2[0]);
}

TEST(Vector, can_get_size)
{
	Vector<int> v(4);
	EXPECT_EQ(4, v.length());
}

TEST(Vector, can_set_and_get_element)
{
	Vector<int> v(4);
	v[0] = 4;
	EXPECT_EQ(4, v[0]);
}

TEST(Vector, can_assign_vector_to_itself)
{
	Vector<int> v(5);
	Vector<int> v2 = v;
	v = v;
	EXPECT_EQ(v2, v);
}

TEST(Vector, can_assign_vectors_of_equal_size)
{
	Vector<int> v(5), v2(5);
	ASSERT_NO_THROW(v = v2);
}

TEST(Vector, assign_operator_change_vector_size)
{
	Vector<int> v(4), v2(5);
	v = v2;
	EXPECT_EQ(v.length(), v2.length());
}

TEST(Vector, can_assign_vectors_of_different_size)
{
	Vector<int> v(5), v2(10);
	ASSERT_NO_THROW(v = v2);
}

TEST(Vector, can_push_back)
{
	Vector<int> v;
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(v.push_back(i));
	}
}

TEST(Vector, check_push_back_items)
{
	Vector<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
	}
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(i, v[i]);
	}
}

TEST(Vector, can_pop_back)
{
	Vector<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
	}
	v.pop_back();
	EXPECT_EQ(99, v.length());
}

TEST(Vector, can_clear)
{
	Vector<int> v(10);
	ASSERT_NO_THROW(v.clear());
	EXPECT_EQ(0, v.length());
}

TEST(Vector, check_length_before_clear)
{
	Vector<int> v(10);
	v.clear();
	EXPECT_EQ(0, v.length());
}