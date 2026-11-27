#pragma once
#include "Tiles.hpp"

//Struct el qual s'encarrega de emmagatzema el contingut d'un node, posicio (Tile), prioritat i interseccio
struct Node
{
public:
	Tiles tile;
	float priority;
	//intersection l'utilitzo per si la prioritat es igual a un altre
	int intersection;

	bool operator<(const Node& node) const
	{ 
		if (this->priority != node.priority)
			return (this->priority > node.priority);
		return (this->intersection > node.intersection);
	}
};