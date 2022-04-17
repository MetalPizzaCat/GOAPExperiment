#include "Human.h"
#include "Barn.h"
#include "Tree.h"
#include <algorithm>
#include "Tasks.h"
void Human::Update(int ticks)
{
	if (!_tasks.empty())
	{
		_currentTaskExecutionCounter += ticks;
		if (_currentTaskExecutionCounter >= (*_tasks.begin()).Task->GetExecutionTime())
		{
			_currentTaskExecutionCounter = 0;
			TaskData  t = (*_tasks.begin());

			_tasks.erase(_tasks.begin());
			t.Task->Perform(_currentTarget, this,t);
			_prepareNewTask();
		}
	}
}

void Human::RemoveResource(std::string const& name, int32_t amount)
{
	if (_inventory[name] > 0)
	{
		_inventory[name] -= amount > _inventory[name] ? _inventory[name] : amount;
	}
}

void Human::AddResource(std::string const& name, int32_t amount)
{
	_inventory[name] += amount;
}

void Human::DisplayStatus()
{
	PRINT(termcolor::white, Name << " : ");
	if (_tasks.empty())
	{
		PRINT_LINE(termcolor::green, "Idle");
	}
	else
	{
		for (TaskData& task : _tasks)
		{
			PRINT(termcolor::yellow, task.Task->GetName() << "->");
		}
	}
	std::cout << std::endl;
}

void Human::AddTask(Task const* task, Resource* specialTaskData)
{
	if (!task)
		return;
	for (Resource const& res : (task->GetRequirements()))
	{
		//make system of fallbacks when if there are not enought resources ai would execute set of tasks
		/* example
		* make plank ->
		* if no logs -> cut tree -> get logs
		* else -> get logs
		*/
		if (_world->Get(res.Name) >= res.Amount)
		{
			//call "get" task
			//pseudo movement, ideally ai would also find where to go, by looking at all places where needed resource is located and finding the closest one
			//and if that one doesn't have enough add task to go to next one and do this till enough is found
			//but for this expirement there is one super-barn that has all resources
			_safeAdd(_taskManager->Get("move_to"));
			_safeAdd(_taskManager->Get("get_" + res.Name), new Resource{res.Name,res.Amount});
		}
		else
		{
			//we don't have enough resources prepared
			_safeAdd(_taskManager->Get("make_" + res.Name), new Resource{ res.Name,res.Amount });
		}
	}
	_safeAdd(task, specialTaskData);
}

void Human::AddTask(std::string name, Resource* specialTaskData)
{
	AddTask(_taskManager->Get(name));
}

void Human::_prepareNewTask()
{
	if (!_tasks.empty())
	{
		TaskData t = (*_tasks.begin());
		switch (t.Task->NeededObjectType)
		{
		case EOT_Barn:
		{
			if (std::vector<Barn*> barns = _world->GetAllObjectsOfType<Barn>(); !barns.empty() && t.TaskResourceData)
			{
				size_t id = 0;
				float bestCost = max(0, min(barns[0]->GetResource(t.TaskResourceData->Name) / t.TaskResourceData->Amount, 1)) / barns[0]->GetLocation().Distance(GetLocation());
				for (int i = 1; i < barns.size(); i++)
				{
					//cost = min(0,max(have/need,1))/distance
					//the formula just looked nice on graphs
					float cost = max(0, min(barns[0]->GetResource(t.TaskResourceData->Name) / t.TaskResourceData->Amount, 1)) / barns[0]->GetLocation().Distance(GetLocation());
					if (cost < bestCost)
					{
						id = i;
						bestCost = cost;
					}
				}
				_currentTarget = barns[id];
			}
			break;
		}
		case EOT_Tree:
		{
			if (std::vector<Tree*> trees = _world->GetAllObjectsOfType<Tree>(); !trees.empty() && t.TaskResourceData)
			{
				size_t id = 0;
				float bestCost = max(0, min(trees[0]->GetLogCount() / t.TaskResourceData->Amount, 1)) / trees[0]->GetLocation().Distance(GetLocation());
				for (int i = 1; i < trees.size(); i++)
				{
					//cost = min(0,max(have/need,1))/distance
					//the formula just looked nice on graphs
					float cost = max(0, min(trees[0]->GetLogCount() / t.TaskResourceData->Amount, 1)) / trees[0]->GetLocation().Distance(GetLocation());
					if (cost < bestCost)
					{
						id = i;
						bestCost = cost;
					}
				}
				_currentTarget = trees[id];
			}
			break;
		}
		default:
			break;
		}
	}
}

void Human::_safeAdd(Task const* task, Resource* specialTaskData)
{
	if (task != nullptr)
	{
		_tasks.push_back(TaskData{task,specialTaskData});
	}
}

Human::~Human()
{
}
