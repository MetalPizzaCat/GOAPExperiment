#pragma once
#include "Object.h"
/// <summary>
/// Tree is a simple object that can be used for logs
/// Regenerates log count over time
/// </summary>
class Tree : public Object
{
private:
	/// <summary>
	/// Every this amount of ticks new log will be added back to log count
	/// </summary>
	int32_t _regenerationRate = 2;
	int32_t _logCount = 5;
	int32_t _tickCount = 0;
public:
	//type of the class
	static const EObjectType ClassType = EOT_Barn;

	virtual constexpr EObjectType Type() { return EOT_Tree; };
	void Update(int32_t deltaTicks)override
	{
		if (++_tickCount > _regenerationRate)
		{
			_logCount++;
			_tickCount = 0;
		}
	}
	
	int32_t GetLogCount()const { return _logCount; }
	/// <summary>
	/// Take some logs from the tree. Try to take more then there is will set count to 0.
	/// To check if there are enough logs to take use GetLogCount()
	/// </summary>
	/// <param name="amount">How many to take</param>
	/// <returns>amount of logs left</returns>
	int32_t TakeLogs(int32_t amount) { return _logCount -= (amount <= _logCount) ? _logCount : amount; }
};

