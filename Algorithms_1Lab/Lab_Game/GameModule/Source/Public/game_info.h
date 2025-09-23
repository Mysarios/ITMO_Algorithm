#pragma once
#include "game_message.h"
struct civilization_info
{
    unsigned int gold;
    unsigned int food;

    unsigned int base_humans;
    unsigned int warriors;
    unsigned int fields;
    
    float happiness;
    float tallage_percent;
};


class game_info
{
public:
    civilization_info main_information;
    
    static game_message try_load_game(game_info* loaded_game) { return SUCCESS_MESSAGE; }
    static game_message create_new_game(game_info* created_game) { return SUCCESS_MESSAGE; }
};
