#include "Barn.h"

int32_t Barn::GetResource(std::string const& name)
{
    return _resources.contains(name) ? _resources[name] : -1;
}

void Barn::RemoveResource(std::string const& name, int32_t amount)
{
    if (_resources[name] > 0)
    {
        _resources[name] -= amount > _resources[name] ? _resources[name] : amount;
    }
}

void Barn::AddResource(std::string const& name, int32_t amount)
{
    _resources[name] += amount;
}