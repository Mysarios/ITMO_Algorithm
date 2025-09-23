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
    
public:
    game_message load_data_from_config();
};
