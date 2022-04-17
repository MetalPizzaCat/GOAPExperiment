/**
* This is a simple c++ experiment focused on trying to make GOAP ai 
*/
#include <iostream>
#include <vector>
#include <map>

#include <chrono>
#include <stack>
#include <thread>
#include <memory>
#include "TaskManager.h"
#include "Human.h"
#include "Tasks.h"
#include "Tree.h"
#include "Barn.h"

using namespace std;

int main()
{
	World* world = new World();

	unique_ptr<TaskManager> manager = make_unique<TaskManager>();
	vector<Human> people =
	{
		Human(world,"Ivan",manager.get()),
		Human(world,"Vasya",manager.get()),
		Human(world,"Elena",manager.get())
	};
	manager->Add(new Task("make_plank", 20, EOT_Object));
	manager->At(0)->AddRequirement("log", 5);
	manager->At(0)->AddReturn("plank", 1);

	manager->Add(new Task("get_log", 1, EOT_Barn));
	manager->Add(new Task("move_to", 10, EOT_Object));

	manager->Add(new TaskCutTree("make_log", 20, EOT_Tree));
	manager->At(3)->AddReturn("log", 5);

	people[0].AddTask(manager->Get("make_plank"));

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