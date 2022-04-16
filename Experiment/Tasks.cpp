#include "Tasks.h"
#include "Tree.h"
#include "Human.h"
#include "Barn.h"
void TaskCutTree::Perform(Object* _currentTarget, Human* human) const
{
	if (Tree* tree = dynamic_cast<Tree*>(_currentTarget); tree)
	{
		tree->TakeLogs(tree->GetLogCount() >= 5 ? 5 : tree->GetLogCount());
	}
}

void TaskTakeResources::Perform(Object* _currentTarget, Human* human) const
{
	if (Barn* barn = dynamic_cast<Barn*>(_currentTarget); barn)//we can only take items out of target
	{
		//on task completion we give all returns back to world and take all needs
		//ideally you'd have mini inventory system to avoid making ai constantly walk back and forth
		//but for simplicity let's say ai always gives everything they have to the "super-barn" as soon as they make it
		for (auto const& [name, value] : _requirements)
		{
			//take required task items from whatever was the target
			barn->RemoveResource(name, value);
			//_world->Add(name, -value);
		}
	}
	else
	{
		//we can't take resources from a place that doesn't have resources
		//so we need to add this task back but with new goal
		//however technically this should not happen as _currentTarget being correct *should* be insured during task assigment
	}
}
