#include "PathFinding.hpp"

PathFindingResult PathFinding::Find(Tiles start,Tiles objective, World& world)
{
    short x = 0;
    short y = 0;
    bool isDiagonal;
    bool isFound = false;
    //Buscant les caselles adyacents
    for (short dx = -1; dx <= 1; dx++)
    {
        for (short dy = -1; dy <= 1; dy++)
        {
            isDiagonal = (dx != 0 && dy != 0);
            //Ignorem la posicio inicial
            if (dx == 0 && dy == 0)
                continue;
            //Assignem la posicio adyacent
            short ax = x + dx;
            short ay = y + dy;

            //Si no es transitable
            if (!world.isWalkable(ax, ay))
                continue;
            //Si la opció transitable es diagonal i alguna de les posicions ortogonals no es transitable
            if ((isDiagonal) && (!world.isWalkable(ax,y) || !world.isWalkable(x, ay)))
                continue;
            //Comprova si ja ha sigut recorregut
            if (isFound)
                continue;

            PathFindingResult result;




        }
    }
    
    return PathFindingResult();
}
