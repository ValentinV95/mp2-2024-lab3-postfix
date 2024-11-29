
#include "myvector.h"
#include <gtest.h>

TEST(myVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

//TEST(TDynamicVector, cant_create_too_large_vector)
//{
//	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
//}
//
//TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
//{
//	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
//}
//
//TEST(TDynamicVector, can_create_copied_vector)
//{
//	TDynamicVector<int> v(10);
//
//	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
//}
//
//TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
//{
//	TDynamicVector<int> v1(10);
//	for (int i = 0; i < 10; ++i)
//		v1[i] = i;
//	TDynamicVector<int> v2 = v1;
//
//	EXPECT_EQ(v1, v2);
//}
//
//TEST(TDynamicVector, copied_vector_has_its_own_memory)
//{
//	TDynamicVector<int> v1(10);
//	v1[5] = 4;
//	TDynamicVector<int> v2 = v1;
//	v2[5] = 3;
//
//	EXPECT_NE(v1, v2);
//}