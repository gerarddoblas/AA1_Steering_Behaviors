#include "Army.hpp"
#include <iostream>

Army::Army()
{
	//
	_flocking.Add(&_separation, _separationWeight);
	_flocking.Add(&_alignmentBehavior, _alignmentWeight);
	_flocking.Add(&_cohesionBehavior, _cohesionWeight);

	//
	_farBlend.Add(&_flocking, _flockingWeight);
	_farBlend.Add(&_seekBehavior, _goalWeight);

	_nearBlend.Add(&_flocking, _flockingWeight);
	_nearBlend.Add(&_arriveBehavior, _goalWeight);

	//
	_farPriority.Add(&_emergencySeparation);
	_farPriority.Add(&_farBlend);
	//
	_nearPriority.Add(&_emergencySeparation);
	_nearPriority.Add(&_nearBlend);
}

void Army::Update(std::vector<Agent>& agents, float dt)
{
	_agents.clear();
    //
    for (Agent& agent : agents)
    {
        _agents.push_back(&agent);
    }
    //
    for (Agent& agent : agents)
    {
        agent.SetAgents(_agents);
    }
    //
	Agent& leader = agents[0];

	if (leader.hasTarget)
	{
		_followLeader = true;   // ya hubo un clic, los seguidores pueden seguirlo

		float leaderDist = (leader.target - leader.position).length();
		if (leaderDist < _leaderStopDist)
			leader.hasTarget = false;
	}
	//
	for (size_t i = 1; i < agents.size(); ++i)
	{
		Agent& follower = agents[i];

		if (!_followLeader)
		{
			follower.hasTarget = false;
			continue;
		}

		float d = (leader.position - follower.position).length();
		if (d < _followerStopDist)
		{
			follower.hasTarget = false;
		}
		else
		{
			follower.target = leader.position;
			follower.hasTarget = true;
		}
	}
	for (Agent& agent : agents)
	{
		//

		if (agent.GetSteering() == nullptr)
			agent.SetSteering(&_farPriority);

		if (!agent.hasTarget)
			continue;

		float dist = (agent.target - agent.position).length();

		//
		if (agent.GetSteering() == &_farPriority && dist < _arriveEnterDist)
		{
			agent.SetSteering(&_nearPriority);
			std::cout << "lejos -> cerca (dist " << dist << ")\n";
		}
		else if (agent.GetSteering() == &_nearPriority && dist > _arriveExitDist)
		{
			agent.SetSteering(&_farPriority);
			std::cout << "cerca -> lejos (dist " << dist << ")\n";
		}
	}
	std::cout << leader.hasTarget << std::endl;
}
