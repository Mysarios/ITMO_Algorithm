#include "../Public/GameModule.h"
#include <iostream>

game_message game_module::start_dialogue()
{
    std::cout << "Print 1 to create new game\nPrint 2 to try load game\nPrint 3 to close game\nPrint: ";
    int input{0};
    std::cin >> input;

    auto create_message = SUCCESS_MESSAGE;
    switch (input)
    {
    case 1:
        // create new input by switch config
        create_message = game_info_->try_load_game_or_create(); // load
        break;
    case 2:
        create_message = game_info_->try_load_game_or_create(config::save_part); // create
        break;
    case 3:
        return {end_game, "\nGame closed", true}; //end
    default:
        std::cout << "\nEnter correct number!\n\n";
        return start_dialogue(); // try to start again
    }
    game_loop_ = new game_loop(game_info_);
    return create_message;
}

game_module::game_module(): game_loop_(nullptr), game_info_(nullptr)
{
    game_info_ = new game_info();
}

game_module::~game_module()
{
    delete game_info_;
    delete game_loop_;
}


game_message game_module::start_game()
{
    if (const auto create_message = start_dialogue(); !create_message.success || create_message.status == end_game)
    {
        return create_message;
    } // load phasre

    game_loop_->loop();


    return SUCCESS_MESSAGE;
}
