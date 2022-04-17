#pragma once
#include "TaskManager.h"
#include "World.h"
#include "Logger.h"

class Human : public Object
{
private:
	//using std::vector as stack because need direct access to tasks for display
	std::vector<Task*> _tasks;
	World* _world = nullptr;
	TaskManager* _taskManager = nullptr;
	int _currentTaskExecutionCounter = 0;
	//items currently held by ai
	std::map<std::string, int32_t> _inventory;

	//current destination
	Object* _currentTarget = nullptr;

	void _safeAdd(Task const* task, Resource* specialTaskData = nullptr);

	void _prepareNewTask();
public:
	std::string Name;
	void AddTask(Task const* task);

	void DisplayStatus();

	void Update(int ticks);
	Human(World* world, std::string name, TaskManager* taskManager) :_world(world), Name(name), _taskManager(taskManager) {}

	virtual ~Human();
};
