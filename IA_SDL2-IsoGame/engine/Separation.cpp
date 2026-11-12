#include "Separation.hpp"

Separation::Separation(float radius): _radius(radius){}

Steering Separation::GetSteering(const Agent& agent) const
{
    Steering steering;
    Vector2 totalForce = {0,0};
    const std::vector<Agent*>& brothers = agent.GetAgents();
    //Se recorre un vector el cual se compone por todos los vecinos/hermanos.
    for (short i = 0; i < brothers.size(); i++)
    {
        //Si el hermano es el propio agent lo excluye, para que no se considere a si mismo.
        if (&agent == brothers[i])
            continue;
        else
        {
            //Calcula el vector entre la posición del propio agent y su hermano, metodo AB = B-A.
            Vector2 away = agent.position - brothers[i]->position;
            //Calculo la distancia de ese vector. 
            float dist = away.length();
            //Si dicha distancia es más pequeña que el radio minimo de separación.
            if ( dist < _radius)
            {
                //Calcula una fuerza de repulsión y se almacena en un Vector, para que todos los agent se separen la misma distancia.
                float force = (_radius - dist) / _radius;
                totalForce += away.normalized() * force;    
            }
        }
    }
    //La fuerza que devuelve es la fuerza total por la maxima fuerza del agente y se trunca para que no la supere.
    steering._linear = (totalForce * agent.maxForce).truncated(agent.maxForce);

    return steering;
}
