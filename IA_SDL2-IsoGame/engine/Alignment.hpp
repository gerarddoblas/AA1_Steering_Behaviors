#pragma once
#include "SteeringBehavior.hpp"

class Alignment : public SteeringBehavior
{
public:

	Alignment(float radius);
	Steering GetSteering(const Agent& agent) const override;

private:
	float _radius;
};