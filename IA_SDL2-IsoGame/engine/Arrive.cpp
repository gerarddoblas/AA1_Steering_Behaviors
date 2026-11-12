#include "Arrive.hpp"

Arrive::Arrive(float slowRadius, float stopRadius) : _slowRadius(slowRadius), _stopRadius(stopRadius) {}

Steering Arrive::GetSteering(const Agent& agent) const
{
    if(!agent.hasTarget)
        return Steering();

    Steering steering;
    //Calcula la dirección y la distancia del target hacia el agente, metodo AB = B - A.
    Vector2 target = agent.target - agent.position;
    float dis = target.length();
    Vector2 dir = target.normalized();
    //Dependiendo de la distancia la velocidad o es cero porque su radio ya le indica que esta cerca y se puede parar
    //o si es más pequeña o igual al radio de ralentización su velocidad se reduce, si no es la velocidad maxima.
    float speed;
    if (dis <= _stopRadius)
        speed = 0;
    else if (dis <= _slowRadius)
        speed = (agent.maxSpeed * dis) / _slowRadius;
    else
        speed = agent.maxSpeed;

    //La fuerza es la velocidad deseada menos la velocidad actual del agente, truncada a su fuerza maxima.
    steering._linear = ((dir * speed) - agent.velocity).truncated(agent.maxForce);

    return steering;
}
