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
    size_t round_ = 0;
    game_info* info_ = nullptr;
    randomize_round_params after_round_random_params_ = {};
private:
    void first_message_after_game_start(bool new_game) const;
    void before_round_event();
    void after_round_event();

    bool round_event() const;
    
    randomize_round_params get_random_params();
    
public:
    game_loop() = default;
    game_loop(game_info* info_);
    void loop();
};
