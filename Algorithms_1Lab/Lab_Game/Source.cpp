#pragma once
#include <iostream>

#include "GameModule/Source/Public/GameModule.h"
#include "GameModule/Source/Public/game_message.h"

int main()
{
    const auto game = new game_module;

    if(game_message game_messages = game->start_game(); !game_messages.status || game_messages.status == end_game)
    {
        std::cout<<game_messages.message_text<<"\n";
    }
    return 1;
}
