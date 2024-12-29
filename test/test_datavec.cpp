// тесты для вектора, на котором написан стек

#include "datavec.h"
#include <gtest.h>

TEST(Vec, can_create_vector_with_positive_capacity)
{
	ASSERT_NO_THROW(Vec<int> v(5));
}

TEST(Vec, cant_create_too_large_vector)
{
	size_t sz = (1ull << 32) / sizeof(int);
	ASSERT_ANY_THROW(Vec<int> v(sz));
}

TEST(Vec, throws_when_create_vector_with_zero_capacity)
{
	ASSERT_ANY_THROW(Vec<int> v(-5));
}

TEST(Vec, can_get_size)
{
	Vec<int> v(4);
	v.SetSize(2);
	EXPECT_EQ(2, v.GetSize());
}

TEST(Vec, can_get_capacity)
{
	Vec<int> v(4);
	EXPECT_EQ(4, v.GetCapacity());
}

TEST(Vec, can_access_to_its_memory_via_squre_brackets)
{
	Vec<int> v(5);
	int* p = v.GetData();
	int a = 0;
	v.SetSize(5);
	v[2] = 5;
	EXPECT_EQ(5, p[2]);
	a = v[2];
	EXPECT_EQ(5, a);
	v[2] += 4;
	EXPECT_EQ(9, p[2]);
}

TEST(Vec, can_create_copied_vector)
{
	Vec<int> v(10);
	ASSERT_NO_THROW(Vec<int> w(v));
}

TEST(Vec, copied_vector_is_equal_to_source_one)
{
	Vec<int> v(20);
	int offset = 0, scale = 1;
	v.SetSize(10);
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
	}
	Vec<int> w(v);
	EXPECT_EQ(v, w);
}

TEST(Vec, copied_vector_has_its_own_memory)
{
	Vec<int> v(64), t(64);
	int offset = 0, scale = 1;
	v.SetSize(64);
	t.SetSize(64);
	for (size_t i = 0; i < 64; i++)
	{
		v[i] = (0);
		t[i] = (0);
	}
	Vec<int> w(v);
	for (size_t i = 0; i < 64; i++)
	{
		w[i] = 1;
	}
	EXPECT_EQ(t, v);
	EXPECT_NE(v, w);
}

TEST(Vec, can_be_assigned)
{
	Vec<int> v(64), t(32);
	v.SetSize(64);
	t.SetSize(32);
	for (size_t i = 0; i < 64; i++)
		v[i] = i;
	ASSERT_NO_THROW(t = v);
}

TEST(Vec, assigned_vec_equals_to_its_source)
{
	Vec<int> v(64), t(32);
	v.SetSize(64);
	t.SetSize(32);
	for (size_t i = 0; i < 64; i++)
		v[i] = i;
	t = v;
	EXPECT_EQ(t, v);
}

TEST(Vec, assigned_vec_has_its_own_memory)
{
	Vec<int> v(64), w(64), t(32);
	v.SetSize(64);
	w.SetSize(64);
	t.SetSize(32);
	for (size_t i = 0; i < 64; i++)
	{
		v[i] = i;
		w[i] = i;
	}
	t = v;
	for (size_t i = 0; i < 64; i++)
		v[i] = 5;
	EXPECT_EQ(t, w);
	EXPECT_NE(t, v);
}

TEST(Vec, can_be_assigned_to_itself)
{
	Vec<int> v(64), w(64);
	v.SetSize(64);
	w.SetSize(64);
	for (size_t i = 0; i < 64; i++)
	{
		v[i] = i;
		w[i] = i;
	}
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v, w);
}

TEST(Vec, can_create_vector_with_T_pointer)
{
	int sz = 10;
	int* arr = new int[sz];
	ASSERT_NO_THROW(Vec<int> v(arr, sz));
	delete[] arr;
	sz = 80;
	arr = new int[sz];
	ASSERT_NO_THROW(Vec<int> w(arr, sz));
	delete[] arr;
}

TEST(Vec, elements_of_vector_created_with_T_point_are_equal_to_el_from_array)
{
	int sz = 10, offset = 0, scale = 1;
	int* arr = new int[sz];
	Vec<int> w, u(80 * 3 / 2);
	w.SetSize(sz);
	u.SetSize(80);
	for (size_t i = 0; i < sz; i++)
	{
		arr[i] = (offset + i * scale);
		w[i] = (offset + i * scale);
	}
	Vec<int> v(arr, sz);
	EXPECT_EQ(w, v);
	delete[] arr;
	sz = 80;
	arr = new int[sz];
	for (size_t i = 0; i < sz; i++)
	{
		arr[i] = (offset + i * scale);
		u[i] = (offset + i * scale);
	}
	Vec<int> t(arr, sz);
	EXPECT_EQ(u, t);
}

TEST(Vec, vector_created_with_T_pointer_has_its_own_memory)
{
	int sz = 10, offset = 0, scale = 1;
	int* arr = new int[sz];
	Vec<int> w(sz), t(sz);
	w.SetSize(10);
	t.SetSize(10);
	for (size_t i = 0; i < sz; i++)
	{
		arr[i] = (offset + i * scale);
		w[i] = (offset + i * scale);
	}
	Vec<int> v(arr, sz);
	offset = 1, scale = 2;
	for (size_t i = 0; i < sz; i++)
		v[i] = (offset + i * scale);
	for (size_t i = 0; i < sz; i++)
		t[i] = arr[i];
	EXPECT_EQ(w, t);
	EXPECT_NE(w, v);
	delete[] arr;
}

TEST(Vec, can_determine_if_its_empty_or_full)
{
	Vec<int> v(10);
	v.SetSize(0);
	EXPECT_EQ(false, v.Is_Full());
	EXPECT_EQ(true, v.Is_Empty());
	v.SetSize(5);
	EXPECT_EQ(false, v.Is_Full());
	EXPECT_EQ(false, v.Is_Empty());
	v.SetSize(10);
	EXPECT_EQ(true, v.Is_Full());
	EXPECT_EQ(false, v.Is_Empty());
}

TEST(Vec, can_take_value_from_its_top)
{
	Vec<int> v(10);
	v.SetSize(10);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(a = v.Top());
	EXPECT_EQ(9, a);
}

TEST(Vec, taking_value_from_empty_vector_throws)
{
	Vec<int> v(10);
	int i;
	ASSERT_ANY_THROW(i = v.Top());
}

TEST(Vec, can_push_value_to_its_top)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(v.push_back(15));
}

TEST(Vec, pushing_a_value_changes_vector_size)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	v.push_back(15);
	EXPECT_EQ(6, v.GetSize());
}

TEST(Vec, pushed_value_equal_to_its_source)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	v.push_back(15);
	EXPECT_EQ(15, v.Top());
}

TEST(Vec, pushing_value_to_full_vector_causes_rearrange_and_saves_the_value)
{
	Vec<int> v(10);
	v.SetSize(10);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(v.push_back(11));
	EXPECT_TRUE(10 < v.GetCapacity());
	EXPECT_EQ(11, v.GetSize());
	EXPECT_EQ(11, v.Top());
}

TEST(Vec, push_does_not_change_previous_values)
{
	Vec<int> v(10);
	v.SetSize(10);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
	}
	v.push_back(11);
	for (size_t i = 0; i < 10; i++)
	{
		EXPECT_EQ(i, v[i]);
	}
}

TEST(Vec, can_pop_from_its_top)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(v.pop_back());
}

TEST(Vec, popping_changes_vector_size)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	v.pop_back();
	EXPECT_EQ(4, v.GetSize());
}

TEST(Vec, popping_from_empty_vector_throws)
{
	Vec<int> v(10);
	ASSERT_ANY_THROW(v.pop_back());
}

TEST(Vec, can_clear_itself)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1, a;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(v.clear());
}

TEST(Vec, clearing_itself_changes_size)
{
	Vec<int> v(10);
	v.SetSize(5);
	int offset = 0, scale = 1;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = (offset + i * scale);
	}
	v.clear();
	EXPECT_EQ(0, v.GetSize());
}

TEST(Vec, can_be_moved)
{
	Vec<int> v(10);
	v.SetSize(10);
	int offset = 0, scale = 1;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(Vec<int> t(std::move(v)));
}

TEST(Vec, moved_vec_equals_to_its_source)
{
	Vec<int> v(10), w(10);
	v.SetSize(10);
	w.SetSize(10);
	int offset = 0, scale = 1;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
		w[i] = (offset + i * scale);
	}
	Vec<int> t(std::move(v));
	EXPECT_EQ(t, w);
}

TEST(Vec, can_be_assigned_moved)
{
	Vec<int> v(10), t(10);
	v.SetSize(10), t.SetSize(10);
	int offset = 0, scale = 1;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
	}
	ASSERT_NO_THROW(t = std::move(v));
}

TEST(Vec, assigned_moved_vec_equals_to_its_source)
{
	Vec<int> v(10), w(10), t;
	v.SetSize(10);
	w.SetSize(10);
	int offset = 0, scale = 1;
	for (size_t i = 0; i < 10; i++)
	{
		v[i] = (offset + i * scale);
		w[i] = (offset + i * scale);
	}
	t = std::move(v);
	EXPECT_EQ(t, w);
}
