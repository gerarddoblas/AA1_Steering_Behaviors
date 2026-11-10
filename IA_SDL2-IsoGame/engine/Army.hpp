#pragma once
#include <vector>
#include "Agent.hpp"
#include "Seek.hpp"
#include "Arrive.hpp"
#include "Separation.hpp"
#include "Cohesion.hpp"
#include "Alignment.hpp"
#include "WeightedBlending.hpp"
#include "PrioritizedList.hpp"

class Army
{
public:
	Army();
	Army(const Army&) = delete;
	Army& operator=(const Army&) = delete;
	void Update(std::vector<Agent>& _agents, float dt);

private:
	Vector2 FormationSlot(const Agent& leader, size_t i) const;

	std::vector<Agent*> _agents;
	//Steering Variables
	float _slowRadiusArrive = 250.0f;
	float _stopRadiusArrive = 20.0f;
	float _arriveEnterDist = 300.f;
	float _arriveExitDist = 350.f;
	//
	bool  _followLeader = false;   // se activa tras el primer clic
	float _leaderStopDist = 20.0f;  // distancia a la que el líder "llega"
	float _followerStopDist = 24.0f; // distancia a la que un seguidor se queda quieto
	float _slotSpacing = 90.0f;
	float _slotSideFactor = 0.8f;
	//Separation
	float _separationRadius = 80.0f;
	//Alignment
	float _alignmentRadius = 192.f;
	//Cohesion
	float _cohesionRadius = 256.f;
	//PrioritiList
	float _priorityThreshold = 1.f;
	float _emergencyRadius = 40.0f;
	//Wheights
	float _separationWeight = 1.5f;
	float _alignmentWeight = 1.0f;
	float _cohesionWeight = 0.8f;
	float _flockingWeight = 1.0f;
	float _goalWeight = 1.2f;

	//Steering behaviors
	Seek _seekBehavior;
	Arrive _arriveBehavior = { _slowRadiusArrive, _stopRadiusArrive };
	Separation _separation = { _separationRadius };
	Alignment _alignmentBehavior = { _alignmentRadius };
	Cohesion _cohesionBehavior = { _cohesionRadius };
	Separation _emergencySeparation = { _emergencyRadius };
	//WeightedBlending
	WeightedBlending _flocking;
	WeightedBlending _farBlend;
	WeightedBlending _nearBlend;
	//PrioritizedList
	PrioritizedList _farPriority{ _priorityThreshold };
	PrioritizedList _nearPriority{ _priorityThreshold };
	PrioritizedList _leaderFar{ _priorityThreshold };
	PrioritizedList _leaderNear{ _priorityThreshold };
};