#pragma once
#include <map>
#include "Tools.h"
#include <string>
struct Requirement
{
	int Log;
	int Iron;
	int Food;
	ETools NeededTool;
};
class Object;
class Human;

enum ETaskType
{
	/**means nothing really happends except ai waiting for some time*/
	ETT_Generic,
	/**Resources will be taken and/or added to the inventory of the task executor*/
	ETT_ResourceTransfer,
	/**Called if this event has special action to execute*/
	ETT_SpecialAction
};
class Task//yes i know this is used as a class, but i use keyword struct for classes with data-only usage
{
protected:
	std::string _name;
	std::map<std::string, int32_t> _requirements;
	std::map<std::string, int32_t> _returns;
	std::map<std::string, int32_t> _resourcesToTake;

	ETaskType _type = ETT_Generic;
	//simulation of doing something by means of waiting
	//time in game ticks
	int _executionTime;
public:
	std::string const& GetName() const { return _name; }
	std::map < std::string, int32_t> const & GetRequirements()const { return _requirements; }
	std::map < std::string, int32_t> const & GetReturns()const { return _returns; }
	std::map < std::string, int32_t> const & GetResourcesToTake()const { return _resourcesToTake; }

	void AddRequirement(std::string name, int32_t amount) { _requirements[name] += amount; }
	void AddReturn(std::string name, int32_t amount) { _returns[name] += amount; }
	void AddResourcesToTake(std::string name, int32_t amount) { _resourcesToTake[name] += amount; }

	ETaskType GetType()const { return _type; }

	int32_t GetExecutionTime()const { return _executionTime; }
	Task(std::string name, int executionTime, std::map<std::string, int32_t>& requirments, std::map<std::string, int32_t>& returns) :
		_name(name),
		_requirements(std::move(requirments)),//because we don't want value duplication
		_returns(std::move(returns)),//because we don't want value duplication
		_executionTime(executionTime) {}

	Task(std::string name, int executionTime):
		_name(name), _executionTime(executionTime) {}

	/// <summary>
	/// Executed when task needs to be performed
	/// Put here any special actions(like interaction) that need to be executed
	/// </summary>
	/// <param name="target">Object which is the current target of the task(like a tree, creature etc.)</param>
	/// <param name="human">Person that is executing the task</param>
	virtual void Perform(Object* target, Human* human)const {}
};
