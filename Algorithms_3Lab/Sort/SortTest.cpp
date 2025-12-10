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
constexpr int count = 50;

int main()
{
    
    int base_arr[count];
    for (int& i : base_arr)
    {
        i = rand() % 50; 
    }
    
    int arr_1[count];
    int arr_2[count];
    int arr_3[count];

    int counter =0;
    for (int& i : base_arr)
    {
        arr_1[counter] = i;
        arr_2[counter] = i;
        arr_3[counter] = i;
        ++counter;
    }

    std::cout << "First" << " ";
    print_array(arr_1,std::size(arr_1));
    std::chrono::microseconds first_sort_time = sort(std::begin(arr_1), std::end(arr_1)-1, asc_comparator, sort_namespace::base,true);
    print_array(arr_1,std::size(arr_1));

    std::cout << "Second" << " ";
    print_array(arr_2,std::size(arr_2));
    std::chrono::microseconds second_sort_time = sort(std::begin(arr_2), std::end(arr_2), asc_comparator, sort_namespace::quick_sort,true);
    print_array(arr_2,std::size(arr_2));

    std::cout << "Third" << " ";
    print_array(arr_3,std::size(arr_3));
    std::chrono::microseconds third_sort_time = sort(std::begin(arr_3), std::end(arr_3), asc_comparator, sort_namespace::quick_sort,true);
    print_array(arr_3,std::size(arr_3));


    return 0;
}
