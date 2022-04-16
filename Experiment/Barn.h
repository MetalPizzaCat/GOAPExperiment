#pragma once
#include "Object.h"
#include <map>
#include <string>
#include <vector>

/// <summary>
/// Barn is used to store resources
/// </summary>
class Barn : public Object
{
private:
	/// <summary>
	/// Max amount of any resource type this barn can store
	/// </summary>
	const int32_t _maxResourceCount = 10;
	std::map<std::string, int32_t> _resources;
public:
	//type of the class
	static const EObjectType ClassType = EOT_Barn;

	virtual constexpr EObjectType Type() { return EOT_Barn; };
	/// <summary>
	/// Returns amount of resource with that name or -1 if it's not present there
	/// </summary>
	/// <returns>amount of resource with that name or 1 if it's not present there</returns>
	int32_t GetResource(std::string const& name);

	void RemoveResource(std::string const& name, int32_t amount);

	void AddResource(std::string const& name, int32_t amount);
};

