#pragma once

#include <utility>

namespace sort_namespace
{
    enum sort_types
    {
        none, base
    };
}

namespace
{
    
    template <class SortableType, typename Compare>
    void base_sort(SortableType* begin, SortableType* end, Compare comparator)
    {
        if (begin >= end) return;  // Пустой или некорректный диапазон
        size_t size = static_cast<size_t>(end - begin);
        bool need_resort;
        do
        {
            need_resort = false;  // Сбрасываем перед каждым проходом
            for (size_t i = 0; i < size - 1; ++i)
            {
                if (comparator(*(begin + i), *(begin + i + 1)))
                {
                    need_resort = true;
                    std::swap(*(begin + i), *(begin + i + 1));
                }
            }
        } while (need_resort);
    }

}

template <class SortableType, typename Compare>
void sort(SortableType* begin, SortableType* end, Compare comparator, sort_namespace::sort_types sort_type = sort_namespace::base)
{
    switch (sort_type)
    {
    case sort_namespace::none:
            break;
    case sort_namespace::base:
        base_sort(begin, end, comparator);
        break;
    default:
        base_sort(begin, end, comparator);
        break;
    }
}
