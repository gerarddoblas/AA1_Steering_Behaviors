#include "Cohesion.hpp"

Cohesion::Cohesion(float radius) :_radius(radius) {}

Steering Cohesion::GetSteering(const Agent& agent) const
{
    //
    Steering steering;
    Vector2 totalPosition = { 0,0 };
    short minionsCount = 0;
    const std::vector<Agent*> brothers = agent.GetAgents();
    //
    for (short i = 0; i < brothers.size(); i++)
    {
        if (&agent == brothers[i])
            continue;
        else
        {
            //
            Vector2 away = agent.position - brothers[i]->position;
            //
            float dist = away.length();
            //
            if (dist < _radius)
            {
                totalPosition += brothers[i]->position;
                minionsCount++;


            }
        }
    }
    if (minionsCount == 0)
    {
        return steering;
    }

    //float minonsCenter = totalPosition.operator/(minionsCount);
}