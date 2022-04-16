#pragma once
#include <map>
#include <string>
#include <vector>
#include "Object.h"
#include <memory>

/**World contains all of the resources in the world*/
class World
{
private:
	std::vector<std::unique_ptr<Object>> _objects;
public:
	/**Gets total amount of this resource in the world, including every barn placed*/
	int32_t Get(std::string const&  name);

	template<class T = Object>
	std::vector<T*> GetAllObjectsOfType()
	{
		std::vector<T*> res;
		for (std::unique_ptr<Object>const & obj : _objects)
		{
			if (obj->Type() == T::ClassType)
			{
				res.push_back(static_cast<T*>(obj.get()));
			}
		}
		return res;
	}

	std::vector<Object*> GetAllObjectsOfType(EObjectType type);
};	
