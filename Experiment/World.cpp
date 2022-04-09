#include "World.h"

int32_t World::Get(std::string const&  name)
{
    return  _resources[name];
}

void World::Add(std::string const& name, int32_t amount)
{
    _resources[name] += amount;
}
