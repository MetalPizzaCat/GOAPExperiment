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
#include<memory>

#define PRINT(color,text) std::cout << color << text;
#define PRINT_LINE(color,text) std::cout << color << text << termcolor::reset << std::endl
#define RESET_COLOR() std::cout << termcolor::reset << std::endl
#define SCREEN_CLEAR() cout << "\033[2J\033[1;1H"
using namespace std;

enum ETools
{
	ET_None,
	ET_Axe,
	ET_SmithingTable,
	ET_Hammer
};
struct Requirement
{
	int Log;
	int Iron;
	int Food;
	ETools NeededTool;
};

struct Task
{
	const char* Name;
	Requirement Requirments;
	vector<Requirement> Returns;
	//simulation of doing something by means of waiting
	//time in game ticks
	int ExecutionTime;

	Task(const char* name, int execTime) :
		Name(name), ExecutionTime(execTime) {}
	Task(const char* name, Requirement && requirments, int execTime) :
		Name(name), ExecutionTime(execTime),Requirments(requirments) {}

	Task(const char* name, Requirement requirments, int execTime) :
		Name(name), ExecutionTime(execTime), Requirments(requirments) {}
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
	bool Add(const char* name, int executionTime,Requirement requirement)
	{
		vector<Task*>::iterator it = std::find_if(_tasks.begin(), _tasks.end(), [name](Task* task) {return task->Name == name; });
		if (it == _tasks.end())
		{
			_tasks.push_back(new Task(name, requirement, executionTime));
			return true;
		}
		return false;
	}
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

	//Get task by name
	//value is returned as const to avoid accidental modifications to value
	Task const* Get(const char* name)
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
	Task const* At(int id)
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
	TaskManager* _taskManager;
	int _currentTaskExecutionCounter = 0;

	inline void _safeAdd(Task const* task) {
		if (task != nullptr) { _tasks.push_back(task); }
	}
public:
	const char* Name;
	void AddTask(Task const* task)
	{
		if (task->Requirments.Log > 0)
		{
			if (_world.LogCount >= task->Requirments.Log)
			{
				_safeAdd(_taskManager->Get("get_logs"));
			}
			else
			{
				_safeAdd(_taskManager->Get("get_axe"));
				_safeAdd(_taskManager->Get("cut_trees"));
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
	Human(World& world,const char *name, TaskManager* taskManager) :_world(world),Name(name),_taskManager(taskManager) {}
};

int main()
{
	World world = { 20,20,20 };
	unique_ptr<TaskManager> manager = make_unique<TaskManager>();
	vector<Human> people = {
		Human(world,"Ivan",manager.get()),
		Human(world,"Vasya",manager.get()),
		Human(world,"Elena",manager.get())
	};
	manager->Add("make_plank", 20, { 20,0,0,ETools::ET_Axe });
	manager->Add("cut_trees", 20, { 0,0,0,ETools::ET_Axe });
	manager->Add("get_logs", 20, { 0,0,0,ETools::ET_Axe });
	
	people[0].AddTask(manager->operator[]("make_plank"));
	people[1].AddTask(manager->operator[]("make_plank"));
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