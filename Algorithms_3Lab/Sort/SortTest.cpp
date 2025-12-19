#include <algorithm>
#include <iostream>
#include <gtest/gtest.h>

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

constexpr int count_minimal = 15;
constexpr int count = 400;
constexpr int rand_limit = 15321;

struct time_check
{
    std::chrono::microseconds base;
    std::chrono::microseconds quick;
    std::chrono::microseconds insert;
    std::chrono::microseconds fast;
};


int main(int argc, char** argv)
{
    if (1)
    {
        ::testing::InitGoogleTest(&argc, argv);
        RUN_ALL_TESTS();
    }

    //std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<time_check> result;
    int base_arr[count];
    for (int& i : base_arr)
    {
        i = rand() % rand_limit;
    }


    if (0)
    {
        print_array(base_arr, count);
        /*const std::chrono::microseconds first_sort_time = sort(base_arr, base_arr + count, asc_comparator,
                                                                   sort_namespace::base);*/
        /*const std::chrono::microseconds second_sort_time = sort(base_arr, base_arr + count, desc_comparator,
                                                                sort_namespace::quick_sort);*/
        /*std::chrono::microseconds third_sort_time = sort(base_arr, base_arr + count, desc_comparator,
                                                         sort_namespace::insert_sort);*/
        print_array(base_arr, count);
    }
    if (1)
    {
        for (int check = count_minimal; check < count; ++check)
        {
            time_check new_result;

            const auto arr_1 = new int [check];
            const auto arr_2 = new int [check];
            const auto arr_3 = new int [check];
            const auto arr_4 = new int [check];

            int counter = 0;
            for (int i = 0; i < check; ++i)
            {
                arr_1[i] = base_arr[i];
                arr_2[i] = base_arr[i];
                arr_3[i] = base_arr[i];
                arr_4[i] = base_arr[i];
                ++counter;
            }

            const std::chrono::microseconds first_sort_time = sort(arr_1, arr_1 + check, asc_comparator,
                                                                   sort_namespace::base);
            const std::chrono::microseconds second_sort_time = sort(arr_2, arr_2 + check, asc_comparator,
                                                                    sort_namespace::quick_sort);
            
            /*const std::chrono::microseconds second_sort_time = quicksort(arr_2, arr_2 + check, asc_comparator);*/
            //print_array(arr_3, check);
            const std::chrono::microseconds third_sort_time = sort(arr_3, arr_3 + check, asc_comparator,
                                                                   sort_namespace::insert_sort);
            //print_array(arr_3, check);
            const std::chrono::microseconds forth_sort_time = fast_sort(arr_4, arr_4 + check, asc_comparator);

            delete[] arr_1;
            delete[] arr_2;
            delete[] arr_3;
            delete[] arr_4;

            new_result.base = first_sort_time;
            new_result.quick = second_sort_time;
            new_result.insert = third_sort_time;
            new_result.fast = forth_sort_time;
            result.push_back(new_result);
        }

        int counter{0};
        for (auto time : result)
        {
            const double base_us = time.base.count();
            const double quick_us = time.quick.count();
            const double insert_us = time.insert.count();
            const double fast_us = time.fast.count();

            std::cout << std::fixed << std::setprecision(6)
                << counter++ << " Element: "
                << base_us << " s and "
                << quick_us << " µs and "
                << insert_us << " µs and "
                << fast_us << " µs\n";
        }
    }


    return 0;
}
