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
        create_message = game_info_->try_load_game_or_create(/* tik*/);
        break;
    case 2:
        create_message = game_info_->try_load_game_or_create();
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
    //game_config_ = new game_config();
    game_info_ = new game_info();
    game_loop_ = new game_loop(game_info_);
}

/*game_message game_module::initialize() const
{
    //std::map<std::string,std::map<std::string,int>> config;
    /*if (const game_message load_config_message = game_config_->load_data_from_config(config); !load_config_message.success)
    {
        return {error_read_file, "Can't load config, check file", false};
    }#1#

    return SUCCESS_MESSAGE;
}*/

game_message game_module::start_game()
{
    /*if (const game_message init = initialize(); !init.success)
    {
        return init;
    }*/
    
    const auto create_message = start_dialogue();
    //ToDo - init game
    /*switch(){
    case 1 - try_load_game
    case 2 - create_new_game
    }

    game_loop create and init.
    game_loop - start game loop()
    */

    return create_message;
}
