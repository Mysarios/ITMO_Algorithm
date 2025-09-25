#pragma once

#include <map>

#include "game_message.h"
#include <string>
#include <vector>

namespace config
{
    static std::string base_config_part{ "GameModule/Config/BaseParametersConfig.txt"};
}

class game_config
{
public:
    static game_message load_data_from_config(std::map<std::string, std::map<std::string, float>>& config, std::string config_part = {});
    static std::vector<std::string> split_str(std::string s, const std::string& delimiter);
};
