#pragma once
#include "TArray.h"

class TArrayTest : public ::testing::Test {
protected:
    TArray<int> array_;
    
    void SetUp() override {
        array_ = TArray<int>(4);
    }
    void TearDown() override {
    }
    
};
// Тест конструкторов
TEST_F(TArrayTest, DefaultConstructor) {
    const TArray<int> empty;
    EXPECT_EQ(empty.size(), 0);
    EXPECT_GE(empty.capacity(), 8);
}
TEST_F(TArrayTest, ConstructorWithCapacity) {
    const TArray<int> custom(10);
    EXPECT_EQ(custom.size(), 0);
    EXPECT_EQ(custom.capacity(), 10);
}
// Тест вставки
TEST_F(TArrayTest, InsertEnd) {
    array_.insert(1);
    EXPECT_EQ(array_.size(), 1);
    EXPECT_EQ(array_[0], 1);
}
TEST_F(TArrayTest, InsertAtIndex) {
    array_.insert(1);
    array_.insert(2);
    array_.insert(1, 99);  // Вставка в середину
    EXPECT_EQ(array_.size(), 3);
    EXPECT_EQ(array_[0], 1);
    EXPECT_EQ(array_[1], 99);
    EXPECT_EQ(array_[2], 2);
}
TEST_F(TArrayTest, InsertWithResize) {
    for (int i = 0; i < 5; ++i) {  // Превышает capacity 4
        array_.insert(i);
    }
    EXPECT_EQ(array_.size(), 5);
    EXPECT_GE(array_.capacity(), 8);  // После resize
}
// Тест удаления
TEST_F(TArrayTest, Remove) {
    array_.insert(1);
    array_.insert(2);
    array_.insert(3);
    
array_.remove(1);  // Удалить второй элемент
EXPECT_EQ(array_.size(), 2);
EXPECT_EQ(array_[0], 1);
EXPECT_EQ(array_[1], 3);
}
// Тест итераторов
TEST_F(TArrayTest, IteratorTraversal) {
    array_.insert(1);
    array_.insert(2);
    array_.insert(3);
    
    auto it = array_.iterator();
    EXPECT_TRUE(it.has_next());
    EXPECT_EQ(it.get(), 1);
    it.next();
    EXPECT_EQ(it.get(), 2);
    it.next();
    EXPECT_EQ(it.get(), 3);
    it.next();
    EXPECT_FALSE(it.has_next());
}
TEST_F(TArrayTest, RangeBasedFor) {
    array_.insert(1);
    array_.insert(2);
    int sum = 0;
    for (const auto& elem : array_) {
        sum += elem;
    }
    EXPECT_EQ(sum, 3);
}

// Тест edge cases
TEST_F(TArrayTest, EmptyArray) {
    EXPECT_EQ(array_.size(), 0);
    auto it = array_.iterator();
    EXPECT_FALSE(it.has_next());
}
TEST_F(TArrayTest, CopyConstructor) {
    array_.insert(1);
    array_.insert(2);
    TArray<int> copy = array_;
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
}