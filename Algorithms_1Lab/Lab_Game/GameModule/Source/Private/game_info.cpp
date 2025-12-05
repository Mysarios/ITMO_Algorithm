#include "../Public/game_info.h"

#include <iomanip>
#include <iostream>
#include <ranges>
#include <set>

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
                                     const resource_cost_map&
                                     base_cost_config)
{
    for (auto& [name, value] : resource_config)
    {
        resource_map_.emplace(resource(name), value);
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


void civilization_info::buy_resource(const resource& buy, const resource& sell, const unsigned int count)
{
    std::cout << "\n=U wanna buy: " << count << " " << buy.name << " by: " << sell.name << "!    ";
    if (try_to_buy_resources(buy, sell, count))
    {
        std::cout << "and U do this! Now U have: \n";
        this->print_all_info();
    }
    else
    {
        std::cout << "but U can't do this =) \n";
    }
}

void civilization_info::print_all_info()
{
    std::cout << "\nAt the moment, you have:\n";
    std::cout << "Resource name:   " << " Resource count:" << '\n';
    size_t line_index = 1;
    for (const auto& key : resource_map_ | std::views::keys)
    {
        std::cout << line_index++ << ") " << std::setw(14) << key.name << "   " << std::setw(13) <<
            get_resource_count(key) << '\n';
    }
    std::cout << '\n';
}

resource_index_table civilization_info::print_cost_information(
    const resource& resource_to_sell)
{
    resource_index_table result;
    const auto it = cost_map_.find(resource_to_sell);
    if (it == cost_map_.end())
    {
        return {};
    }

    std::cout << '\n' << "U need spend: " << resource_to_sell.name << " to buy next resources!\n";
    std::cout << "Resource name:   " << "Resource count to buy:" << '\n';
    int index_line = 1;
    for (const auto& pair : it->second)
    {
        result.emplace_back(index_line, pair.first);
        std::cout << index_line++ << ")" << std::setw(13) << pair.first.name << "   " << std::setw(23) << pair.second <<
            '\n';
    }
    return result;
}

resource_index_table civilization_info::print_cost_information_to_buy(
    const resource& resource_to_buy)
{
    resource_index_table result;

    std::cout << '\n' << "=U wanna buy: " << resource_to_buy.name << " It's resources, which u can sell:" "\n";
    std::cout << "Resource name:     " << "Resource count to buy:" << '\n';
    size_t index_line = 1;
    for (const auto& cost : cost_map_)
    {
        if (cost.second.contains(resource_to_buy))
        {
            const auto& cost_value = cost.second.find(resource_to_buy);
            result.emplace_back(index_line++, cost.first);
            std::cout << index_line - 1 << ")" << std::setw(13) << cost.first.name << "   " << std::setw(23) <<
                std::to_string(round(cost_value->second)) + " by one " + resource_to_buy.name << '\n';
        }
    }

    return result;
}

resource_index_table civilization_info::print_buy_information()
{
    resource_index_table result;
    std::set<std::string> unique_resources;
    size_t cost_index = 1;
    std::cout << "--------------------------------" << '\n';
    std::cout << "=All Resource which u can buy:   \n";
    for (const auto& key : cost_map_ | std::views::values)
    {
        for (const auto& map_key : key | std::views::keys)
        {
            if (!unique_resources.contains(map_key.name))
            {
                unique_resources.emplace(map_key.name);
                result.emplace_back(cost_index++, map_key.name);
            }
        }
    }
    for (const auto& resource_element : result)
    {
        std::cout << resource_element.first << ")" << std::setw(13) << resource_element.second.name << '\n';
    }
    return result;
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
    if (!resource_map_.contains(want_buy) || !resource_map_.contains(want_sell))
    {
        return false;
    }

    const float count_selling_resource = get_resource_count(want_sell);
    const float cost_buy_resource = get_resource_cost(want_buy, want_sell);

    const float needed_resource = count / cost_buy_resource;
    if (needed_resource > count_selling_resource)
    {
        return false;
    }

    const auto resource_to_sell = resource_map_.find(want_sell);
    const auto resource_to_buy = resource_map_.find(want_buy);

    const std::variant<unsigned int, float>& resource_to_buy_ref = resource_to_buy->second;
    const std::variant<unsigned int, float>& resource_to_sell_ref = resource_to_sell->second;
    
    bool is_int_variant = true;
    if (!std::holds_alternative<unsigned int>(resource_to_buy->second) || !std::holds_alternative<unsigned int>(
        resource_to_sell->second))
    {
        is_int_variant = false;
    }
    
    if(is_int_variant)
    {
        unsigned int& resource_count_to_buy = std::get<unsigned int>(resource_to_buy->second);
        unsigned int& resource_count_to_sell = std::get<unsigned int>(resource_to_sell->second);

        resource_count_to_buy += count;
        resource_count_to_sell -= static_cast<unsigned int>(count / cost_buy_resource);
        return true;
    }

    float& resource_count_to_buy = std::get<float>(resource_to_buy->second);
    float& resource_count_to_sell = std::get<float>(resource_to_sell->second);
    resource_count_to_buy += count;
    resource_count_to_sell -= count / cost_buy_resource;
    return true;
}

float civilization_info::get_resource_cost(const resource& want_buy, const resource& want_sell)
{
    if (const auto it = cost_map_.find(want_sell); it != cost_map_.end())
    {
        if (const auto it_cost = it->second.find(want_buy); it_cost != it->second.end())
        {
            return it_cost->second;
        }
    }
    return FLT_MAX;
}

std::vector<resource> civilization_info::get_saleable_resources()
{
    std::vector<resource> result;
    return result;
}

int civilization_info::get_humans_count() const
{
    if (const unsigned int* humans_count = std::get_if<unsigned int>(&resource_map_.find(resource("humans"))->second);
        humans_count != nullptr)
    {
        return *humans_count;
    }
    return 0;
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

    resource_cost_map cost_config;
    for (const auto [name,cost] : base_cost_info_config)
    {
        std::vector<std::string> names = game_config::split_str(name, "To");
        if (auto it = cost_config.find(names[0]); it != cost_config.end())
        {
            it->second.emplace(names[1], cost);
        }
        else
        {
            std::unordered_map<resource, float> buf;
            buf.emplace(names[1], cost);
            cost_config.emplace(names[0], buf);
        }
    }
    std::cout << std::endl;
    switch (config_part.length())
    {
    case 0:
        std::cout <<
            "=Hello!\nToday you will play as the ruler of Ancient Egypt!\nTry to lead your nation to greatness, and do not be discouraged by the difficulties along the way!\n\n";
        std::cout <<
            "=Remember that the poorer and malnourished your population is, the less food you produce.\nIf famine has begun, it is almost impossible to stop.\nAlso remember that the more abundant your resources are, the more demanding your citizens are! \nAnd don't forget about your enemies. They are always nearby, eager to seize your wealth!\nYou have fields for food, food reserves, gold, wars, and tax levels to collect money from your subjects. Remember that the mood of your subjects reflects on the success of your country.\nTry to maintain a balance in your government, as well as protect your country.\nGood reign to you!\n\n";
        break;
    default:
        break;
    }
    max_rounds_ = static_cast<size_t>(game_info_config->second.find("maxRounds")->second);
    main_information = civilization_info(civil_info_config->second, cost_config);

    main_information.print_all_info();

    return SUCCESS_MESSAGE;
}

bool game_info::game_lose() const
{
    if (!main_information.get_humans_count())
    {
        return false;
    }
    return true;
}

void game_info::start_dialogue(bool is_new_game)
{
    std::cout << std::endl;
    if (is_new_game)
    {
        std::cout <<
            "=Hello!\nToday you will play as the ruler of Ancient Egypt!\nTry to lead your nation to greatness, and do not be discouraged by the difficulties along the way!\n\n";
        std::cout <<
            "=Remember that the poorer and malnourished your population is, the less food you produce.\nIf famine has begun, it is almost impossible to stop.\nAlso remember that the more abundant your resources are, the more demanding your citizens are! \nAnd don't forget about your enemies. They are always nearby, eager to seize your wealth!\nYou have fields for food, food reserves, gold, wars, and tax levels to collect money from your subjects. Remember that the mood of your subjects reflects on the success of your country.\nTry to maintain a balance in your government, as well as protect your country.\nGood reign to you!\n\n";
    }
    else
    {
        std::cout << "Today, u continue game! And win it!" << std::endl << std::endl;
    }
}

bool game_info::read_config_and_init_game(const config_type& config)
{
    const auto game_info_config = config.find("GameInfo");
    const auto civil_info_config = config.find("CivilInfo");
    const auto random_info_config = config.find("RandomInfo");
    std::map<std::string, float> base_cost_info_config = config.find("BaseCostInfo")->second;

    resource_cost_map cost_config;
    for (const auto& [name,cost] : base_cost_info_config)
    {
        std::vector<std::string> names = game_config::split_str(name, "To");
        if (auto it = cost_config.find(names[0]); it != cost_config.end())
        {
            it->second.emplace(names[1], cost);
        }
        else
        {
            std::unordered_map<resource, float> buf;
            buf.emplace(names[1], cost);
            cost_config.emplace(names[0], buf);
        }
    }
    max_rounds_ = game_info_config->second.find("maxRounds")->second;
    main_information = civilization_info(civil_info_config->second, cost_config);
    main_information.print_all_info();
    return true;
}
