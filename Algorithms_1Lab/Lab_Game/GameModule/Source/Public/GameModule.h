#pragma once
#include "game_config.h"
#include "game_info.h"
#include "game_loop.h"
#include "game_message.h"

class game_module
{
private:
    game_config game_config_;
    /**
     * Main loop in this game
     */
    game_loop* game_loop_;
    game_info* game_info_;
    game_message start_dialogue();
public:
    game_module();
    game_message initialize();
    game_message start_game();
protected:
};


