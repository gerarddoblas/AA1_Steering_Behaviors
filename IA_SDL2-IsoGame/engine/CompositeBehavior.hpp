#pragma once
#include "SteeringBehavior.hpp"
class CompositeBehavior : public SteeringBehavior
{
public:
	virtual void Add(SteeringBehavior* steering);
	virtual void Remove(SteeringBehavior* steering);
protected:
	std::vector<SteeringBehavior*> _children;
};