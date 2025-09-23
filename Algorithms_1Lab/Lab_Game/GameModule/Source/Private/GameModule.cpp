#include "../Public/GameModule.h"
#include <iostream>

game_message game_module::start_dialogue()
{
    std::cout << "Print 1 to try load game, 2 to create new game and 3 to close game" << '\n';
    int input{0};
    std::cin >> input;
    auto create_message = SUCCESS_MESSAGE;
    switch (input)
    {
    case 1:
        create_message = game_info::try_load_game(game_info_);
        break;
    case 2:
        game_info::create_new_game(game_info_);
        break;
    case 3:
        return {end_game,"Game closed",true};
    default:
        std::cout <<"Enter correct number! \n";
        return start_dialogue();
    }
    return create_message;
}

game_module::game_module(): game_loop_(nullptr), game_info_(nullptr)
{
}

game_message game_module::initialize()
{
    const game_message load_config = game_config_.load_data_from_config();
    if (!load_config.success)
    {
        return {error_read_file, "Can't load config, check file", false};
    }

    return SUCCESS_MESSAGE;
}

game_message game_module::start_game()
{
    const auto create_message = start_dialogue();
    return create_message;
}
