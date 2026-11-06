#pragma once
#include "engine/SteeringBehavior.hpp"

class Cohesion : public SteeringBehavior
{
public:
	Cohesion(float radius);
	Steering GetSteering(const Agent& agent) const override;
private:
	float _radius;
};