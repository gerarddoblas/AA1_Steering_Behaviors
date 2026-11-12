#include "Alignment.hpp"

Alignment::Alignment(float radius) : _radius(radius){}

Steering Alignment::GetSteering(const Agent& agent) const
{
    //Se crea un minionsCount para saber cuantos hermanos son los que se van a mover a la misma velocidad.
    Steering steering;
    Vector2 totalVelocity = { 0,0 };
    short minionsCount = 0;
    const std::vector<Agent*>& brothers = agent.GetAgents();
    //Recorre a todos los hermanos ignorandose a si mismo
    for (short i = 0; i < brothers.size(); i++)
    {
        if (&agent == brothers[i])
            continue;
        else
        {
            //Se calcula la dirección del agente, con el metodo AB = B - A.
            Vector2 NeighborPosition = agent.position - brothers[i]->position;
            //La distancia de la dirección
            float dist = NeighborPosition.length();
            //Si la distancai es más pequeña que el radio se almacena la velocidad y el numero de minion para calcular le media de velocidad.
            if (dist < _radius)
            {
                totalVelocity += brothers[i]->velocity;
                minionsCount++;
            }
        }
    }
    //Si no tiene vecinos retorna un steering vacio
    if (minionsCount == 0)
        return steering;
    //Se calcula la velocidad media deseada a la que tiene que ir el minion.
    Vector2 averageVelocity = totalVelocity.operator/(minionsCount);

    steering._linear = (averageVelocity - agent.velocity).truncated(agent.maxForce);

    return steering;
}
