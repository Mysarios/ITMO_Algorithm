#include "../Public/game_config.h"

#include <fstream>
#include <ranges>
#include <vector>


game_message game_config::load_data_from_config(std::map<std::string,std::map<std::string,float>>& config, std::string config_part)
{
    if(config_part.length() == 0)
    {
        config_part = config::base_config_part;
    }
    std::ifstream in_file(config_part);
    if (!in_file.is_open())
    {
        return {error_read_file,"Can't read config file:" + config_part,true};
    }  
    std::string line;  
    while (std::getline(in_file, line)) {
        std::map<std::string,float> config_map;
        size_t equal_symbol_index = line.find('=');
        std::string config_name = line.substr(0, equal_symbol_index);

        std::string tokens_string = line.substr(equal_symbol_index+1, line.length());
        std::vector<std::string> tokens = split_str(std::move(tokens_string), ";");
        for(auto str : tokens)
        {
            std::vector<std::string> pair = split_str(std::move(str), ":");
            config_map.emplace(pair[0],std::stof(pair[1]));
        }
        config.emplace(config_name,config_map);
    }  
    in_file.close();
    
    return SUCCESS_MESSAGE;
}

std::vector<std::string> game_config::split_str(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}
