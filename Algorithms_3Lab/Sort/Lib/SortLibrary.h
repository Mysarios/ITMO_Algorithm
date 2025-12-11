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
    SortableType* median(SortableType* a, SortableType* b, SortableType* c, Compare comp)
    {
        if (comp(*b, *a)) std::swap(*a, *b);
        if (comp(*c, *b)) std::swap(*b, *c);
        if (comp(*b, *a)) std::swap(*a, *b);
        return b;
    }

    template <class SortableType, typename Compare>
SortableType* partition(SortableType* first, SortableType* last, const SortableType& pivot, Compare comp)
    {
        if (first >= last - 1) return first;
    
        SortableType* less_searcher = first;
        SortableType* above_searcher = last - 1;

        while (true)
        {
            while (less_searcher < last && comp(*less_searcher, pivot))
            {
                ++less_searcher;
            }

            while (above_searcher >= first && comp(pivot, *above_searcher))
            {
                --above_searcher;
            };

            if (less_searcher >= above_searcher)
            {
                return less_searcher;
            }

            std::swap(*less_searcher, *above_searcher);
            ++less_searcher;
            --above_searcher;
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
            for (size_t i = 0; i < size; ++i)
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

    template <class SortableType, typename Compare>
void quicksort(SortableType* begin, SortableType* end, Compare comp)
{
    if (end - begin <= 1) return;
    
    SortableType* left = begin;
    SortableType* right = end;
    
    while (left < right)
    {
        const size_t size = right - left;
        if (size <= 1) break;
        
        SortableType* mid = left + (size / 2);
        SortableType* pivot_it = median(left, mid, right - 1, comp);
        SortableType pivot = *pivot_it;
        
        SortableType* partition_point = partition(left, right, pivot, comp);
        
        if (partition_point == left || partition_point == right)
        {
            bool all_equal = true;
            for (SortableType* p = left + 1; p < right; ++p)
            {
                if (comp(*left, *p) || comp(*p, *left))
                {
                    all_equal = false;
                    break;
                }
            }
            if (all_equal) break;
            
            std::swap(*left, *mid);
            partition_point = partition(left, right, *left, comp);
        }
        
        if (partition_point - left < right - partition_point)
        {
            quicksort(left, partition_point, comp);
            left = partition_point;
        }
        else
        {
            quicksort(partition_point, right, comp);
            right = partition_point;
        }
    }
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
}

template <class SortableType, typename Compare>
const std::chrono::microseconds sort(SortableType* begin, SortableType* end, Compare comparator,
          const sort_namespace::sort_types sort_type = sort_namespace::base, bool print_time = false)
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
