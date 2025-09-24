#include "../Public/game_info.h"

#include <iostream>
#include <ranges>

float get_value(std::variant<unsigned int, float> v)
{
    return std::visit([]<typename T0>(T0&& arg) -> float
    {
        using t = std::decay_t<T0>;
        if constexpr (std::is_same_v<t, unsigned int>)
        {
            return static_cast<float>(arg);
        }
        else
        {
            return arg;
        }
    }, v);
}

void civilization_info::buy_resource(const resource& buy, const resource& sell, unsigned int count)
{
    //ToDo print what buy
    //ToDo minus sell plus buy
}

void civilization_info::print_all_info()
{
    std::cout << "Resource name:   " << "Resource count:" << std::endl;
    for (const auto& key : resource_map_ | std::views::keys)
    {
        std::cout << key.name << "   " << get_resource_count(key) << std::endl;
    }
}

void civilization_info::print_cost_information(const resource& resource)
{
    const auto it = cost_map_.find(resource);
    if (it == cost_map_.end())
    {
        return;
    }

    std::cout << "Resource name:   " << "Resource count to buy:" << std::endl;
    for (const auto& pair : it->second)
    {
        std::cout << pair.first.name << "   " << pair.second << std::endl;
    }
}

float civilization_info::get_resource_count(const resource& resource_name)
{
    if (const auto it = resource_map_.find(resource_name); it != resource_map_.end())
    {
        return get_value(it->second);
    }
    return 0.f;
}


bool civilization_info::try_to_buy_resources(const resource& want_buy, const resource& want_sell,
                                             const unsigned int count)
{
    const float count_selling_resource = get_resource_count(want_sell);
    if (const float cost_buy_resource = get_resource_cost(want_buy, want_sell); count * cost_buy_resource >
        count_selling_resource)
    {
        //ToDo print error buy
        return false;
    }
    buy_resource(want_buy, want_sell, count);
    return true;
}

float civilization_info::get_resource_cost(const resource& want_buy, const resource& want_sell)
{
    if (const auto it = cost_map_.find(want_buy); it != cost_map_.end())
    {
        if (const auto it_cost = it->second.find(want_sell); it_cost != it->second.end())
        {
            return it_cost->second;
        }
    }
    return FLT_MAX;
}
