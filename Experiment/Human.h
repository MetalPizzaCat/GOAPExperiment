#pragma once
#include "TaskManager.h"
#include "World.h"
#include "Logger.h"

class Human : public Object
{
private:
	/**Resources that human will take for using their tasks which will be returned if for whatever reason task has been cancelled*/
	Requirement _promisedResources;
	//using std::vector as stack because need direct access to tasks for display
	std::vector<Task const*> _tasks;
	World* _world = nullptr;
	TaskManager* _taskManager = nullptr;
	int _currentTaskExecutionCounter = 0;
	//items currently held by ai
	std::map<std::string, int32_t> _inventory;

	//current destination
	Object* _currentTarget = nullptr;

	inline void _safeAdd(Task const* task)
	{
		if (task != nullptr) { _tasks.push_back(task); }
	}
public:
	std::string Name;
	void AddTask(Task const* task);

	void DisplayStatus();

	void Update(int ticks);
	Human(World* world, std::string name, TaskManager* taskManager) :_world(world), Name(name), _taskManager(taskManager) {}
};
