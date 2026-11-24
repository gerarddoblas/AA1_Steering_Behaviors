#include"vector"
#include "Tiles.hpp"

struct PathFindingResult
{
public:
	bool isFound = false;
	std::vector<Tiles> _path;
	int _cost = 0;
	std::vector<Tiles> _exploredNodes;
	float time;

};