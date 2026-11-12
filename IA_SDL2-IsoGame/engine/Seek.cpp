#include "Seek.hpp"

Steering Seek::GetSteering(const Agent& agent) const
{
    //Si el agent no tiene target, es decir, no tiene a donde ir no se mueve, le retorna un Steering vacio.
    if (!agent.hasTarget)
        return Steering();

    Steering steering;
    //Calculo la velocidad deseada entre la posición del agente y la del objetivo, es decir, el metodo AB = B - A, por la velocidad maxima del agente.
    //Es decir, calculo la velocidad deseada que tendría el agente si fuera a velocidad maxima hacia el objetivo
    Vector2 dir = ((agent.target - agent.position).normalized()) * agent.maxSpeed;
    //La fuerza del agente se convierte en la velocidad deseada menos la actual velocidad del agente, truncado a su maxima fuerza.
    steering._linear = (dir - agent.velocity).truncated(agent.maxForce);

    return steering;

}
