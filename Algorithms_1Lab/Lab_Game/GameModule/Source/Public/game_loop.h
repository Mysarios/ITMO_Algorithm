#pragma once
#include <string>

#include "game_config.h"
#include "game_info.h"
#include "game_resourses.h"

struct randomize_round_params
{
    //food
    float food_disaster_percent;
    float food_eat_multiplier;
    //human
    float human_disaster_percent;
    //gold
    float gold_losted_percent;
    float gold_getted_by_humans;
    //all
    float disaster_chance;

    //cost
    float eat_cost;
    float food_cost;
    float warriors_cost;
    float fields_cost;
    
};
class game_loop
{
private:
    size_t round_;

    //game_config* config_;
    game_info* info_;
    randomize_round_params after_round_random_params_;
private:
    void after_round_event();
    randomize_round_params get_random_params();
    
public:
    explicit game_loop(game_info* info_initialize) : round_(0), info_(info_initialize), after_round_random_params_()
    {
    }

    void loop();
};
