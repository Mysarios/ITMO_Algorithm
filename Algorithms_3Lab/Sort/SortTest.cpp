#include <algorithm>
#include <iostream>

#include "Lib/SortLibrary.h"
#include "vector"

auto asc_comparator = [](const int& a, const int& b) -> bool
{
    return a > b;
};
auto desc_comparator = [](const int& a, const int& b) -> bool
{
    return a < b;
};

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

constexpr int count_minimal = 3;
constexpr int count = 120;
constexpr int rand_limit = 3500;

struct time_check
{
    std::chrono::microseconds base;
    std::chrono::microseconds quick;
    std::chrono::microseconds insert;
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<time_check> result;
    int base_arr[count];
    for (int& i : base_arr)
    {
        i = rand() % rand_limit;
    }

    for (int check = count_minimal; check < count; ++check)
    {
        time_check new_result;

        const auto arr_1 = new int [check];
        const auto arr_2 = new int [check];
        const auto arr_3 = new int [check];

        int counter = 0;
        for (int i = 0; i < check; ++i)
        {
            arr_1[i] = base_arr[i];
            arr_2[i] = base_arr[i];
            arr_3[i] = base_arr[i];
            ++counter;
        }

        const std::chrono::microseconds first_sort_time = sort(arr_1, arr_1 + check, asc_comparator,
                                                               sort_namespace::base);
        const std::chrono::microseconds second_sort_time = sort(arr_2, arr_2 + check, asc_comparator,
                                                                sort_namespace::quick_sort);
        std::chrono::microseconds third_sort_time = sort(arr_3, arr_3 + check, asc_comparator,
                                                         sort_namespace::insert_sort);

        delete[] arr_1;
        delete[] arr_2;
        delete[] arr_3;

        new_result.base = first_sort_time;
        new_result.quick = second_sort_time;
        new_result.insert = third_sort_time;
        result.push_back(new_result);
    }

    int counter{0};
    for (auto time : result)
    {
        std::cout << counter++ << " Element: " << time.base.count() << " and " << time.quick.count() << " and " << time.
            insert.count() << '\n';
    }

    return 0;
}
