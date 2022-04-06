/**
* This is a single file c++ experiment focused on trying to make GOAP ai 
*/
#include <iostream>
#include <vector>
#include <map>
#include <termcolor/termcolor.hpp>
#include <chrono>
#include <stack>
#include <thread>

#define PRINT(color,text) std::cout << color << text;
#define PRINT_LINE(color,text) std::cout << color << text << termcolor::reset << std::endl
#define RESET_COLOR() std::cout << termcolor::reset << std::endl
#define SCREEN_CLEAR() cout << "\033[2J\033[1;1H"
using namespace std;

enum Tool
{
	None,
	Axe,
	SmithingTable,
	Hammer
};
struct Requirement
{
	int Log;
	int Iron;
	int Food;
	Tool NeededTool;
};

struct Task
{
	const char* Name;
	vector<Requirement> Requirments;
	vector<Requirement> Returns;
	//simulation of doing something by means of waiting
	//time in game ticks
	int ExecutionTime;

	Task(const char* name, int execTime) :
		Name(name), ExecutionTime(execTime) {}
	Task(const char* name, vector<Requirement>&& requirments, int execTime) :
		Name(name), ExecutionTime(execTime),Requirments(requirments) {}
};
//struct that contains all of the world's resources
struct World
{
	int LogCount;
	int IronCount;
	int FoodCount;
};

class TaskManager
{
private:
	vector<Task*> _tasks;
public:
	//Get task by name
	//value is returned as const to avoid accidental modifications to value
	Task const* operator[](const char* name)
	{
		for (Task*& task : _tasks)
		{
			if (task->Name == name)
			{
				return task;
			}
		}
		return nullptr;
	}

	Task const* operator[](int id)
	{
		if(id >=0 && id < _tasks.size())
		{
			return _tasks[id];
		}
		return nullptr;
	}
};

class Human
{
private:
	//using vector as stack because need direct access to tasks for display
	vector<Task const*> _tasks;
	World& _world;
	TaskManager& _taskManager;
	int _currentTaskExecutionCounter = 0;
public:
	const char* Name;
	void AddTask(Task const*  task)
	{
		for (Requirement req : task->Requirments)
		{
			if (req.Log > 0)
			{
				if (_world.LogCount >= req.Log)
				{
					_tasks.push_back(_taskManager["get_logs"]);
				}
				else
				{
					_tasks.push_back(_taskManager["get_axe"]);
					_tasks.push_back(_taskManager["cut_trees"]);
				}
			}
		}
		_tasks.push_back(task);
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
		cout << endl;
	}

	void Update(int ticks)
	{
		if (!_tasks.empty())
		{
			_currentTaskExecutionCounter += ticks;
			if (_currentTaskExecutionCounter  >= (*_tasks.begin())->ExecutionTime)
			{
				_currentTaskExecutionCounter = 0;
				_tasks.erase(_tasks.begin());
			}
		}
	}
	Human(World& world,const char *name, TaskManager& taskManager) :_world(world),Name(name),_taskManager(taskManager) {}
};

int main()
{
	World world = { 20,20,20 };
	TaskManager manager;
	vector<Human> people = {
		Human(world,"Ivan",manager),
		Human(world,"Vasya",manager),
		Human(world,"Elena",manager)
	};
	//array of all possible tasks
	vector<Task*> tasks = {
		new Task
		{
			"Make plank",vector<Requirement>
			{
				{10,20,30}
			},20
		},
		new Task
		{
			"Make a lot of planks",vector<Requirement>
			{
				{100,20,30}
			},20
		},
		new Task
		{
			"Build house",vector<Requirement>
			{
				{100,20,30}
			},20
		}
	};
	people[0].AddTask(tasks[0]);
	people[1].AddTask(tasks[1]);
	while (true)
	{
		SCREEN_CLEAR();
		for (Human& human : people)
		{
			human.Update(1);
			human.DisplayStatus();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}