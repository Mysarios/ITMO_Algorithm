#include "../Public/game_loop.h"

#include <iostream>


float game_loop::get_cost_multiplier(const resourse resourse)
{
    float result = 1;
    switch (resourse.type)
    {
    case gold:
        result = after_round_random_params_.eat_cost;
        break;
    case food:
        result = after_round_random_params_.food_cost;
        break;
    case warriors:
        result = after_round_random_params_.warriors_cost;
        break;
    case fields:
        result = after_round_random_params_.fields_cost;
        break;
    default: ;
    }
    return result;
}

unsigned int game_loop::get_count_resourse(resourse resourse)
{
    unsigned int count = 0;
    const civilization_info info = info_->main_information;
    switch (resourse.type)
    {
    case gold:
        count = info.gold;
        break;
    case food:
        count = info.food;
        break;
    case warriors:
        count = info.warriors;
        break;
    case fields:
        count = info.fields;
        break;
    case humans:
        count = info.base_humans;
        break;
    default: ;
    }
    return count;
}

bool game_loop::can_buy_resourse(const resourse& getted_by,const resourse& lost_resourse, const unsigned int count)
{
    return get_cost_multiplier(getted_by) * static_cast<float>(count) <= static_cast<float>(
        get_count_resourse(lost_resourse));
}


bool game_loop::try_to_by_resourses(const resourse& want_by, const resourse& want_sell, const unsigned int count)
{
    bool can_buy = can_buy = can_buy_resourse(want_by,want_sell,count);

    if (!can_buy)
    {
        std::cout << "U can't buy: " << want_by.name << " u haven't enough: " << want_sell.name << std::endl;
        std::cout << "U can buy only:" << static_cast<int>(get_count_resourse(want_sell) /
            get_cost_multiplier(want_sell)) << std::endl << std::endl;
    }
    return can_buy;
}

randomize_round_params game_loop::get_random_params()
{
    return randomize_round_params{};
}

void game_loop::after_round_event()
{
    // Disasters
    // Add humans
    ++rounds_;
}


void game_loop::loop()
{
    // while(game)
    // init_rand params
    // User unput
    // Events
    after_round_event();
}
