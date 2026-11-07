#include "WeightedBlending.hpp"

void WeightedBlending::Add(SteeringBehavior* steering)
{
	if(steering != nullptr)
	{
		CompositeBehavior::Add(steering);
		_weights.push_back(1.0f);
	}
}

void WeightedBlending::Add(SteeringBehavior* steering, float weight)
{
	if(steering != nullptr)
	{
		CompositeBehavior::Add(steering);
		_weights.push_back(weight);
	}
}

void WeightedBlending::Remove(SteeringBehavior* steering)
{
	//
	std::vector<SteeringBehavior*>::iterator it = std::find(_children.begin(), _children.end(), steering);
	//
	if (it == _children.end())
		return;
	//
	int index = it - _children.begin();
	_children.erase(it);
	_weights.erase(_weights.begin() + index);
}

void WeightedBlending::SetWeight(SteeringBehavior* steering, float weight)
{
	//
	std::vector<SteeringBehavior*>::iterator it = std::find(_children.begin(), _children.end(), steering);
	//
	if (it == _children.end())
		return;
	//
	int index = it - _children.begin();
	_weights[index] = weight;
}

Steering WeightedBlending::GetSteering(const Agent& agent) const
{
	Steering result;

	for (int i = 0; i < _children.size(); i++)
	{
		//
		result += _children[i]->GetSteering(agent) * _weights[i];
	}
	//
	return result.truncated(agent.maxForce);
}