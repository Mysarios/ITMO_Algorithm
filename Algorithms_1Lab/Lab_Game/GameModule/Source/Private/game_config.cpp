#include "../Public/game_config.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <vector>

namespace fs = std::filesystem;
struct stat sb;

namespace
{
    void fill_config(std::ifstream& file, config_type& config)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::map<std::string, float> config_map;
            const size_t equal_symbol_index = line.find('=');
            std::string config_name = line.substr(0, equal_symbol_index);

            std::string tokens_string = line.substr(equal_symbol_index + 1, line.length());
            for (std::vector<std::string> tokens = game_config::split_str(std::move(tokens_string), ";"); auto str :
                 tokens)
            {
                std::vector<std::string> pair = game_config::split_str(std::move(str), ":");
                config_map.emplace(pair[0], std::stof(pair[1]));
            }
            config.emplace(config_name, config_map);
        }
    }

    void find_saves(std::string& part)
    {
        std::vector<std::string> saves;
        int counter_saves = 0;
        for (const auto& entry : fs::directory_iterator(part))
        {
            if (entry.is_regular_file())  // Проверяем, что это файл (не директория)
            {
                std::string filename = entry.path().filename().string();  // Только имя файла с расширением
                std::cout << ++counter_saves << ") | " << filename << std::endl;
                saves.push_back(filename);
            }
        }
        int input_key;
        do
        {
            std::cout << "Enter index of save to load, or 0 to start new game \nPrint: " << std::endl;
            std::cin >> input_key;
            if (input_key == 0)
            {
                part = config::base_config_part;
                break;
            }
            input_key-=1;
            if (input_key < saves.size() && input_key > 0)
            {
                part += saves[input_key];
                return;
            }
            std::cout << "Incorrect index, try again \n\n";
        }
        while (true);
    }
}

game_message game_config::load_data_from_config(config_type& config, std::string config_part)
{
    if (config_part.empty())
    {
        config_part = config::base_config_part; // load base configuration
    }
    else
    {
        find_saves(config_part);
    }

    std::ifstream in_file(config_part);
    if (!in_file.is_open())
    {
        return {error_read_file, "Can't read config file:" + config_part, true}; // can't open file - end
    }

    fill_config(in_file, config); // fill config by file data
    in_file.close();

    return SUCCESS_MESSAGE;
}

std::vector<std::string> game_config::split_str(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}
