#include "Seek.hpp"

Steering Seek::GetSteering(const Agent& agent) const
{
    //
    if (!agent.hasTarget)
        return Steering();

    Steering steering;
    //
    Vector2 dir = ((agent.target - agent.position).normalized()) * agent.maxSpeed;
    //
    steering._linear = (dir - agent.velocity).truncated(agent.maxForce);

    return steering;

}
