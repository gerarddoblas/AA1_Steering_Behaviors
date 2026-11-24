#include"World.hpp"
#include"Tiles.hpp"
#include"PathFindingResult.hpp"
#include"vector"


class PathFinding
{
public:
	std::vector<Tiles> _path;
	std::vector<Tiles> _exploredPath;

	PathFindingResult _result;

	PathFindingResult Find(Tiles start, Tiles objective, World& world);
};