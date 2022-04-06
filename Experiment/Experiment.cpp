// Experiment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	string Name;
	vector<Requirement> Requirments;
	//simulation of doing something by means of waiting
	//time in game ticks
	int ExecutionTime;

	Task(string name, int execTime) :
		Name(name), ExecutionTime(execTime) {}
	Task(string name, vector<Requirement>&& requirments, int execTime) :
		Name(name), ExecutionTime(execTime),Requirments(requirments) {}
};
//struct that contains all of the world's resources
struct World
{
	int LogCount;
	int IronCount;
	int FoodCount;
};

class Human
{
private:
	//using vector as stack because need direct access to tasks for display
	vector<Task*> _tasks;
	World& _world;
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
					_tasks.push_back(new Task("Get logs", 10));
				}
				else
				{
					_tasks.push_back(new Task("Get axe", 20));
					_tasks.push_back(new Task("Cut trees", 20));
				}
			}
		}
		_tasks.push_back(new Task(task->Name, task->ExecutionTime));
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
			for (Task* task : _tasks)
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
			Task* task = *_tasks.begin();
			task->ExecutionTime -= ticks;
			if (task->ExecutionTime <= 0)
			{
				delete task;
				_tasks.erase(_tasks.begin());
			}
		}
	}
	Human(World& world,const char *name) :_world(world),Name(name) {}
};

int main()
{
	World world = { 20,20,20 };
	vector<Human> people = {
		Human(world,"Ivan"),
		Human(world,"Vasya"),
		Human(world,"Elena")
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