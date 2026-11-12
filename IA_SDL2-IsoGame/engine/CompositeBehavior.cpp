#include "CompositeBehavior.hpp"

void CompositeBehavior::Add(SteeringBehavior* steering)
{
	if(steering != nullptr)
		_children.push_back(steering);
}

void CompositeBehavior::Remove(SteeringBehavior* steering)
{
	//Remove remueve todos los SteeringBehavior hacia el final que coincidan con el elemento pasado, en este caso el steering
	//Luego eras borra esos elementos que sobran.
	//Se puede poner el remove, porque su última posición termina siendo el inicio a Steeringbehavior a remover.
	_children.erase(std::remove(_children.begin(), _children.end(), steering), _children.end());
}
