#pragma once
#include "Task.h"
#include "Human.h"

class TaskCutTree : public Task
{
public:
	void Perform(Object* obj, Human* human)const override;

	TaskCutTree(std::string name, int executionTime) :
		Task(name, executionTime) {}
};

/// <summary>
/// Task for taking resources out of storage and putting them into the inventory
/// </summary>
class TaskTakeResources : public Task
{
public:
	void Perform(Object* obj, Human* human)const override;

	TaskTakeResources(std::string name, int executionTime) :
		Task(name, executionTime) {}
};

/// <summary>
/// Task for getting items from inventory and putting them into storage
/// </summary>
class TaskGiveResources : public Task
{
public:
	void Perform(Object* obj, Human* human) const override;

	TaskGiveResources(std::string name, int executionTime) :
		Task(name, executionTime) {}
};