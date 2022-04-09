#pragma once
#include <vector>
#include "Task.h"

class TaskManager
{
private:
	std::vector<Task*> _tasks;
public:
	bool Add(Task* task);
	//Get task by name
	//value is returned as const to avoid accidental modifications to value
	Task const* operator[](std::string const&  name);

	//Get task by name
	//value is returned as const to avoid accidental modifications to value
	Task const* Get(std::string const&  name);

	Task * At(int id);
};