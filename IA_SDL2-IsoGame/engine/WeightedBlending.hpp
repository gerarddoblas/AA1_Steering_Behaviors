#pragma once
#include "CompositeBehavior.hpp"

class WeightedBlending : public CompositeBehavior
{
public:
	//
	void Add(SteeringBehavior* steering) override;
	void Add(SteeringBehavior* steering, float weight);
	void Remove(SteeringBehavior* steering) override;
	void SetWeight(SteeringBehavior* steering, float weight);
	Steering GetSteering(const Agent& agent) const override;

private:
	std::vector<float> _weights;

};