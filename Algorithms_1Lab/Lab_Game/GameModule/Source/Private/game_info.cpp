#include "../Public/game_info.h"

#include <iomanip>
#include <iostream>
#include <ranges>

#include "../Public/game_config.h"

namespace
{
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
}


civilization_info::civilization_info(const std::map<std::string, float>& resource_config,
                                     const std::map<std::string, std::unordered_map<std::string, float>>&
                                     base_cost_config)
{
    for (auto& [name, value] : resource_config)
    {
        std::variant<unsigned int, float> new_val;
        new_val.emplace<float>(value);
        resource_map_.emplace(resource(name), new_val);
    }
    for (auto& [name, value] : base_cost_config)
    {
        std::unordered_map<resource, float> cost_map;
        for (auto& [name_value, value_cost] : value)
        {
            cost_map.emplace(resource(name_value), value_cost);
        }
        base_cost_map_.emplace(resource(name), cost_map);
    }
    cost_map_ = base_cost_map_;
}

void civilization_info::buy_resource(const resource& buy, const resource& sell, unsigned int count)
{
    //ToDo print what buy
    //ToDo minus sell plus buy
}

void civilization_info::print_all_info()
{
    std::cout << "\nAt the moment, you have:\n";
    std::cout << "Resource name:   " << " Resource count:" << std::endl;
    size_t line_index = 1;
    for (const auto& key : resource_map_ | std::views::keys)
    {
        std::cout << line_index++ << ") " << std::setw(14) << key.name << "   " << std::setw(13) <<
            get_resource_count(key) << std::endl;
    }
}

void civilization_info::print_cost_information(const resource& resource)
{
    const auto it = cost_map_.find(resource);
    if (it == cost_map_.end())
    {
        return;
    }

    std::cout << std::endl << "U need spend: " << resource.name << "to buy next resources!\n";
    std::cout << "Resource name:   " << "Resource count to buy:" << std::endl;
    int index_line = 1;
    for (const auto& pair : it->second)
    {
        std::cout << index_line++ << ")" << std::setw(13) << pair.first.name << "   " << std::setw(23) << pair.second <<
            std::endl;
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

game_message game_info::try_load_game_or_create(const std::string& config_part)
{
    std::map<std::string, std::map<std::string, float>> config;
    if (const game_message load_message = game_config::load_data_from_config(config, config_part); !load_message.
        success)
    {
        return load_message;
    }
    const auto game_info_config = config.find("GameInfo");
    const auto civil_info_config = config.find("CivilInfo");
    const auto random_info_config = config.find("RandomInfo");
    std::map<std::string, float> base_cost_info_config = config.find("BaseCostInfo")->second;

    std::map<std::string, std::unordered_map<std::string, float>> cost_config;
    for (const auto [name,cost] : base_cost_info_config)
    {
        std::vector<std::string> names = game_config::split_str(name, "To");
        if (auto it = cost_config.find(names[0]); it != cost_config.end())
        {
            it->second.emplace(names[1], cost);
        }
        else
        {
            std::unordered_map<std::string, float> buf;
            buf.emplace(names[1], cost);
            cost_config.emplace(names[0], buf);
        }
    }
    std::cout << std::endl << std::endl;
    switch (config_part.length())
    {
    case 0:
        std::cout <<
            "Hello!\nToday you will play as the ruler of Ancient Egypt!\nTry to lead your nation to greatness, and do not be discouraged by the difficulties along the way!\n\n";
        std::cout <<
            "Remember that the poorer and malnourished your population is, the less food you produce.\nIf famine has begun, it is almost impossible to stop.\nAlso remember that the more abundant your resources are, the more demanding your citizens are! \nAnd don't forget about your enemies. They are always nearby, eager to seize your wealth!\nYou have fields for food, food reserves, gold, wars, and tax levels to collect money from your subjects. Remember that the mood of your subjects reflects on the success of your country.\nTry to maintain a balance in your government, as well as protect your country.\nGood reign to you!\n\n";
        break;
    default:
        break;
    }
    max_rounds_ = game_info_config->second.find("maxRounds")->second;
    main_information = civilization_info(civil_info_config->second, cost_config);

    main_information.print_all_info();
    main_information.print_cost_information(resource("gold"));
    main_information.print_cost_information(resource("food"));
    main_information.print_cost_information(resource("humans"));
    main_information.print_cost_information(resource("fields"));

    return SUCCESS_MESSAGE;
}
