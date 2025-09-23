#pragma once
#include <iostream>

#include "GameModule/Source/Public/GameModule.h"
#include "GameModule/Source/Public/game_message.h"

int main()
{
    const auto game = new game_module;
    game_message game_messages = game->initialize();
    if(!game_messages.status)
    {
        std::cout<<game_messages.message_text<<"\n";
        return 0;
    }
    
    game_messages = game->start_game();
    if(!game_messages.status || game_messages.status == end_game)
    {
        std::cout<<game_messages.message_text<<"\n";
    }
    return 1;
}
