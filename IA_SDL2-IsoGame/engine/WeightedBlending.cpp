#include "WeightedBlending.hpp"

void WeightedBlending::Add(SteeringBehavior* steering)
{
	if(steering != nullptr)
	{
		CompositeBehavior::Add(steering);
		_weights.push_back(1.0f);
	}
}

void WeightedBlending::Add(SteeringBehavior* steering, float weight)
{
	if(steering != nullptr)
	{
		CompositeBehavior::Add(steering);
		_weights.push_back(weight);
	}
}

void WeightedBlending::Remove(SteeringBehavior* steering)
{
	//Busco el puntero steering en el vector del composite con find
	//find lo que hace es buscar entre un inicio y un final un valor que sea el mismo al que se le pasa a la función.
	//Ej: std::find(la posición desde donde empieza, la posición a la que termina, el valor que tiene que encontrar);
	std::vector<SteeringBehavior*>::iterator it = std::find(_children.begin(), _children.end(), steering);
	//Si no lo encuentra el iterador it terminara en el final, es decir, como no hay comparación se saldra del metodo,
	//hay que aclarar que find devuelve end cuando no encuentra nada.
	if (it == _children.end())
		return;
	//Creo un indice el cual será el iterador, menos el inicio del vector para encontrar la posición
	//Luego borro dicha posición en el vector del composite y el de peso, para estar sincronizados
	int index = it - _children.begin();
	_children.erase(it);
	_weights.erase(_weights.begin() + index);
}

void WeightedBlending::SetWeight(SteeringBehavior* steering, float weight)
{
	//Busco el puntero steering en el vector del composite con find
	//find lo que hace es buscar entre un inicio y un final un valor que sea el mismo al que se le pasa a la función.
	//Ej: std::find(la posición desde donde empieza, la posición a la que termina, el valor que tiene que encontrar);
	std::vector<SteeringBehavior*>::iterator it = std::find(_children.begin(), _children.end(), steering);
	//Si no lo encuentra el iterador it terminara en el final, es decir, como no hay comparación se saldra del metodo,
	//hay que aclarar que find devuelve end cuando no encuentra nada.
	if (it == _children.end())
		return;
	//Creo un indice el cual será el iterador, menos el inicio del vector para encontrar la posición
	//Luego borro dicha posición en el vector del composite y el de peso, para estar sincronizados
	int index = it - _children.begin();
	_weights[index] = weight;
}

Steering WeightedBlending::GetSteering(const Agent& agent) const
{
	Steering result;

	for (int i = 0; i < _children.size(); i++)
	{
		//Calculo el steering final del agente combinado con todos los hijos,
		//Se almacena todos los steering multiplicados por sus pesos
		//Cada Steering tiene una fuerza, con los operadores se suman estás fuerzas en una sola
		//y la fuerza que queda es aquella se pone en la velocidad y posición.
		result += _children[i]->GetSteering(agent) * _weights[i];
	}
	//Para evitar que el agente salga disparado se trunca dicha fuerza con tal de no superar un maximo.
	return result.truncated(agent.maxForce);
}

void WeightedBlending::Clear() {
	_weights.clear(); 
}