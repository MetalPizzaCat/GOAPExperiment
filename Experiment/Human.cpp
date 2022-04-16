#include "Human.h"
#include "Barn.h"
void Human::Update(int ticks)
{
	if (!_tasks.empty())
	{
		_currentTaskExecutionCounter += ticks;
		if (_currentTaskExecutionCounter >= (*_tasks.begin())->GetExecutionTime())
		{
			_currentTaskExecutionCounter = 0;
			Task const* t = (*_tasks.begin());

			_tasks.erase(_tasks.begin());
			t->Perform(_currentTarget, this);
		}
	}
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
		for (Task const* task : _tasks)
		{
			PRINT(termcolor::yellow, task->GetName() << "->");
		}
	}
	std::cout << std::endl;
}

void Human::AddTask(Task const* task)
{
	if (!task)
		return;
	for (auto const &[name, amount] : task->GetRequirements())
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