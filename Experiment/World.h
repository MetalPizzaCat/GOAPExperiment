#pragma once
#include <map>
#include <string>
/**World contains all of the resources in the world*/
class World
{
private:
	std::map<std::string , int32_t> _resources;
public:
	/*Get amount of resource with this name
	* Ideally this would interate over all objects that store this item*/
	int32_t Get(std::string const&  name);
	void Add(std::string const&  name, int32_t amount);
};
