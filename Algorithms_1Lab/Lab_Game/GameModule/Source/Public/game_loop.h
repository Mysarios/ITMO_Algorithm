#pragma once
#include <string>

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
    game_info* info_;
    randomize_round_params after_round_random_params_;
    size_t rounds_;
    
    bool try_to_by_resourses(const resourse& want_by, const resourse& want_sell, unsigned int count);
    randomize_round_params get_random_params();
    void after_round_event();
    float get_cost_multiplier(resourse resourse);
    bool can_buy_resourse(const resourse& getted_by, const resourse& lost_resourse,unsigned int count);
    unsigned int get_count_resourse(resourse resourse);
public:
    explicit game_loop(game_info* info_initialize) : info_(info_initialize), rounds_(0){}
    
    void loop();
};
