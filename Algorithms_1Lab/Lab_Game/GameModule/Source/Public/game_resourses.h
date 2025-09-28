#pragma once
#include <string>

enum resource_name
{
    gold,
    food,
    humans,
    warriors,
    fields,
    happines,
    taller
};

struct resource
{
    resource_name type;
    std::string name;
    bool IsInt = false;
    bool operator==(const resource& B) const
    {
        return type == B.type;
    }
    resource(std::string getted_str_name) : name(getted_str_name)
    {
       if(getted_str_name == "gold") {type = gold; }
       else if(getted_str_name == "food") {type = food; }
       else if(getted_str_name == "humans") { type = humans; IsInt = true; }
       else if(getted_str_name == "warriors") {type = warriors; IsInt = true; }
       else if(getted_str_name == "fields") {type = fields; }
       else if(getted_str_name == "happines") { type = happines; }
       else if(getted_str_name == "taller") {type = taller; }
    }
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
