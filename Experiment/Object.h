#pragma once
#include <cmath>

struct Point
{
	int32_t x, y;
	int DistanceSq(Point const&p1) const
	{
		return (x - p1.x) * (x - p1.x) + (y - p1.y) * (y - p1.y);
	}

	float Distance(Point const& p1) const
	{
		return std::sqrt((x - p1.x) * (x - p1.x) + (y - p1.y) * (y - p1.y));
	}
};

/// <summary>
/// This enum describes all of the classes present in the project
/// This is not the best idea but it will simplify type checking
/// </summary>
enum EObjectType
{
	EOT_Object,
	EOT_Tree,
	EOT_Barn,
	EOT_Human
};

class Object
{
private:
	Point _location;
	
public:
	//type of the class
	static const EObjectType ClassType = EOT_Object;
	//current type of the object
	virtual constexpr EObjectType Type() { return EOT_Object; };
	Point GetLocation()const { return _location; }
	Point SetLocation(Point p) { _location = p; }

	virtual void Update(int32_t deltaTicks) {}
	virtual ~Object() = default;
};