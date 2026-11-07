#include "Alignment.hpp"

Alignment::Alignment(float radius) : _radius(radius){}

Steering Alignment::GetSteering(const Agent& agent) const
{
    //
    Steering steering;
    Vector2 totalVelocity = { 0,0 };
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
            Vector2 NeighborPosition = agent.position - brothers[i]->position;
            //
            float dist = NeighborPosition.length();
            //
            if (dist < _radius)
            {
                totalVelocity += brothers[i]->velocity;
                minionsCount++;
            }
        }
    }
    //
    if (minionsCount == 0)
        return steering;
    //
    Vector2 averageVelocity = totalVelocity.operator/(minionsCount);

    steering._linear = (averageVelocity - agent.velocity).truncated(agent.maxForce);

    return steering;
}
