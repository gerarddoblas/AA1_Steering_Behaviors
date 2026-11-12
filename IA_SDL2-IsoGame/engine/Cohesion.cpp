#include "Cohesion.hpp"

Cohesion::Cohesion(float radius) :_radius(radius) {}

Steering Cohesion::GetSteering(const Agent& agent) const
{
    //Se crea un minionsCount para saber cuantos hermanos son los que se van a dirigir al centro.
    Steering steering;
    Vector2 totalPosition = { 0,0 };
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
            Vector2 awayPosition = agent.position - brothers[i]->position;
            //La distancia de la dirección
            float dist = awayPosition.length();
            //Se añaden al calculo del centro de masas solo los minions que estén más cerca del radio
            //De esta forma se acercan al centro de lo vecions y no se dirigen a un punto fijo, el cual sería el centro de todo el grupo.
            if (dist < _radius)
            {
                totalPosition += brothers[i]->position;
                minionsCount++;
            }
        }
    }
    //Si no tiene vecinos retorna un steering vacio
    if (minionsCount == 0)
        return steering;
    //Se calcula la media de las posiciones de los hermanos, es decir, se coge la posición total de los minions y se dividie entre el numero total.
    Vector2 minionsCenter = totalPosition.operator/(minionsCount);
	Vector2 speed = (minionsCenter - agent.position).normalized() * agent.maxSpeed;

	steering._linear = (speed - agent.velocity).truncated(agent.maxForce);

    return steering;
}