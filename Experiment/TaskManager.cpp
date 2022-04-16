#include "TaskManager.h"

bool TaskManager::Add(Task* task)
{
	std::vector<Task*>::iterator it = std::ranges::find_if(_tasks.begin(), _tasks.end(), [task](Task const* cur_task) {return cur_task->GetName() == task->GetName(); });
	if (it == _tasks.end())
	{
		_tasks.push_back(task);
		return true;
	}
	return false;
}

Task const* TaskManager::operator[](std::string const& name)
{
	for (Task*& task : _tasks)
	{
		if (task->GetName() == name)
		{
			return task;
		}
	}
	return nullptr;
}

Task const* TaskManager::Get(std::string const& name)
{
	for (Task*& task : _tasks)
	{
		if (task->GetName() == name)
		{
			return task;
		}
	}
	return nullptr;
}

Task * TaskManager::At(int id)
{
	if (id >= 0 && id < _tasks.size())
	{
		return _tasks[id];
	}
	return nullptr;
}
