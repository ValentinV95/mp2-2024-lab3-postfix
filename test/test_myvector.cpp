#include "myvector.h"
#include <gtest.h>

TEST(myVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(myVector<int> v(5));
}

TEST(myVector, createed_vector_is_filled_with_zeros)
{
	myVector<int> v(5);
	for (int i = 0; i < 5; ++i)
		EXPECT_EQ(0, v[i]);
}


TEST(myVector, can_create_vector_with_zero_length)
{
	ASSERT_NO_THROW(myVector<int> v());
	ASSERT_NO_THROW(myVector<int> v(0));
}

TEST(myVector, can_create_vector_with_positive_length_using_example)
{
	myVector<int> v(5, 12);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(v[i], 12);
	}
}

TEST(myVector, can_create_copied_vector)
{
	myVector<int> v(10, 1);

	ASSERT_NO_THROW(myVector<int> v1(v));
}

TEST(myVector, copied_vector_is_equal_to_source_one)
{
	myVector<int> v1(10, 1);
	myVector<int> v2 = v1;

	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(myVector, copied_vector_has_its_own_memory)
{
	myVector<int> v1(10, 12);
	v1[5] = 4;
	myVector<int> v2 = v1;
	v2[5] = 3;

	EXPECT_NE(v1[5], v2[5]);
}

TEST(myVector, can_get_size)
{
	myVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(myVector, can_set_and_get_element)
{
	myVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

/*
TEST(myVector, throws_when_set_element_with_negative_index)
{
	myVector<int> v(4);

	ASSERT_ANY_THROW(v.at(-4));
}

TEST(myVector, throws_when_set_element_with_too_large_index)
{
	myVector<int> v(4);

	ASSERT_ANY_THROW(v.at(4));
}
*/

TEST(myVector, can_assign_vector_to_itself)
{
	myVector<int> v(10);
	for (int i = 0; i < 10; ++i) v[i] = i;
	myVector<int> w = v;

	ASSERT_NO_THROW(v = v);
	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v[i], w[i]);
}

TEST(myVector, can_assign_vectors_of_equal_size)
{
	myVector<int> v(10);
	myVector<int> w(10);
	for (int i = 0; i < 10; ++i) {
		v[i] = i;
		w[i] = 2 * i;
	}

	ASSERT_NO_THROW(v = w);
}

TEST(myVector, assign_operator_change_vector_size)
{
	myVector<int> v(10);
	myVector<int> w(12);
	for (int i = 0; i < 10; ++i) {
		v[i] = i;
		w[i] = 2 * i;
	}
	w[10] = 10;
	w[11] = 11;

	EXPECT_EQ((v = w).size(), 12);
	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v[i], w[i]);
}

TEST(myVector, can_assign_vectors_of_different_size)
{
	myVector<int> v(10);
	myVector<int> w(12);
	for (int i = 0; i < 10; ++i) {
		v[i] = i;
		w[i] = 2 * i;
	}
	w[10] = 10;
	w[11] = 11;

	ASSERT_NO_THROW(v = w);
}

TEST(myVector, can_push_back_vector) {
	myVector<int> v(3, 2);

	ASSERT_NO_THROW(v.push_back(4));
	EXPECT_EQ(4, v[3]);
}

TEST(myVector, push_back_changes_size) {
	myVector<int> v(3, 2);

	v.push_back(4);
	EXPECT_EQ(4, v.size());
}

TEST(myVector, can_resize_vector_bigger) {
	myVector<int> v(3, 2);

	ASSERT_NO_THROW(v.resize(6));
	EXPECT_EQ(6, v.size());
	EXPECT_EQ(0, v[5]);
}

TEST(myVector, can_resize_vector_smaller) {
	myVector<int> v(6, 2);

	ASSERT_NO_THROW(v.resize(3));
	EXPECT_EQ(3, v.size());
	EXPECT_EQ(2, v[2]);
}