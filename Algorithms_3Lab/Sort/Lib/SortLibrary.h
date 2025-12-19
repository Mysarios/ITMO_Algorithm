#pragma once

#include <algorithm>
#include <utility>
#include <chrono>
#include <iostream>

namespace sort_namespace
{
    enum sort_types
    {
        none, base, quick_sort, insert_sort
    };
}

namespace
{
    template <class SortableType, typename Compare>
    int median(SortableType* arr, int idx_a, int idx_b, int idx_c, Compare comp)
    {
        const SortableType& a = arr[idx_a];
        const SortableType& b = arr[idx_b];
        const SortableType& c = arr[idx_c];

        if (comp(a, b))
        {
            if (comp(b, c)) return idx_b;
            if (comp(a, c)) return idx_c;
            return idx_a;
        }
        else
        {
            if (comp(a, c)) return idx_a;
            if (comp(b, c)) return idx_c;
            return idx_b;
        }
    }

    template <class SortableType, typename Compare>
    int partition_hoare(SortableType* arr, int l, int r, Compare comp)
    {
        SortableType pivot = arr[(l + r) / 2];
        int i = l - 1;
        int j = r + 1;

        while (true)
        {
            do
            {
                ++i;
            }
            while (comp(arr[i], pivot));

            do
            {
                --j;
            }
            while (comp(pivot, arr[j]));

            if (i >= j)
                return j;

            std::swap(arr[i], arr[j]);
        }
    }

    template <class SortableType, typename Compare>
    void quicksort_itmo_impl(SortableType* arr, int l, int r, Compare comp)
    {
        if (l >= r) return;
        
        int median_idx = median(arr, l, (l + r) / 2, r, comp);
        std::swap(arr[median_idx], arr[(l + r) / 2]);

        int i = partition_hoare(arr, l, r, comp);
        //рекурсимся
        quicksort_itmo_impl(arr, l, i, comp);
        quicksort_itmo_impl(arr, i + 1, r, comp);
    }

    template <class SortableType, typename Compare>
    void insertion_sort(SortableType* begin, SortableType* end, Compare comp)
    {
        if (begin >= end) return;
        for (SortableType* i = begin + 1; i < end; ++i)
        {
            auto key = std::move(*i);
            SortableType* j = i;
            while (j > begin && comp(key, *(j - 1)))
            {
                *j = std::move(*(j - 1));
                --j;
            }
            *j = std::move(key);
        }
    }

    template <class SortableType, typename Compare>
    void base_sort(SortableType* begin, SortableType* end, Compare comparator)
    {
        if (begin >= end) return;
        const size_t size = static_cast<size_t>(end - begin);
        bool need_resort;
        do
        {
            need_resort = false;
            for (size_t i = 0; i < size - 1; ++i)
            {
                if (comparator(*(begin + i + 1), *(begin + i)))
                {
                    need_resort = true;
                    std::swap(*(begin + i), *(begin + i + 1));
                }
            }
        }
        while (need_resort);
    }
}

template <class SortableType, typename Compare>
    const std::chrono::microseconds quicksort(SortableType* begin, SortableType* end, Compare comp)
{
    if (begin >= end) return std::chrono::microseconds::zero();

    //prepare
    int l = 0;
    int r = static_cast<int>(end - begin) - 1;
    auto start = std::chrono::high_resolution_clock::now();
    quicksort_itmo_impl(begin, l, r, comp);
    const auto end_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start);
}

template <class SortableType, typename Compare>
const std::chrono::microseconds sort(SortableType* begin, SortableType* end, Compare comparator,
                                     const sort_namespace::sort_types sort_type = sort_namespace::base,
                                     bool print_time = false)
{
    auto start = std::chrono::high_resolution_clock::now();
    switch (sort_type)
    {
    case sort_namespace::none:
        break;
    case sort_namespace::base:
        base_sort(begin, end, comparator);
        break;
    case sort_namespace::quick_sort:
        quicksort(begin, end, comparator);
        break;
    case sort_namespace::insert_sort:
        insertion_sort(begin, end, comparator);
        break;
    default:
        base_sort(begin, end, comparator);
        break;
    }
    const auto end_time = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start);

    if (print_time)
    {
        std::cout << "Sorting time: " << duration.count() << " microseconds" << std::endl;
    }
    return duration;
}

constexpr int change_size = 90;

template <class SortableType, typename Compare>
const std::chrono::microseconds fast_sort(SortableType* begin, SortableType* end, Compare comparator)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (end - begin <= change_size)
    {
        insertion_sort(begin, end, comparator);
    }
    else
    {
        quicksort(begin, end, comparator);
    }
    const auto end_time = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start);
    return duration;
}
