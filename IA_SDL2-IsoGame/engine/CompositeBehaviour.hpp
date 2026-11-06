#pragma once
#include "engine/SteeringBehavior.hpp"
#include <list>
class Separation : public SteeringBehavior
{
public:
	void Add(SteeringBehavior steering);
	void Remove(SteeringBehavior steering);
	virtual Steering GetSteering(Agent agent) override;
protected:
	std::list<SteeringBehavior> _children;
};