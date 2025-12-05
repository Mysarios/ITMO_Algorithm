#include "../Public/game_loop.h"

#include <iostream>

namespace
{
    bool buy_dialogue(game_info* info)
    {
        const auto buy_array = info->main_information.print_buy_information();

        int input_key;
        while (true)
        {
            std::cout << "Enter: resource table-index of resource to try buy it\nEnter: 0 to end buy\n\nPrint: ";
            std::cin >> input_key;
            if (!input_key)
            {
                return false;
            }
            if (input_key < 1 || input_key > buy_array.size())
            {
                std::cout << "Incorrect index!" << '\n';
                continue;
            }
            const resource resource_to_buy = buy_array[input_key - 1].second;
            const auto sell_array = info->main_information.print_cost_information_to_buy(resource_to_buy);
            int input_key_to_sell;


            std::cout << "Enter: index of resource-table to try sell it\nEnter: 0 to end buy\n\nPrint: ";
            std::cin >> input_key_to_sell;
            if (!input_key)
            {
                continue;
            }
            if (input_key_to_sell < 1 || input_key_to_sell > sell_array.size())
            {
                std::cout << "Incorrect index!" << '\n';
                continue;
            }
            const resource resource_to_sell = sell_array[input_key_to_sell - 1].second;

            int count_to_buy;
            std::cout << "=U wanna buy: " << resource_to_buy.name << " by: " << resource_to_sell.name << '\n';
            std::cout << "Enter count resource u want buy" << '\n';
            std::cin >> count_to_buy;

            info->main_information.buy_resource(resource_to_buy, resource_to_sell, count_to_buy);
            break;
        }
        return true;
    }

    void info_dialogue(game_info* info)
    {
        info->main_information.print_all_info();
    }

    bool input_dialogue(game_info* info, const int input_key)
    {
        switch (input_key)
        {
        case 1:
            buy_dialogue(info); //buy
            return true;
        case 2:
            info_dialogue(info); // info about all
            return true;
        case 3:
            std::cout << "=End round!\n" << '\n'; // end
            return false;
        default:
            std::cout << "Enter correct input! ..." << '\n'; //retry
            return true;
        }
    }
}

randomize_round_params game_loop::get_random_params()
{
    return randomize_round_params{}; // end
}

void game_loop::first_message_after_game_start(const bool new_game) const
{
    if (!new_game)
    {
        std::cout << "=Game again started!\n U have " << info_->get_max_rounds_count() - round_ <<
            " to continue create best civilization, or die unknown!\n Good luck!\n" << '\n';
    }
    else
    {
        std::cout << "=Game Started!\nU have " << info_->get_max_rounds_count() <<
            " rounds to create best civilization, or die unknown!\nGood luck!\n" << '\n';
    }
}

void game_loop::before_round_event()
{
    std::cout << "--------------------------------" << '\n';
    std::cout << "=Round: " << round_ + 1 << '\n';
    std::cout << "--------------------------------" << '\n';
    get_random_params();
}

bool game_loop::round_event() const
{
    std::cout <<
        "Enter: 1 to buy resource\nEnter: 2 to get info about all resources\nEnter: 3 to end round\nEnter: 4 to save game and exit\n\nPrint: ";

    int input;
    std::cin >> input;
    if (!input_dialogue(info_, input))
    {
        return false;
    }
    if (info_->game_lose())
    {
        std::cout << "=U sell all humans, it's not bad, but, but... maybe U wanna play trading simulator...?" <<
            '\n';
        return false;
    }
    std::cout << "--------------------------------\n" << '\n';
    return true;
}

void game_loop::after_round_event()
{
    // Disasters
    // Add humans
    ++round_;
}


game_loop::game_loop(game_info* new_game_info) : info_(new_game_info){};

void game_loop::loop()
{
    first_message_after_game_start(round_);

    const size_t max_rounds = info_->get_max_rounds_count();
    while (round_ <= max_rounds)
    {
        before_round_event();

        bool round_play = true;
        while (round_play)
        {
            round_play = round_event();
        }

        after_round_event();

        if (info_->game_lose())
        {
            std::cout << "U lose =(" << '\n';
            return;
        }
    }
    
    std::cout << "U Win!!!! =)" << '\n';
}
