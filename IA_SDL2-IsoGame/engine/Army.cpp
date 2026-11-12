#include "Army.hpp"
#include <cmath>

Army::Army()
{
	//Añado los Steerings con su peso en un WeightedBlending, es decir, la mezcla de las 3 reglas de Reynold
	_flocking.Add(&_separation, _separationWeight);
	_flocking.Add(&_alignmentBehavior, _alignmentWeight);
	_flocking.Add(&_cohesionBehavior, _cohesionWeight);

	//Creo 2 WeightedBlending, uno para cuando el jugador este en seek y otro para cuando este en Arrive
	//Añado en ambos WeightedBlending el anterior, es decir, un flocking.
	//También, un peso para decidir si esta en arrive o en seek.
	_farBlend.Add(&_flocking, _flockingWeight);
	_farBlend.Add(&_seekBehavior, _goalWeight);

	_nearBlend.Add(&_flocking, _flockingWeight);
	_nearBlend.Add(&_arriveBehavior, _goalWeight);

	//Luego añado en una PrioritizedList el WeightedBlending de lejos y un limite de emergencia para que se llame a un Separation
	_farPriority.Add(&_emergencySeparation);
	_farPriority.Add(&_farBlend);
	//Luego añado en una PrioritizedList el WeightedBlending de cerca y un limite de emergencia para que se llame a un Separation
	_nearPriority.Add(&_emergencySeparation);
	_nearPriority.Add(&_nearBlend);
	//Una PrioritizedList basica para el Lider, tanto de lejos como de cerca
	_leaderFar.Add(&_emergencySeparation);
	_leaderFar.Add(&_seekBehavior);

	_leaderNear.Add(&_emergencySeparation);
	_leaderNear.Add(&_arriveBehavior);
}

Vector2 Army::FormationSlot(const Agent& leader, size_t i) const
{
	const float row = (float)((i + 1) / 2);
	const float side = (i % 2 == 1) ? -1.0f : 1.0f;

	const Vector2 forward(std::cos(leader.heading), std::sin(leader.heading));
	const Vector2 right(-forward.y, forward.x);

	return leader.position
		- forward * (row * _slotSpacing)
		+ right * (side * row * _slotSpacing * _slotSideFactor);
}

void Army::Update(std::vector<Agent>& agents, float dt)
{
	(void)dt;
	if (agents.empty())
		return;

	_agents.clear();
	//Se limpia el vector de Agents para que no de problemas y se vuelve a regenar
	for (Agent& agent : agents)
	{
		_agents.push_back(&agent);
	}
	//Luego a cada agent se le añade el vector de agents anteriormente rellenado
	for (Agent& agent : agents)
	{
		agent.SetAgents(_agents);
	}
	//Se asigna un lider
	Agent& leader = agents[0];

	if (leader.hasTarget)
	{
		_followLeader = true;   // ya hubo un clic, los seguidores pueden seguirlo

		float leaderDist = (leader.target - leader.position).length();
		if (leaderDist < _leaderStopDist)
		{
			leader.hasTarget = false;
			leader.velocity = Vector2(0.0f, 0.0f);
		}
	}
	//Se el asigna el seguir al lider si este a hecho un click, si no se iran a la formación si detectan que están lo suficientemente cerca de otros minions.
	for (size_t i = 1; i < agents.size(); ++i)
	{
		Agent& follower = agents[i];

		if (!_followLeader)
		{
			follower.hasTarget = false;
			continue;
		}

		Vector2 slot = FormationSlot(leader, i);
		float d = (slot - follower.position).length();
		if (d < _followerStopDist)
		{
			follower.hasTarget = false;
		}
		else
		{
			follower.target = slot;
			follower.hasTarget = true;
		}
	}
	for (size_t i = 0; i < agents.size(); ++i)
	{
		Agent& agent = agents[i];
		SteeringBehavior* far = (i == 0) ? (SteeringBehavior*)&_leaderFar : (SteeringBehavior*)&_farPriority;
		SteeringBehavior* near = (i == 0) ? (SteeringBehavior*)&_leaderNear : (SteeringBehavior*)&_nearPriority;
		//Se eligen lalista del lider y la de los seguidores

		if (agent.GetSteering() == nullptr)
			agent.SetSteering(far);

		if (!agent.hasTarget)
			continue;

		float dist = (agent.target - agent.position).length();

		//Si el actual steering del agente es uno de lejos y la distancia es más pequeña que al marjen de arrive pasa a usar arrive y viceversa
		if (agent.GetSteering() == far && dist < _arriveEnterDist)
		{
			agent.SetSteering(near);
		}
		else if (agent.GetSteering() == near && dist > _arriveExitDist)
		{
			agent.SetSteering(far);
		}
	}
}

void Army::ExaggerateSeek(float factor) {
	ResetWeights();
	_goalWeight *= factor;

	// Recreamos el farBlend asignándole los nuevos valores directamente
	_farBlend = WeightedBlending();
	_farBlend.Add(&_flocking, _flockingWeight);
	_farBlend.Add(&_seekBehavior, _goalWeight);
}

void Army::ExaggerateArrive(float factor) {
	ResetWeights();
	_slowRadiusArrive *= factor;
	_goalWeight *= factor;

	// Actualizamos el Arrive con el nuevo radio de frenado
	_arriveBehavior = Arrive{ _slowRadiusArrive, _stopRadiusArrive };

	_nearBlend = WeightedBlending();
	_nearBlend.Add(&_flocking, _flockingWeight);
	_nearBlend.Add(&_arriveBehavior, _goalWeight);
}

void Army::ExaggerateSeparation(float factor) {
	ResetWeights();
	_separationWeight *= factor;
	_separationRadius *= factor;

	// Actualizamos el comportamiento de separación con el nuevo radio
	_separation = Separation{ _separationRadius };

	_flocking = WeightedBlending();
	_flocking.Add(&_separation, _separationWeight);
	_flocking.Add(&_alignmentBehavior, _alignmentWeight);
	_flocking.Add(&_cohesionBehavior, _cohesionWeight);
}

void Army::ExaggerateAlignment(float factor) {
	ResetWeights();
	_alignmentWeight *= factor;

	_flocking = WeightedBlending();
	_flocking.Add(&_separation, _separationWeight);
	_flocking.Add(&_alignmentBehavior, _alignmentWeight);
	_flocking.Add(&_cohesionBehavior, _cohesionWeight);
}

void Army::ExaggerateCohesion(float factor) {
	ResetWeights();
	_cohesionWeight *= factor;

	_flocking = WeightedBlending();
	_flocking.Add(&_separation, _separationWeight);
	_flocking.Add(&_alignmentBehavior, _alignmentWeight);
	_flocking.Add(&_cohesionBehavior, _cohesionWeight);
}

void Army::ResetWeights() {
	_separationWeight = 1.5f;
	_alignmentWeight = 1.0f;
	_cohesionWeight = 0.8f;
	_flockingWeight = 1.0f;
	_goalWeight = 1.2f;
	_slowRadiusArrive = 250.0f;
	_stopRadiusArrive = 20.0f;
	_separationRadius = 80.0f;
	_alignmentRadius = 192.f;
	_cohesionRadius = 256.f;

	// Reinicializamos los comportamientos a sus radios originales
	_arriveBehavior = Arrive{ _slowRadiusArrive, _stopRadiusArrive };
	_separation = Separation{ _separationRadius };

	// Recreamos los blends limpios desde cero
	_flocking = WeightedBlending();
	_flocking.Add(&_separation, _separationWeight);
	_flocking.Add(&_alignmentBehavior, _alignmentWeight);
	_flocking.Add(&_cohesionBehavior, _cohesionWeight);

	_farBlend = WeightedBlending();
	_farBlend.Add(&_flocking, _flockingWeight);
	_farBlend.Add(&_seekBehavior, _goalWeight);

	_nearBlend = WeightedBlending();
	_nearBlend.Add(&_flocking, _flockingWeight);
	_nearBlend.Add(&_arriveBehavior, _goalWeight);
}