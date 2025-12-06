#pragma once

#include <map>
#include <unordered_map>
#include <variant>

#include "game_message.h"
#include "game_resourses.h"

using resource_cost = std::unordered_map<resource, float>;
using resource_cost_map = std::unordered_map<resource, std::unordered_map<resource, float>>;
using resource_map = std::unordered_map<resource, std::variant<unsigned int, float>>;
using resource_index_table = std::vector<std::pair<size_t, resource>>;
using config_type = std::map<std::string,std::map<std::string,float>>;

struct civilization_info
{
private:
    resource_map resource_map_;
    resource_cost_map cost_map_;
    resource_cost_map base_cost_map_;

public:
    explicit civilization_info(const std::map<std::string, float>& resource_config,
                               const resource_cost_map& base_cost_config);
    civilization_info() = default;

    std::map<std::string, std::string> get_info_to_save_resource_map();
    std::map<std::string, std::string> get_info_to_save_base_cost_map();
    void buy_resource(const resource& buy, const resource& sell, unsigned int count);
    void print_all_info();
    
    resource_index_table print_cost_information_to_buy(const resource& resource);
    resource_index_table print_cost_information(const resource& resource);
    resource_index_table print_buy_information();
    
    bool try_to_buy_resources(const resource& want_buy, const resource& want_sell, unsigned int count);

    float get_resource_count(const resource& resource_name);
    float get_resource_cost(const resource& want_buy, const resource& want_sell);
    std::vector<resource> get_saleable_resources();

    int get_humans_count() const;
    void add_humans(int count);

    void randomize_costs(float percent);

    bool add_resource_by_another(const resource& witch_deal, const resource& added_resource, float multiplier,float with_limit =-1);
    bool spend_resource_by_another(const resource& spended_resource, const resource& resource,
    float multiplier,bool can_be_null);
    bool spend_resource_by_another_with_loss(const resource& spended_resource, const resource& resource,
    float multiplier);
};

struct randomize_info
{
};

class game_info
{
private:
    
    size_t max_rounds_ = 0;
    float random_percent_ = 0.f;

    bool read_config_and_init_game(const config_type& config);
    static void start_dialogue(bool is_new_game);
    
public:
    civilization_info main_information;
    size_t current_round = 0;
public:
    game_info() = default;
    [[nodiscard]] size_t get_max_rounds_count() const { return max_rounds_; }
    [[nodiscard]] float get_randomize_percent() const { return random_percent_; }

    game_message try_load_game_or_create(const std::string& config_part = {});
    bool game_lose() const;
};
