#include <gtest.h>
#include "vector.h"

TEST(VectorTest, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.getsize(), 0);
    EXPECT_EQ(vec.getcapacity(), 1);
}

TEST(VectorTest, PushBack) {
    Vector<int> vec;
    vec.push_back(1);
    EXPECT_EQ(vec.getsize(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, PushBackMultiple) {
    Vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    EXPECT_EQ(vec.getsize(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(VectorTest, PopBack) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    EXPECT_EQ(vec.getsize(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, Clear) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.clear();
    EXPECT_EQ(vec.getsize(), 0);
}

TEST(VectorTest, Resize) {
    Vector<int> vec;
    ASSERT_NO_THROW(vec.resize(5));
    EXPECT_EQ(vec.getsize(), 5);
}

TEST(VectorTest, ResizeSmaller) {
    Vector<int> vec;
    vec.resize(10);
    vec.resize(5);
    EXPECT_EQ(vec.getsize(), 5);
}

TEST(VectorTest, At) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
}

TEST(VectorTest, AtOutOfBounds) {
    Vector<int> vec;
    vec.push_back(1);
    EXPECT_THROW(vec.at(1), std::out_of_range);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    Vector<int> vecCopy(vec);
    EXPECT_EQ(vecCopy.getsize(), 2);
    EXPECT_EQ(vecCopy[0], 1);
    EXPECT_EQ(vecCopy[1], 2);
}

TEST(VectorTest, AssignmentOperator) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    Vector<int> vecCopy;
    vecCopy = vec;
    EXPECT_EQ(vecCopy.getsize(), 2);
    EXPECT_EQ(vecCopy[0], 1);
    EXPECT_EQ(vecCopy[1], 2);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    Vector<int> vecMove(std::move(vec));
    EXPECT_EQ(vecMove.getsize(), 2);
    EXPECT_EQ(vecMove[0], 1);
    EXPECT_EQ(vecMove[1], 2);
    EXPECT_EQ(vec.getsize(), 0);
}

TEST(VectorTest, MoveAssignmentOperator) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    Vector<int> vecMove;
    vecMove = std::move(vec);
    EXPECT_EQ(vecMove.getsize(), 2);
    EXPECT_EQ(vecMove[0], 1);
    EXPECT_EQ(vecMove[1], 2);
    EXPECT_EQ(vec.getsize(), 0);
}

TEST(VectorTest, Front) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.front(), 1);
}

TEST(VectorTest, Back) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.back(), 2);
}

TEST(VectorTest, EqualityOperator) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    Vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    Vector<int> v3;
    v3.push_back(4);
    v3.push_back(5);
    v3.push_back(6);

    EXPECT_TRUE(v1 == v2); 
    EXPECT_FALSE(v1 == v3); 
}

TEST(VectorTest, InequalityOperator) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    Vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    Vector<int> v3;
    v3.push_back(4);
    v3.push_back(5);
    v3.push_back(6);

    EXPECT_FALSE(v1 != v2); 
    EXPECT_TRUE(v1 != v3);
}

TEST(VectorTest, EqualityOperatorDifferentSizes) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    Vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    EXPECT_FALSE(v1 == v2); 
}

TEST(VectorTest, InequalityOperatorDifferentSizes) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    Vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    EXPECT_TRUE(v1 != v2); 
}