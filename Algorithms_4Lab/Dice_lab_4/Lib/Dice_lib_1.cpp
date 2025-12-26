#include "Dice_lib_1.h"

#include <iostream>
#include <sstream>

#include "vector"

namespace
{
    std::pair<int, int> parse_count(const std::string& dice_str)
    {
        std::string current_num;
        size_t i = 0;

        while (i < dice_str.size() && std::isdigit(dice_str[i]))
        {
            current_num += dice_str[i];
            i++;
        }

        if (!current_num.empty())
        {
            return {std::stoi(current_num), i};
        }
        else
        {
            return {1, i};
        }
    }

    int parse_modify(const std::string& dice_str)
    {
        if (dice_str.empty())
        {
            return 0;
        }

        if (dice_str[0] == '+')
        {
            return parse_count(dice_str.substr(1)).first;
        }
        else if (dice_str[0] == '-')
        {
            return -1 * parse_count(dice_str.substr(1)).first;
        }
        return 0;
    }

    special_dice parse_one_dice(std::string dice_str)
    {
        //count check
        const std::pair<int, int> count_pair = parse_count(dice_str);
        int count = count_pair.first;
        size_t index_d = count_pair.second;

        // check d
        if (index_d < dice_str.size() && dice_str[index_d] != 'd')
        {
            return {0, 0, 0};
        }
        ++index_d;

        // parse val
        std::string substr_value_and_mody = dice_str.substr(index_d);
        const std::pair<int, int> val_pair = parse_count(substr_value_and_mody);
        int max_val = val_pair.first;
        size_t index_mody = val_pair.second;

        //parse mody
        int modifier = parse_modify(substr_value_and_mody.substr(index_mody));

        return {count, max_val, modifier};
    }

    std::vector<special_dice> create_dices_by_string(std::string str)
    {
        std::vector<special_dice> result;
        if (str.empty())
        {
            return result;
        }
        //check bad str
        std::string processed_str = str;
        processed_str.erase(
            std::remove_if(processed_str.begin(), processed_str.end(), ::isspace),
            processed_str.end()
        );

        std::stringstream str_stream(str);
        std::string one_dice;

        while (std::getline(str_stream, one_dice, ','))
        {
            if (!one_dice.empty())
            {
                special_dice dice = parse_one_dice(one_dice);
                //correct values
                if (dice.dice_is_correct())
                {
                    result.push_back(dice);
                }
            }
        }
        return result;
    }
}

int DiceGenerator::generate_value() const
{
    int result = 0;
    for (const auto dice : dices_)
    {
        result += dice.generate_value();
    }
    return result;
}

std::string DiceGenerator::get_string()
{
    std::string result_str{};
    for (const auto dice : dices_)
    {
        dice.add_to_string(result_str);
        //dice.print();
    }
    return result_str;
}

void DiceGenerator::new_dices(const std::string& dice_input)
{
    dices_.clear();
    std::string result_str{};
    dices_ = create_dices_by_string(dice_input);
    /*for (const auto dice : dices_)  //Debug 
    {
        dice.add_to_string(result_str);
        dice.print();
    }
/std::cout << "Back to string: " << result_str << '\n';*/
}
