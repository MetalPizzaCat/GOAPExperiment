#include "Tasks.h"
#include "Tree.h"
#include "Human.h"
#include "Barn.h"
bool TaskCutTree::Perform(Object* _currentTarget, Human* human, TaskData& data) const
{
	if (Tree* tree = dynamic_cast<Tree*>(_currentTarget); tree)
	{
		if (tree->GetLogCount() < 5)
			return false;
		tree->TakeLogs(5);
		return true;
	}
	return false;
}

bool TaskTakeResources::Perform(Object* _currentTarget, Human* human, TaskData& data) const
{
	if (Barn* barn = dynamic_cast<Barn*>(_currentTarget); barn && data.TaskResourceData)//we can only take items out of target
	{
		//try to take needed resource from the barn and if unable give new task of getting it from somewhere else
		//right now system doesn't fail tasks, but if it would it should notify of task failure rather then give new one

		std::string& name = data.TaskResourceData->Name;
		int32_t& value = data.TaskResourceData->Amount;

		if (barn->GetResource(name) >= value)
		{
			barn->RemoveResource(name, value);
			human->AddResource(name, value);
		}
		else
		{
			const int32_t amount = barn->GetResource(name) - value;
			human->AddResource(name, amount);
			barn->RemoveResource(name, amount);
			//since there are not enough resources for us we need to get some
			human->AddTask("get_" + name, new Resource{ name, amount });
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
