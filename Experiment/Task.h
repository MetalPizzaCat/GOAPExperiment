#pragma once
#include <map>
#include "Tools.h"
#include <string>
struct Requirement
{
	int Log;
	int Iron;
	int Food;
	ETools NeededTool;
};

struct Task//yes i know this is used as a class, but i use keywords sturcts for classes with data-only usage
{
	std::string Name;
	std::map<std::string, int32_t> Requirments;
	std::map<std::string, int32_t> Returns;
	//simulation of doing something by means of waiting
	//time in game ticks
	int ExecutionTime;

	Task(std::string name, int executionTime, std::map<std::string, int32_t>& requirments, std::map<std::string, int32_t>& returns) :
		Name(name),
		Requirments(std::move(requirments)),//because we don't want value duplication
		Returns(std::move(returns)),//because we don't want value duplication
		ExecutionTime(executionTime) {}

	Task(std::string name, int executionTime):
		Name(name), ExecutionTime(executionTime) {}
};
