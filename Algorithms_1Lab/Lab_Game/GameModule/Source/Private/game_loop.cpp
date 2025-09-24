#include "../Public/game_loop.h"

#include <iostream>


randomize_round_params game_loop::get_random_params()
{
    return randomize_round_params{};
}

void game_loop::after_round_event()
{
    // Disasters
    // Add humans
    ++rounds_;
}

//ToDo
bool buy_dialogue(game_info* info)
{
    info->main_information.print_all_info();
    std::cout<< std::endl << "Enter ..." << std::endl;

    int input_key;
    std::cin >> input_key;
    switch (input_key)
    {
        case 1:
            std::cout << "Enter ..." << std::endl;
            return true;
        case 2:
            std::cout << "Enter ..." << std::endl;
            return true;
        case 3:
            std::cout << "Enter ..." << std::endl;
            return false;
        default:
            std::cout << "Enter correct unput! ..." << std::endl;
            return true;
    }
}

//ToDo
bool info_dialogue()
{
}

bool input_dialogue(game_info* info, const int input_key)
{
    switch (input_key)
    {
        case 1:
            std::cout << "Enter ..." << std::endl;
            buy_dialogue(info);
            return true;
        case 2:
            std::cout << "Enter ..." << std::endl;
            info_dialogue();
            return true;
        case 3:
            std::cout << "End round ..." << std::endl;
            return false;
        default:
            std::cout << "Enter correct input! ..." << std::endl;
            return true;
    }
}

void game_loop::loop()
{
    while (rounds_ <= config_->get_max_rounds())
    {
        get_random_params();

        bool round_play = true;
        while (round_play)
        {
            std::cout << "Enter ..." << std::endl;

            int input;
            std::cin >> input;
            round_play = input_dialogue(info_, input);
        }

        after_round_event();
    }
}
