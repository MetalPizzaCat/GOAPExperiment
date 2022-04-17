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
	unique_ptr<World> world = std::make_unique<World>();
	world->SpawnObject<Tree>();
	Barn* b = world->SpawnObject<Barn>();
	b->AddResource("log", 5);

	unique_ptr<TaskManager> manager = make_unique<TaskManager>();
	vector<Human> people =
	{
		Human(world.get(),"Ivan",manager.get()),
		Human(world.get(),"Vasya",manager.get()),
		Human(world.get(),"Elena",manager.get())
	};
	manager->Add(new Task("make_plank", 5, EOT_Object));
	manager->At(0)->AddRequirement("log", 5);
	manager->At(0)->AddReturn("plank", 1);

	manager->Add(new TaskTakeResources("get_log", 2, EOT_Barn));
	manager->Add(new Task("move_to", 2, EOT_Object));

	manager->Add(new TaskCutTree("make_log", 20, EOT_Tree));
	manager->At(3)->AddReturn("log", 5);

	people[0].AddTask(manager->Get("make_plank"));
	people[1].AddTask(manager->Get("make_plank"));

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