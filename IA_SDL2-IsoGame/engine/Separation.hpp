#pragma once
#include "engine/SteeringBehavior.hpp"

class Separation : public SteeringBehavior
{
public:
	Separation(float radius);

	Steering GetSteering(const Agent& agent) const override;
private:
	float _radius;
};