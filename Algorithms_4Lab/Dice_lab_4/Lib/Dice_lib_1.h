#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

namespace
{
    struct special_dice
    {
    private:
        std::string print_without_endl() const
        {
            std::string result;
            if (count_ != 1)
            {
                result += std::to_string(count_);
            }
            result += "d" + std::to_string(max_gen_value_);
            if (modifyer_ != 0)
            {
                if (modifyer_ > 0)
                {
                    result += "+";
                }
                result += std::to_string(modifyer_);
            }
            return result;
        }

        int generate_value_from_one_dice() const
        {
            return rand() % max_gen_value_;
        }

        int count_ = 0;
        int max_gen_value_ = 0;
        int modifyer_ = 0;

    public:
        special_dice(const int new_count, const int max_val, const int mod) : count_(new_count), max_gen_value_(max_val), modifyer_(mod)
        {
        }

        bool dice_is_correct() const
        {
            return count_ > 0 && max_gen_value_ > 0;
        }

        void print() const
        {
            std::cout << print_without_endl() << '\n';
        }

        void add_to_string(std::string& string_to_add) const
        {
            if (!string_to_add.empty())
            {
                string_to_add += ",";
            }
            string_to_add += print_without_endl();
        }

        int generate_value() const
        {
            int result{0};
            for (int i = 0; i < count_; ++i)
            {
                result += generate_value_from_one_dice() + modifyer_;
            }
            return result;
        }
    };
}

class DiceGenerator
{
private:
    std::vector<special_dice> dices_{};

public:
    DiceGenerator() = default;
    void new_dices(const std::string& dice_input);
    int generate_value() const;
    int count_dices() const {return dices_.size();}

    std::string get_string();
};
