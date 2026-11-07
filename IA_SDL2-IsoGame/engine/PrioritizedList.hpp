#pragma once
#include "CompositeBehavior.hpp"

class PrioritizedList : public CompositeBehavior
{
public:
	PrioritizedList(float threshold);
	Steering GetSteering(const Agent& agent) const override;
	void SetThreshold(float threshold);
protected:
	float _threshold;

};