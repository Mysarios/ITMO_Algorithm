#pragma once

#include "game_message.h"
#include <string>

namespace config
{
    static std::string config_part{ "Hi"};
}
class game_config
{
private:
    size_t max_rounds_ = 0;
public:
    [[nodiscard]] size_t get_max_rounds() const {return max_rounds_;}
    
    game_message load_data_from_config();
};
