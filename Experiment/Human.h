#pragma once
#include "TaskManager.h"
#include "World.h"
#include "Logger.h"



class Human
{
private:
	/**Resources that human will take for using their tasks which will be returned if for whatever reason task has been cancelled*/
	Requirement _promisedResources;
	//using std::vector as stack because need direct access to tasks for display
	std::vector<Task const*> _tasks;
	World* _world;
	TaskManager* _taskManager;
	int _currentTaskExecutionCounter = 0;
	//items currently held by ai
	std::map<std::string, int32_t> _inventory;

	inline void _safeAdd(Task const* task)
	{
		if (task != nullptr) { _tasks.push_back(task); }
	}
public:
	std::string Name;
	void AddTask(Task const* task)
	{
		if (!task)
			return;
		for (auto [name,amount] : task->Requirments)
		{
			//make system of fallbacks when if there are not enought resources ai would execute set of tasks
			/* example
			* make plank -> 
			* if no logs -> cut tree -> get logs
			* else -> get logs
			*/
			if (_world->Get(name) >= amount)
			{
				//call "get" task
				//pseudo movement, ideally ai would also find where to go, by looking at all places where needed resource is located and finding the closest one
				//and if that one doesn't have enough add task to go to next one and do this till enough is found
				//but for this expirement there is one super-barn that has all resources
				_safeAdd(_taskManager->Get("move_to"));
				_safeAdd(_taskManager->Get("get_" + name));
			}
			else
			{
				//we don't have enough resources prepared
				_safeAdd(_taskManager->Get("make_" + name));
			}
		}
		_safeAdd(task);
	}

	void DisplayStatus()
	{
		PRINT(termcolor::white, Name << " : ");
		if (_tasks.empty())
		{
			PRINT_LINE(termcolor::green, "Idle");
		}
		else
		{
			for (Task const* task : _tasks)
			{
				PRINT(termcolor::yellow, task->Name << "->");
			}
		}
		std::cout << std::endl;
	}

	void Update(int ticks)
	{
		if (!_tasks.empty())
		{
			_currentTaskExecutionCounter += ticks;
			if (_currentTaskExecutionCounter >= (*_tasks.begin())->ExecutionTime)
			{
				_currentTaskExecutionCounter = 0;
				Task const* t = (*_tasks.begin());

				_tasks.erase(_tasks.begin());

				//on task completion we give all returns back to world and take all needs
				//ideally you'd have mini inventory system to avoid making ai constantly walk back and forth
				//but for simplicity let's say ai always gives everything they have to the "super-barn" as soon as they make it
				for (auto [name, value] : t->Requirments)
				{
					_world->Add(name, -value);
				}
				for (auto [name, value] : t->Returns)
				{
					_world->Add(name, value);
				}
			}
		}
	}
	Human(World* world, std::string name, TaskManager* taskManager) :_world(world), Name(name), _taskManager(taskManager) {}
};
