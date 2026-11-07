#include "PrioritizedList.hpp"

PrioritizedList::PrioritizedList(float threshold) : _threshold(threshold) {}

Steering PrioritizedList::GetSteering(const Agent& agent) const
{
	for (int i = 0; i < _children.size(); i++)
	{
		Steering steering = _children[i]->GetSteering(agent);

		if(steering.magnitude()> _threshold)
		{
			return steering.truncated(agent.maxForce);
		}
	}

	return Steering();
}

void PrioritizedList::SetThreshold(float threshold)
{
	_threshold = threshold;
}
