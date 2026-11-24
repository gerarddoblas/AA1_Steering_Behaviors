#include"vector"
#include "Tiles.hpp"

//Aquest struct existeix principalment perque els Paths han retornar varies coses
struct PathFindingResult
{
public:
	bool isFound = false;
	//Vector que guarda especificament el cami optim
	std::vector<Tiles> _path;
	//El cost dle resultat
	int _cost = 0;
	//El numero total de nodes explorats
	int _exploredNodes;
	float time;
	//Vector que guarda totes les caselles explorades, aixo hi es principalment per a debug.
	std::vector<Tiles> _explorationOrder;
};