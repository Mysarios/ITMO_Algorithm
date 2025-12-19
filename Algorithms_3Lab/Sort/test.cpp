#include <gtest/gtest.h>
#include "Lib/SortLibrary.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

using namespace sort_namespace;


// Check sort func
template<typename T, typename Compare>
bool is_sorted(T* first, T* last, Compare comp) {
    if (first == last) return true;
    for (T* it = first + 1; it != last; ++it) {
        if (comp(*it, *(it - 1))) return false;
    }
    return true;
}

#pragma region Base_Types

TEST(SortTest, EmptyArray) {
    int* arr = nullptr;
    sort(arr, arr, [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_TRUE(true);
}

TEST(SortTest, SingleElement) {
    int arr[] = {42};
    sort(arr, arr + 1, [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_EQ(arr[0], 42);
}

TEST(SortTest, SortedArray) {
    int arr[] = {1, 2, 3, 4, 5};
    sort(arr, arr + 5, [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

TEST(SortTest, ReverseSortedArray) {
    int arr[] = {5, 4, 3, 2, 1};
    sort(arr, arr + 5, [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

TEST(SortTest, RandomArray) {
    std::vector<int> arr(100);
    std::iota(arr.begin(), arr.end(), 0);
    std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
    
    sort(arr.data(), arr.data() + arr.size(), [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_TRUE(is_sorted(arr.data(), arr.data() + arr.size(), [](int a, int b) { return a < b; }));
}

TEST(SortTest, Duplicates) {
    int arr[] = {5, 2, 5, 1, 2, 1};
    sort(arr, arr + 6, [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_TRUE(is_sorted(arr, arr + 6, [](int a, int b) { return a < b; }));
}
#pragma endregion

#pragma region Non_Base_Types
struct Student {
    std::string name;
    int age;
    bool operator<(const Student& other) const {
        return age < other.age;
    }
};

TEST(SortTest, CustomStruct) {
    Student people[] = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    sort(people, people + 3, [](const Student& a, const Student& b) { return a < b; }, quick_sort);
    EXPECT_TRUE(is_sorted(people, people + 3, [](const Student& a, const Student& b) { return a < b; }));
}
#pragma endregion

#pragma region Non_Base_Types
TEST(SortTest, BaseSort) {
    int arr[] = {5, 3, 4, 1, 2};
    sort(arr, arr + 4, [](int a, int b) { return a < b; }, base);
    EXPECT_TRUE(is_sorted(arr, arr + 4, [](int a, int b) { return a < b; }));
}

TEST(SortTest, InsertionSort) {
    int arr[] = {5, 3, 4, 1, 2};
    sort(arr, arr + 5, [](int a, int b) { return a < b; }, insert_sort);
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

TEST(SortTest, QuickSort) {
    int arr[] = {5, 3, 4, 1, 2};
    sort(arr, arr + 5, [](int a, int b) { return a < b; }, quick_sort);
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

#pragma endregion
