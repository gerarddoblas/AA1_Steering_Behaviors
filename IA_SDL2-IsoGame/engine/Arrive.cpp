#include "Arrive.hpp"

Steering Arrive::GetSteering(const Agent& agent) const
{
    if(!agent.hasTarget)
        return Steering();

    Steering steering;
    //
    Vector2 target = agent.target - agent.position;
    float dis = target.length();
    Vector2 dir = target.normalized();
    //
    float speed;
    if (dis <= _stopRadius)
        speed = 0;
    else if (dis <= _slowRadius)
        speed = (agent.maxSpeed * dis) / _slowRadius;
    else
        speed = agent.maxSpeed;

    //
    steering._linear = ((dir * speed) - agent.velocity).truncated(agent.maxForce);

    return steering;
}
