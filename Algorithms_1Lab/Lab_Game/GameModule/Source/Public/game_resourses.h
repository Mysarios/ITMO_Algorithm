#pragma once
#include <string>

enum resource_name
{
    gold,
    food,
    humans,
    warriors,
    fields
};

struct resource
{
    resource_name type;
    std::string name;
    bool operator==(const resource& B) const
    {
        return type == B.type;
    }
};

class game_resources
{
public:
    bool try_to_by_resources(const resource& want_by, const resource& want_sell, unsigned int count);

    float get_cost_multiplier(resource resource);
    bool can_buy_resource(const resource& getted_by, const resource& lost_resource,unsigned int count);
    unsigned int get_count_resource(resource resource);
};

//hash func for unordered_map
namespace std
{
    template<>
    struct hash<resource>
    {
        size_t operator()(const resource& r) const
        {
            size_t h1 = hash<resource_name>{}(r.type);
            size_t h2 = hash<std::string>{}(r.name);
            size_t seed = h1;
            seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}
