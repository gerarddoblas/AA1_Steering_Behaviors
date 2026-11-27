#pragma once
#include "Tiles.hpp"

//Struct el qual s'encarrega de emmagatzema el contingut d'un node, posicio (Tile), prioritat i interseccio
struct Nodes
{
public:
	Tiles tile;
	float priority;
	//intersection l'utilitzo per si la prioritat es igual a un altre
	int intersection;
};