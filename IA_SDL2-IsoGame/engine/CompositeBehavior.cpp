#include "CompositeBehavior.hpp"

void CompositeBehavior::Add(SteeringBehavior* steering)
{
	if(steering != nullptr)
		_children.push_back(steering);
}

void CompositeBehavior::Remove(SteeringBehavior* steering)
{
	//
	_children.erase(std::remove(_children.begin(), _children.end(), steering), _children.end());
}
