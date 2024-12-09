#include "myvector.h"
#include <gtest.h>
#include <string>

myVector<int> foo() {
	myVector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	return v;
}

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


TEST(myVector, can_create_vector_with_no_operands)
{
	ASSERT_NO_THROW(myVector<int> v);
}

TEST(myVector, can_create_vector_with_zero_length)
{
	ASSERT_NO_THROW(myVector<int> v(0));
}

TEST(myVector, can_create_vector_with_positive_length_using_example)
{
	myVector<int> v(5, 12);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(v[i], 12);
	}
}

TEST(myVector, size_of_newcreated_vector_is_as_operand)
{
	myVector<int> v(5, 12);
	EXPECT_EQ(5, v.size());
}

TEST(myVector, size_of_newcreated_vector_with_no_operands_is_zero)
{
	myVector<int> v;
	EXPECT_EQ(0, v.size());
}

TEST(myVector, can_create_copied_vector)
{
	myVector<int> v(10, 1);

	ASSERT_NO_THROW(myVector<int> v1(v));
}

TEST(myVector, can_create_moved_vector)
{
	ASSERT_NO_THROW(myVector<int> v1(foo()));
}

TEST(myVector, copied_vector_is_equal_to_source_one)
{
	myVector<int> v1(10, 1);
	myVector<int> v2 = v1;

	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(myVector, moved_vector_is_equal_to_source_one)
{
	myVector<int> v2 = foo();

	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(i + 1, v2[i]);
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

	ASSERT_NO_THROW(v.size());
}

TEST(myVector, can_set_element)
{
	myVector<int> v(4);
	ASSERT_NO_THROW(v[0] = 4);

}

TEST(myVector, can_get_element)
{
	myVector<int> v(4);
	v[0] = 4;

	ASSERT_NO_THROW(v[0]);
}

TEST(myVector, set_and_get_element_is_correct)
{
	myVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(myVector, can_assign_vector_to_itself)
{
	myVector<int> v(10);
	for (int i = 0; i < 10; ++i) v[i] = i;
	myVector<int> w = v;

	ASSERT_NO_THROW(v = v);
}

TEST(myVector, assign_vector_to_itself_is_correct)
{
	myVector<int> v(10);
	for (int i = 0; i < 10; ++i) v[i] = i;
	myVector<int> w = v;

	v = v;
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
}

TEST(myVector, assign_operator_is_correct)
{
	myVector<int> v(10);
	myVector<int> w(12);
	for (int i = 0; i < 10; ++i) {
		v[i] = i;
		w[i] = 2 * i;
	}
	w[10] = 10;
	w[11] = 11;

	v = w;
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

TEST(myVector, can_assign_move_vectors) {
	myVector<int> v;
	ASSERT_NO_THROW(v = foo());
}

TEST(myVector, assign_moved_vector_is_correct) {
	myVector<int> v;
	v = foo();
	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(i + 1, v[i]);
}


TEST(myVector, can_push_back) {
	myVector<int> v(3, 2);

	ASSERT_NO_THROW(v.push_back(4));
}

TEST(myVector, push_back_is_correct) {
	myVector<int> v(3, 2);

	v.push_back(4);
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
}

TEST(myVector, resize_changes_size) {
	myVector<int> v(3, 2);

	v.resize(6);
	EXPECT_EQ(6, v.size());
}

TEST(myVector, resize_fills_with_zeros) {
	myVector<int> v(3, 2);

	v.resize(6);
	EXPECT_EQ(0, v[5]);
}

TEST(myVector, can_resize_vector_smaller) {
	myVector<int> v(6, 2);

	ASSERT_NO_THROW(v.resize(3));
}

TEST(myVector, resize_vector_smaller_changes_size) {
	myVector<int> v(6, 2);

	v.resize(3);
	EXPECT_EQ(3, v.size());
}

TEST(myVector, resize_vector_smaller_not_changes_elements) {
	myVector<int> v(6, 2);

	v.resize(3);
	EXPECT_EQ(2, v[2]);
}

// COMPLEX TYPE

using namespace std;

myVector<string> foo2() {
	myVector<string> v;
	v.push_back("1");
	v.push_back("2");
	v.push_back("3");
	return v;
}

TEST(myVector, can_create_vector_with_positive_length_string)
{
	ASSERT_NO_THROW(myVector<string> v(5));
}

TEST(myVector, createed_vector_is_filled_with_zeros_string)
{
	myVector<string> v(5);
	for (int i = 0; i < 5; ++i)
		EXPECT_EQ("", v[i]);
}


TEST(myVector, can_create_vector_with_no_operands_string)
{
	ASSERT_NO_THROW(myVector<string> v);
}

TEST(myVector, can_create_vector_with_zero_length_string)
{
	ASSERT_NO_THROW(myVector<string> v(0));
}

TEST(myVector, can_create_vector_with_positive_length_using_example_string)
{
	myVector<string> v(5, "12");
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(v[i], "12");
	}
}

TEST(myVector, size_of_newcreated_vector_is_as_operand_string)
{
	myVector<string> v(5, "12");
	EXPECT_EQ(5, v.size());
}

TEST(myVector, size_of_newcreated_vector_with_no_operands_is_zero_string)
{
	myVector<string> v;
	EXPECT_EQ(0, v.size());
}

TEST(myVector, can_create_copied_vector_string)
{
	myVector<string> v(10, "1");

	ASSERT_NO_THROW(myVector<string> v1(v));
}

TEST(myVector, can_create_moved_vector_string)
{
	ASSERT_NO_THROW(myVector<string> v1(foo2()));
}

TEST(myVector, copied_vector_is_equal_to_source_one_string)
{
	myVector<string> v1(10, "1");
	myVector<string> v2 = v1;

	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v1[i], v2[i]);
}

TEST(myVector, moved_vector_is_equal_to_source_one_string)
{
	myVector<string> v2 = foo2();

	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(to_string(i + 1), v2[i]);
}

TEST(myVector, copied_vector_has_its_own_memory_string)
{
	myVector<string> v1(10, "12");
	v1[5] = "4";
	myVector<string> v2 = v1;
	v2[5] = "3";

	EXPECT_NE(v1[5], v2[5]);
}

TEST(myVector, can_get_size_string)
{
	myVector<string> v(4);

	ASSERT_NO_THROW(v.size());
}

TEST(myVector, can_set_element_string)
{
	myVector<string> v(4);
	ASSERT_NO_THROW(v[0] = "4");

}

TEST(myVector, can_get_element_string)
{
	myVector<string> v(4);
	v[0] = "4";

	ASSERT_NO_THROW(v[0]);
}

TEST(myVector, set_and_get_element_is_correct_string)
{
	myVector<string> v(4);
	v[0] = "4";

	EXPECT_EQ("4", v[0]);
}

TEST(myVector, can_assign_vector_to_itself_string)
{
	myVector<string> v(10);
	for (int i = 0; i < 10; ++i) v[i] = i;
	myVector<string> w = v;

	ASSERT_NO_THROW(v = v);
}

TEST(myVector, assign_vector_to_itself_is_correct_string)
{
	myVector<string> v(10);
	for (int i = 0; i < 10; ++i) v[i] = i;
	myVector<string> w = v;

	v = v;
	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v[i], w[i]);
}

TEST(myVector, can_assign_vectors_of_equal_size_string)
{
	myVector<string> v(10);
	myVector<string> w(10);
	for (int i = 0; i < 10; ++i) {
		v[i] = to_string(i);
		w[i] = to_string(2 * i);
	}

	ASSERT_NO_THROW(v = w);
}

TEST(myVector, assign_operator_change_vector_size_string)
{
	myVector<string> v(10);
	myVector<string> w(12);
	for (int i = 0; i < 10; ++i) {
		v[i] = to_string(i);
		w[i] = to_string(2 * i);
	}
	w[10] = "10";
	w[11] = "11";

	EXPECT_EQ((v = w).size(), 12);
}

TEST(myVector, assign_operator_is_correct_string)
{
	myVector<string> v(10);
	myVector<string> w(12);
	for (int i = 0; i < 10; ++i) {
		v[i] = to_string(i);
		w[i] = to_string(2 * i);
	}
	w[10] = "10";
	w[11] = "11";

	v = w;
	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(v[i], w[i]);
}

TEST(myVector, can_assign_vectors_of_different_size_string)
{
	myVector<string> v(10);
	myVector<string> w(12);
	for (int i = 0; i < 10; ++i) {
		v[i] = to_string(i);
		w[i] = to_string(2 * i);
	}
	w[10] = "10";
	w[11] = "11";

	ASSERT_NO_THROW(v = w);
}

TEST(myVector, can_assign_move_vectors_string) {
	myVector<string> v;
	ASSERT_NO_THROW(v = foo2());
}

TEST(myVector, assign_moved_vector_is_correct_string) {
	myVector<string> v;
	v = foo2();
	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(to_string(i + 1), v[i]);
}


TEST(myVector, can_push_back_string) {
	myVector<string> v(3, "2");

	ASSERT_NO_THROW(v.push_back("4"));
}

TEST(myVector, push_back_is_correct_string) {
	myVector<string> v(3, "2");

	v.push_back("4");
	EXPECT_EQ("4", v[3]);
}

TEST(myVector, push_back_changes_size_string) {
	myVector<string> v(3, "2");

	v.push_back("4");
	EXPECT_EQ(4, v.size());
}

TEST(myVector, can_resize_vector_bigger_string) {
	myVector<string> v(3, "2");

	ASSERT_NO_THROW(v.resize(6));
}

TEST(myVector, resize_changes_size_string) {
	myVector<string> v(3, "2");

	v.resize(6);
	EXPECT_EQ(6, v.size());
}

TEST(myVector, resize_fills_with_zeros_string) {
	myVector<string> v(3, "2");

	v.resize(6);
	EXPECT_EQ("", v[5]);
}

TEST(myVector, can_resize_vector_smaller_string) {
	myVector<string> v(6, "2");

	ASSERT_NO_THROW(v.resize(3));
}

TEST(myVector, resize_vector_smaller_changes_size_string) {
	myVector<string> v(6, "2");

	v.resize(3);
	EXPECT_EQ(3, v.size());
}

TEST(myVector, resize_vector_smaller_not_changes_elements_string) {
	myVector<string> v(6, "2");

	v.resize(3);
	EXPECT_EQ("2", v[2]);
}