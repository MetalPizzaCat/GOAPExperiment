#include "Tasks.h"
#include "Tree.h"
#include "Human.h"
#include "Barn.h"
bool TaskCutTree::Perform(Object* _currentTarget, Human* human) const
{
	if (Tree* tree = dynamic_cast<Tree*>(_currentTarget); tree)
	{
		if (tree->GetLogCount() < 5)
			return false;
		tree->TakeLogs(5);
		return true;
	}
}

bool TaskTakeResources::Perform(Object* _currentTarget, Human* human) const
{
	if (Barn* barn = dynamic_cast<Barn*>(_currentTarget); barn)//we can only take items out of target
	{
		//on task completion we give all returns back to world and take all needs
		//ideally you'd have mini inventory system to avoid making ai constantly walk back and forth
		//but for simplicity let's say ai always gives everything they have to the "super-barn" as soon as they make it
		for (auto const& [name, value] : *_requirements)
		{
			if (barn->GetResource(name) >= value)
			{
				barn->RemoveResource(name, value);
			}
		}
	}
	else
	{
		//we can't take resources from a place that doesn't have resources
		//so we need to add this task back but with new goal
		//however technically this should not happen as _currentTarget being correct *should* be insured during task assigment
	}
	return true;
}
