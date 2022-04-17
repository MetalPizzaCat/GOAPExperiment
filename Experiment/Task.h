#pragma once
#include <map>
#include "Tools.h"
#include <string>
#include <vector>
#include "Object.h"
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

struct Resource
{
	std::string Name;
	int32_t Amount;
};

class Task
{
protected:
	std::string _name;
	/** What human needs to have BEFORE starting the task*/
	std::vector<Resource> _requirements;
	/**What human will get as the result of the executing the task*/
	std::vector<Resource> _returns;

	

	ETaskType _type = ETT_Generic;
	//simulation of doing something by means of waiting
	//time in game ticks
	int _executionTime;
public:

	//what?
	//the idea is to write here data that will need to be executed with this specific version of the task
	//such as 
	Resource CurrentTaskData;

	/**What kind of object is needed as target. Or EOT_Object if no object is nessesary*/
	const EObjectType NeededObjectType = EOT_Object;
	std::string const& GetName() const { return _name; }
	std::vector<Resource> const & GetRequirements()const { return _requirements; }
	std::vector<Resource> const & GetReturns()const { return _returns; }

	/**Adds new requirment or adds more amount to the existing one*/
	void AddRequirement(std::string name, int32_t amount);

	void AddReturn(std::string name, int32_t amount);

	ETaskType GetType()const { return _type; }

	int32_t GetExecutionTime()const { return _executionTime; }

	Task(std::string name, int executionTime, EObjectType neededObjectType):
		_name(name), _executionTime(executionTime),NeededObjectType(neededObjectType){}

	/// <summary>
	/// Executed when task needs to be performed
	/// Put here any special actions(like interaction) that need to be executed
	/// </summary>
	/// <param name="target">Object which is the current target of the task(like a tree, creature etc.)</param>
	/// <param name="human">Person that is executing the task</param>
	virtual bool Perform(Object* target, Human* human)const { return false; }
};
