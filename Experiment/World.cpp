#include "World.h"
#include "Barn.h"
int32_t World::Get(std::string const&  name)
{
	int32_t total = 0;
	std::vector<Barn*> barns = GetAllObjectsOfType<Barn>();
	for (Barn* b : barns)
	{
		total += b->GetResource(name);
	}
	return total;
}

std::vector<Object*>  World::GetAllObjectsOfType(EObjectType type)
{
	std::vector<Object*> res;
	for (std::unique_ptr<Object>& obj : _objects)
	{
		if (type == obj->Type())
		{
			res.push_back(obj.get());
		}
	}
	return res;
}
