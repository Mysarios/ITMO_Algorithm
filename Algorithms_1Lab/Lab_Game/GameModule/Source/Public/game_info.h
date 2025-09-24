#pragma once

#include <map>
#include <unordered_map>
#include <variant>

#include "game_message.h"
#include "game_resourses.h"


struct civilization_info
{
private:
    std::unordered_map<resource, std::variant<unsigned int, float>> resource_map_;
    std::unordered_map<resource, std::unordered_map<resource, float>> cost_map_;

public:
    void buy_resource(const resource& buy,const resource& sell,unsigned int count);
    void print_all_info();
    void print_cost_information(const resource& resource);
    
    bool try_to_buy_resources(const resource& want_buy, const resource& want_sell, unsigned int count);
    
    float get_resource_count(const resource& resource_name);
    float get_resource_cost(const resource& want_buy, const resource& want_sell);
};

class game_info
{
public:
    civilization_info main_information;

    static game_message try_load_game(game_info* loaded_game) { return SUCCESS_MESSAGE; }
    static game_message create_new_game(game_info* created_game) { return SUCCESS_MESSAGE; }
};
