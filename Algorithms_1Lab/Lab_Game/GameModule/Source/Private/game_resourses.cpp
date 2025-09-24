#include "../Public/game_resourses.h"


/*float game_info::get_cost_multiplier(const resource resource)
{
    float result = 1;
    switch (resource.type)
    {
    case gold:
        result = after_round_random_params_.eat_cost;
        break;
    case food:
        result = after_round_random_params_.food_cost;
        break;
    case warriors:
        result = after_round_random_params_.warriors_cost;
        break;
    case fields:
        result = after_round_random_params_.fields_cost;
        break;
    default: ;
    }
    return result;
}

unsigned int game_info::get_count_resource(resource resource)
{
    unsigned int count = 0;
    const civilization_info info = info_->main_information;
    switch (resource.type)
    {
    case gold:
        count = info.gold;
        break;
    case food:
        count = info.food;
        break;
    case warriors:
        count = info.warriors;
        break;
    case fields:
        count = info.fields;
        break;
    case humans:
        count = info.base_humans;
        break;
    default: ;
    }
    return count;
}

bool game_info::can_buy_resource(const resource& getted_by,const resource& lost_resource, const unsigned int count)
{
    return get_cost_multiplier(getted_by) * static_cast<float>(count) <= static_cast<float>(
        get_count_resource(lost_resource));
}*/



