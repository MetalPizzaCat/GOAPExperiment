#include "Task.h"

void Task::AddRequirement(std::string name, int32_t amount)
{
	auto it = std::ranges::find_if(_requirements->begin(), _requirements->end(),
		[name](Resource const& res) -> bool {return res.Name == name; });
	if (it != _requirements->end())
	{
		(*it).Amount += amount;
	}
	else
	{
		_requirements->push_back({ name,amount });
	}
}

void Task::AddReturn(std::string name, int32_t amount) 
{ 
	auto it = std::ranges::find_if(_returns->begin(), _returns->end(),
		[name](Resource const& res) -> bool {return res.Name == name; });
	if (it != _returns->end())
	{
		(*it).Amount += amount;
	}
	else
	{
		_returns->push_back({ name,amount });
	}
}

Task::Task(Task const& task):
	_requirements(task._requirements),
	_returns(task._returns),
	_name(task._name),
	_type(task._type),
	_executionTime(task._executionTime) {}

Task::Task(Task const* task):
_requirements(task->_requirements),
_returns(task->_returns),
_name(task->_name),
_type(task->_type),
_executionTime(task->_executionTime) {}

Task::Task(std::string name, int executionTime, EObjectType neededObjectType) :
	_name(name), _executionTime(executionTime), NeededObjectType(neededObjectType) 
{
	_requirements = new std::vector<Resource>();
	_returns = new std::vector<Resource>();
}
