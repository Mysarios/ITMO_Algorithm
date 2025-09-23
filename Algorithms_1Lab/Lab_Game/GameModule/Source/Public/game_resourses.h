#pragma once
#include <string>


enum resourse_name
{
    gold,
    food,
    humans,
    warriors,
    fields
};

struct resourse
{
    resourse_name type;
    std::string name;
};
