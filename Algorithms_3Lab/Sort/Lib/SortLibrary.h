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
    /*template <class SortableType, typename Compare>
    int median(SortableType* arr, int a, int b, int c, Compare comp)
    {
        if (comp(arr[b], arr[a]))
        {
            if (comp(arr[c], arr[a]))
            {
                return comp(arr[c], arr[b]) ? b : c;
            }
            return a;
        }
        if (comp(arr[c], arr[b]))
        {
            return comp(arr[c], arr[a]) ? a : c;
        }
        return b;
    }*/  //Вынес внутрь партишиона
    template <class SortableType, typename Compare>
    int partition_hoare(SortableType* arr, int l, int r, Compare comp)
    {
        //Поиск медианы встроена для исключения вызова
        int m = l + (r - l) / 2;
    
        if (comp(arr[m], arr[l])) std::swap(arr[l], arr[m]);
        if (comp(arr[r], arr[l])) std::swap(arr[l], arr[r]);
        if (comp(arr[r], arr[m])) std::swap(arr[m], arr[r]);
    
        const SortableType& pivot = arr[m];
        std::swap(arr[m], arr[(l + r) / 2]); // медиана в серидину

        int i = l - 1;
        int j = r + 1;
        while (true)
        {
            do { i++; }
            while (comp(arr[i], pivot));
            do { j--; }
            while (comp(pivot, arr[j]));

            if (i >= j) return j;
            std::swap(arr[i], arr[j]);
        }
    }
    
    template <class SortableType, typename Compare>
    void insertion_sort(SortableType* begin, SortableType* end, Compare comp)
    //Требование 2 - Инсерт со сдвигом
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
    
    constexpr int INSERTION_THRESHOLD = 32;
    template <class SortableType, typename Compare>
    void quicksort_itmo_impl(SortableType* arr, int l, int r, Compare comp, int treshold = INSERTION_THRESHOLD)
    {
        
        while (r - l > treshold) // Требование 1 - рекурсивно меньшую часть, оставшуюся иттеративно
        {
            int i = partition_hoare(arr, l, r, comp); // Требование 3 - партишн Хоара 

            if (i - l < r - i)
            {
                quicksort_itmo_impl(arr, l, i, comp,treshold);
                l = i + 1;
            }
            else
            {
                quicksort_itmo_impl(arr, i + 1, r, comp,treshold);
                r = i;
            }
        }
        if (l < r)
        {
            insertion_sort(arr + l, arr + r + 1, comp);
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
void quicksort(SortableType* begin, SortableType* end, Compare comp)
{
    if (begin >= end) return;

    int l = 0;
    int r = static_cast<int>(end - begin) - 1;
    quicksort_itmo_impl(begin, l, r, comp);
}

template <class SortableType, typename Compare>
void sort(SortableType* begin, SortableType* end, Compare comparator,
          const sort_namespace::sort_types sort_type = sort_namespace::base,
          const bool print_time = false)
{
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
}

constexpr int change_size = 20;

template <class SortableType, typename Compare>
const std::chrono::nanoseconds fast_sort(SortableType* begin, SortableType* end, Compare comparator, int treshold = change_size )
{
    if (begin >= end) return std::chrono::nanoseconds::zero();
    int l = 0;
    int r = static_cast<int>(end - begin) - 1;

    
    if(end - begin <= treshold)
    {
        auto end_time = std::chrono::steady_clock::now();
        const auto start = std::chrono::steady_clock::now();
        insertion_sort(begin, end, comparator);
        end_time = std::chrono::steady_clock::now();
        
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start);
    }else
    {
        auto end_time = std::chrono::steady_clock::now();
        const auto start = std::chrono::steady_clock::now();
        quicksort_itmo_impl(begin, l, r, comparator,treshold);
        end_time = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start);
    }
    
}

template <class SortableType, typename Compare>
const std::chrono::nanoseconds only_quick_sort(SortableType* begin, SortableType* end, Compare comparator)
{
    auto end_time = std::chrono::steady_clock::now();
    if (begin >= end) return std::chrono::nanoseconds::zero();
    int l = 0;
    int r = static_cast<int>(end - begin) - 1;
    const auto start = std::chrono::steady_clock::now();
    quicksort_itmo_impl(begin, l, r, comparator);
    end_time = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start) ;
}

template <class SortableType, typename Compare>
const std::chrono::nanoseconds  only_insert_sort(SortableType* begin, SortableType* end, Compare comparator)
{
    auto end_time = std::chrono::steady_clock::now();
    if (begin >= end) return std::chrono::nanoseconds::zero();
    
    const auto start = std::chrono::steady_clock::now();
    insertion_sort(begin, end, comparator);
    end_time = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start);
}
