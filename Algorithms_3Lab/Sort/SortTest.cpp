#include <algorithm>
#include <complex>
#include <iostream>
#include <valarray>
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

void print_array(long long arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

constexpr int count_minimal = 2;
constexpr int count = 9000;
constexpr int statistic_get = 10000;
constexpr long long rand_limit = 4563748674546;

struct time_check
{
    std::chrono::nanoseconds base;
    std::chrono::nanoseconds quick;
    std::chrono::nanoseconds insert;
    std::chrono::nanoseconds fast;
};


int main(int argc, char** argv)
{
    int result_checks[10000];
    int best_time_checks[10000];
    for (int i = 0; i < 1 /* statistic_get */; ++i)
    {
        int count_to_check = 5;
        if (1)
        {
            ::testing::InitGoogleTest(&argc, argv);
            RUN_ALL_TESTS();
        }

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        std::vector<time_check> result;
        long long base_arr[count];
        for (long long& i : base_arr)
        {
            i = rand() % rand_limit;
        }

        if (1)
        {
            time_check new_result;
            const auto arr = new int [count];

            int counter = 0;
            for (int y = 0; y < count; ++y)
            {
                arr[y] = base_arr[y];
                ++counter;
            }
            std::chrono::nanoseconds minimal_time = fast_sort(arr, arr + count, asc_comparator, 9);
            int minimal_num = 9;
            for (int t = 10; t < 50; ++t)
            {
                const auto arr = new int [count];

                int counter = 0;
                for (int y = 0; y < count; ++y)
                {
                    arr[y] = base_arr[y];
                    ++counter;
                }
                const std::chrono::nanoseconds second_sort_time = fast_sort(arr, arr + count, asc_comparator, t);
                if (second_sort_time < minimal_time)
                {
                    minimal_time = second_sort_time;
                    minimal_num = t;
                }
                new_result.fast = second_sort_time;
                result.push_back(new_result);
            }
            std::cout << " Min count for min time " << i << " = " << minimal_num << std::endl;
            best_time_checks[i] = minimal_num;
            counter = 0;
            for (auto time : result)
            {
                //const double quick_us = time.quick.count() / 1000.;
                //const double insert_us = time.insert.count() / 1000.;
                const double fast_us = time.fast.count() / 1000.;

                std::cout << std::fixed << std::setprecision(1) // 3 знака после запятой достаточно
                    << " Treshold: " << counter++
                    //<< "q= " << quick_us << " µs and " // Используем Unicode µ
                    //<< "i= " << insert_us << " µs and "
                    << "  time= " << fast_us << " µs\n";
            }
        }

        if (0)
        {
            print_array(base_arr, count);
            /*const std::chrono::microseconds first_sort_time = sort(base_arr, base_arr + count, asc_comparator,
                                                                       sort_namespace::base);*/
            sort(base_arr, base_arr + count, desc_comparator,
                 sort_namespace::quick_sort);
            /*std::chrono::microseconds third_sort_time = sort(base_arr, base_arr + count, desc_comparator,
                                                             sort_namespace::insert_sort);*/
            print_array(base_arr, count);
        }

        if (0)
        {
            int current_count = 0;
            int index = 0;
            for (int check = count_minimal; check < count; ++check)
            {
                time_check new_result;

                const auto arr_2 = new int [check];
                const auto arr_3 = new int [check];
                const auto arr_4 = new int [check];

                int counter = 0;
                for (int i = 0; i < check; ++i)
                {
                    arr_2[i] = base_arr[i];
                    arr_3[i] = base_arr[i];
                    arr_4[i] = base_arr[i];
                    ++counter;
                }

                const std::chrono::nanoseconds second_sort_time = fast_sort(arr_2, arr_2 + check, asc_comparator);
                const std::chrono::nanoseconds third_sort_time = only_insert_sort(arr_3, arr_3 + check, asc_comparator);
                const std::chrono::nanoseconds forth_sort_time = only_quick_sort(arr_4, arr_4 + check, asc_comparator);

                delete[] arr_2;
                delete[] arr_3;
                delete[] arr_4;

                new_result.quick = forth_sort_time;
                new_result.insert = third_sort_time;
                new_result.fast = second_sort_time;
                if (index == 0 && forth_sort_time < third_sort_time)
                {
                    if (++current_count == 5)
                    {
                        index = check;
                    }
                }
                result.push_back(new_result);
            }

            int counter{0};
            for (auto time : result)
            {
                const double quick_us = time.quick.count() / 1000.;
                const double insert_us = time.insert.count() / 1000.;
                const double fast_us = time.fast.count() / 1000.;

                std::cout << std::fixed << std::setprecision(1) // 3 знака после запятой достаточно
                    << counter++ << " Element: "
                    << "q= " << quick_us << " µs and " // Используем Unicode µ
                    << "i= " << insert_us << " µs and "
                    << "f= " << fast_us << " µs\n";
            }
            result_checks[i] = index;
        }
    }
    if (/* get statistic*/ 0)
    {
        int result_count = 0;
        for (int i = 0; i < 1000; ++i)
        {
            result_count += result_checks[i];
        }
        std::cout << std::endl << std::endl << result_count / 1000 << std::endl;
    }
    if (/* get end time*/ 1)
    {
        int result_count = 0;
        for (int i = 0; i < 1000; ++i)
        {
            result_count += best_time_checks[i];
        }
        std::cout << std::endl << std::endl << result_count / 1000 << std::endl;
    }


    return 0;
}
