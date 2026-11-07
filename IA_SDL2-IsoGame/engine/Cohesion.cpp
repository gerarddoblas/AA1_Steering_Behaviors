#include "Cohesion.hpp"

Cohesion::Cohesion(float radius) :_radius(radius) {}

Steering Cohesion::GetSteering(const Agent& agent) const
{
    //
    Steering steering;
    Vector2 totalPosition = { 0,0 };
    short minionsCount = 0;
    const std::vector<Agent*>& brothers = agent.GetAgents();
    //
    for (short i = 0; i < brothers.size(); i++)
    {
        if (&agent == brothers[i])
            continue;
        else
        {
            //
            Vector2 awayPosition = agent.position - brothers[i]->position;
            //
            float dist = awayPosition.length();
            //
            if (dist < _radius)
            {
                totalPosition += brothers[i]->position;
                minionsCount++;
            }
        }
    }
    //
    if (minionsCount == 0)
        return steering;
    //
    Vector2 minionsCenter = totalPosition.operator/(minionsCount);
	Vector2 speed = (minionsCenter - agent.position).normalized() * agent.maxSpeed;

	steering._linear = (speed - agent.velocity).truncated(agent.maxForce);

    return steering;
}