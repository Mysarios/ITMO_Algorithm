#include <algorithm>
#include <iostream>

#include "Lib/SortLibrary.h"
#include "vector"

int main()
{
    int arr[] = {3, 1, 4, 1, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    auto asc_comparator = [](const int& a, const int& b) -> bool
    {
        return a > b;
    };
    auto desc_comparator = [](const int& a, const int& b) -> bool
    {
        return a < b;
    };

    base_sort(arr, arr + size, asc_comparator);
    for (const int i : arr)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    sort(arr, arr + size, desc_comparator, sort_namespace::base);
    for (int i : arr)
    {
        std::cout << i << " ";
    }

    return 0;
}
