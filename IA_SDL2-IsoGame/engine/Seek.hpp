#pragma once
#include "engine/SteeringBehavior.hpp"

class Seek : public SteeringBehavior
{
public:
	Steering GetSteering(const Agent& agent) const override;
};