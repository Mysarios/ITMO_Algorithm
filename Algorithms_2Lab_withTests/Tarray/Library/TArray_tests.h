#pragma once
#include <chrono>

#include "TArray.h"

class TArrayTest : public ::testing::Test
{
protected:
    TArray<int> array_;

    void SetUp() override
    {
        array_ = TArray<int>(4);
    }

    void TearDown() override
    {
    }
};

class TArrayStringTest : public ::testing::Test
{
protected:
    TArray<std::string> string_array_;

    void SetUp() override
    {
        string_array_ = TArray<std::string>(4);
    }
};

class TArrayVsVectorTest : public ::testing::Test
{
protected:
    TArray<int> tarray_;
    std::vector<int> stdvector_;

    void SetUp() override
    {
        tarray_ = TArray<int>(10);
    }

    void compare()
    {
        ASSERT_EQ(tarray_.size(), stdvector_.size());
        for (size_t i = 0; i < stdvector_.size(); ++i)
        {
            EXPECT_EQ(tarray_[i], stdvector_[i])
                << "Mismatch at index " << i;
        }
    }
};

// Тест конструкторов
TEST_F(TArrayTest, DefaultConstructor)
{
    const TArray<int> empty;
    EXPECT_EQ(empty.size(), 0);
    EXPECT_GE(empty.capacity(), 8);
}

TEST_F(TArrayTest, ConstructorWithCapacity)
{
    const TArray<int> custom(10);
    EXPECT_EQ(custom.size(), 0);
    EXPECT_EQ(custom.capacity(), 10);
}

// Тест вставки
TEST_F(TArrayTest, InsertEnd)
{
    array_.insert(1);
    EXPECT_EQ(array_.size(), 1);
    EXPECT_EQ(array_[0], 1);
}

TEST_F(TArrayTest, InsertAtIndex)
{
    array_.insert(1);
    array_.insert(2);
    array_.insert(1, 99);
    EXPECT_EQ(array_.size(), 3);
    EXPECT_EQ(array_[0], 1);
    EXPECT_EQ(array_[1], 99);
    EXPECT_EQ(array_[2], 2);
}

TEST_F(TArrayTest, InsertWithResize)
{
    for (int i = 0; i < 5; ++i)
    {
        array_.insert(i);
    }
    EXPECT_EQ(array_.size(), 5);
    EXPECT_GE(array_.capacity(), 8);
}

// Тест удаления
TEST_F(TArrayTest, Remove)
{
    array_.insert(1);
    array_.insert(2);
    array_.insert(3);

    array_.remove(1);
    EXPECT_EQ(array_.size(), 2);
    EXPECT_EQ(array_[0], 1);
    EXPECT_EQ(array_[1], 3);
}

// Тест итераторов
TEST_F(TArrayTest, IteratorTraversal)
{
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

TEST_F(TArrayTest, RangeBasedFor)
{
    array_.insert(1);
    array_.insert(2);
    int sum = 0;
    for (const auto& elem : array_)
    {
        sum += elem;
    }
    EXPECT_EQ(sum, 3);
}

// Тест ХэсНекст
TEST_F(TArrayTest, EmptyArray)
{
    EXPECT_EQ(array_.size(), 0);
    auto it = array_.iterator();
    EXPECT_FALSE(it.has_next());
}

TEST_F(TArrayTest, CopyConstructor)
{
    array_.insert(1);
    array_.insert(2);
    TArray<int> copy = array_;
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
}

//Тест на строки
TEST_F(TArrayStringTest, DefaultConstructorForStrings)
{
    const TArray<std::string> empty;
    EXPECT_EQ(empty.size(), 0);
    EXPECT_GE(empty.capacity(), 8);
}

TEST_F(TArrayStringTest, InsertAndRemoveStrings)
{
    string_array_.insert("Hello");
    string_array_.insert("World");
    string_array_.insert("Test");

    EXPECT_EQ(string_array_.size(), 3);
    EXPECT_EQ(string_array_[0], "Hello");
    EXPECT_EQ(string_array_[1], "World");
    EXPECT_EQ(string_array_[2], "Test");

    string_array_.insert(1, "Beautiful");
    EXPECT_EQ(string_array_[1], "Beautiful");
    EXPECT_EQ(string_array_[2], "World");

    string_array_.remove(0);
    EXPECT_EQ(string_array_[0], "Beautiful");
    EXPECT_EQ(string_array_.size(), 3);
}

TEST_F(TArrayStringTest, LongStrings)
{
    std::string longStr(1000, 'X');
    string_array_.insert(longStr);
    string_array_.insert(std::string(500, 'Y'));

    EXPECT_EQ(string_array_.size(), 2);
    EXPECT_EQ(string_array_[0], longStr);
    EXPECT_EQ(string_array_[1], std::string(500, 'Y'));
}

TEST_F(TArrayStringTest, EmptyStrings)
{
    string_array_.insert("");
    string_array_.insert("not empty");
    string_array_.insert("");

    EXPECT_EQ(string_array_.size(), 3);
    EXPECT_TRUE(string_array_[0].empty());
    EXPECT_FALSE(string_array_[1].empty());
    EXPECT_TRUE(string_array_[2].empty());
}


// Битва с вектором

TEST_F(TArrayVsVectorTest, InsertionComparison)
{
    for (int i = 0; i < 100; ++i)
    {
        tarray_.insert(i);
        stdvector_.push_back(i);
    }
    compare();
}

TEST_F(TArrayVsVectorTest, InsertAtPositionComparison)
{
    for (int i = 0; i < 10; ++i)
    {
        tarray_.insert(i);
        stdvector_.push_back(i);
    }

    tarray_.insert(5, 999);
    stdvector_.insert(stdvector_.begin() + 5, 999);

    compare();
}

// Тест удаления
TEST_F(TArrayVsVectorTest, RemovalComparison)
{
    for (int i = 0; i < 10; ++i)
    {
        tarray_.insert(i);
        stdvector_.push_back(i);
    }

    tarray_.remove(5);
    stdvector_.erase(stdvector_.begin() + 5);
    compare();

    tarray_.remove(0);
    stdvector_.erase(stdvector_.begin());
    compare();

    tarray_.remove(tarray_.size() - 1);
    stdvector_.pop_back();
    compare();
}

// Тест производительности
TEST_F(TArrayVsVectorTest, PerformanceInsertAtEnd)
{
    const int count_el = 10000;

    auto start_tarray = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_el; ++i)
    {
        tarray_.insert(i);
    }
    auto end_tarray = std::chrono::high_resolution_clock::now();

    auto start_vector = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_el; ++i)
    {
        stdvector_.push_back(i);
    }
    auto end_vector = std::chrono::high_resolution_clock::now();

    auto tarray_time = std::chrono::duration_cast<std::chrono::microseconds>(end_tarray - start_tarray);
    auto vector_time = std::chrono::duration_cast<std::chrono::microseconds>(end_vector - start_vector);
    compare();

    std::cout << "TArray time: " << tarray_time.count() << "μs\n";
    std::cout << "std::vector time: " << vector_time.count() << "μs\n";

    EXPECT_LE(tarray_time.count(), vector_time.count() * 2)
        << "TArray shouldn't be more than 2x slower than std::vector";
}

// Тест производительности 2
TEST_F(TArrayVsVectorTest, PerformanceInsertAtEndPrepaired)
{
    const int count_el = 10000;
    stdvector_.reserve(10000);

    auto start_tarray = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_el; ++i)
    {
        tarray_.insert(i);
    }
    auto end_tarray = std::chrono::high_resolution_clock::now();

    auto start_vector = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_el; ++i)
    {
        stdvector_.push_back(i);
    }
    auto end_vector = std::chrono::high_resolution_clock::now();

    auto tarray_time = std::chrono::duration_cast<std::chrono::microseconds>(end_tarray - start_tarray);
    auto vector_time = std::chrono::duration_cast<std::chrono::microseconds>(end_vector - start_vector);
    compare();

    std::cout << "TArray time: " << tarray_time.count() << "μs\n";
    std::cout << "std::vector time: " << vector_time.count() << "μs\n";

    EXPECT_LE(tarray_time.count(), vector_time.count() * 2)
        << "TArray shouldn't be more than 2x slower than std::vector";
}

TEST_F(TArrayVsVectorTest, MultipleResizeComparison)
{
    const int count_el = 1000;
    constexpr int checked_times = 10;

    for (int i = 0; i < count_el; ++i)
    {
        tarray_.insert(i);
        stdvector_.push_back(i);

        if (i % (1000 / checked_times) == 0)
        {
            compare();
        }
    }
    compare();
}


TEST_F(TArrayVsVectorTest, CopyComparison)
{
    for (int i = 0; i < 10; ++i)
    {
        tarray_.insert(i * 2);
        stdvector_.push_back(i * 2);
    }

    TArray<int> tarray_copy = tarray_;
    std::vector<int> stdvector_copy = stdvector_;

    ASSERT_EQ(tarray_copy.size(), stdvector_copy.size());
    for (size_t i = 0; i < stdvector_copy.size(); ++i)
    {
        EXPECT_EQ(tarray_copy[i], stdvector_copy[i]);
    }

    tarray_.insert(999);
    stdvector_.push_back(999);

    EXPECT_EQ(tarray_copy.size(), stdvector_copy.size());
}


/*TEST_F(TArrayVsVectorTest, EdgeCases)
{
    compare();

    tarray_.insert(42);
    stdvector_.push_back(42);
    compare();

    for (int i = 0; i < 5; ++i)
    {
        tarray_.remove(0);
        stdvector_.erase(stdvector_.begin());
    }

    for (int i = 0; i < 20; ++i)
    {
        tarray_.insert(i + 100);
        stdvector_.push_back(i + 100);
    }
    compare();
}*/
