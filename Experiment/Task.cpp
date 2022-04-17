#include "Task.h"

void Task::AddRequirement(std::string name, int32_t amount)
{
	auto it = std::ranges::find_if(_requirements.begin(), _requirements.end(),
		[name](Resource const& res) -> bool {return res.Name == name; });
	if (it != _requirements.end())
	{
		(*it).Amount += amount;
	}
	else
	{
		_requirements.push_back({ name,amount });
	}
}

void Task::AddReturn(std::string name, int32_t amount) 
{ 
	auto it = std::ranges::find_if(_returns.begin(), _returns.end(),
		[name](Resource const& res) -> bool {return res.Name == name; });
	if (it != _returns.end())
	{
		(*it).Amount += amount;
	}
	else
	{
		_returns.push_back({ name,amount });
	}
}