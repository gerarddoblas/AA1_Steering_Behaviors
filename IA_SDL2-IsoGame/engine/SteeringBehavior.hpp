#pragma once
#include"Steering.hpp"
#include"Agent.hpp"

class SteeringBehavior
{
public:
	virtual Steering GetSteering(const Agent& agent) const = 0;
};