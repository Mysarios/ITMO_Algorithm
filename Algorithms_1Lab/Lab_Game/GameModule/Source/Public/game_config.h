#pragma once

#include <map>

#include "game_message.h"
#include <string>
#include <vector>

#include "game_info.h"

namespace config
{
    static std::string base_config_part{ "GameModule/Config/BaseParametersConfig.txt"};
    static std::string save_part{ "GameModule/Saves/"};
}

using config_type = std::map<std::string,std::map<std::string,float>>;

class game_config
{
public:
    static game_message load_data_from_config(config_type& config, std::string config_part = {});
    static std::vector<std::string> split_str(std::string s, const std::string& delimiter);
    static game_message start_save(game_info* info);
};
