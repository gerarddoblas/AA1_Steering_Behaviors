#include "Separation.hpp"

Separation::Separation(float radius): _radius(radius){}

Steering Separation::GetSteering(const Agent& agent) const
{
    Steering steering;
    Vector2 totalForce = {0,0};
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
            if ( dist < _radius)
            {
                float force = (_radius - dist) / _radius;
                totalForce += away.normalized() * force;

                
            }
        }
    }
    steering._linear = (totalForce * agent.maxForce).truncated(agent.maxForce);

    return steering;
}
