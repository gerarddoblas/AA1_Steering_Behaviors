#pragma once
#include "engine/SteeringBehavior.hpp"

class Arrive : public SteeringBehavior
{
public:
	Arrive(float slowRadius, float stopRadius);
	Steering GetSteering(const Agent& agent) const override;

private:
	float _slowRadius;
	float _stopRadius;
};