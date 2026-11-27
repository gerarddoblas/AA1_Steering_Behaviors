#include "PathFinding.hpp"
#include "Nodes.hpp"
#include <queue>
#include <limits>

PathFindingResult PathFinding::Find(Tiles start,Tiles objective, World& world)
{

    bool isDiagonal;
    const int tiles = world.widthTiles * world.heightTiles;
    std::vector<bool> tileFounds(tiles);
    std::priority_queue<Nodes> frontier;
    //StartNode
    Nodes startNode;
    startNode.tile = start;
    startNode.intersection = 0;
    startNode.priority = 0;

    frontier.push(startNode);

    //Cost del millor camí conegut
    //https://en.cppreference.com/cpp/types/numeric_limits/infinity
    std::vector<float> g(tiles, std::numeric_limits<float>::infinity());
    //g index
    int startIndex = start.y * world.widthTiles + start.x;
    g[startIndex] = 0;
    //L'index de la casella des de la qual s'ha arribat pel millor camí
    std::vector<int> parents(tiles, -1);

    while (!frontier.empty())
    {
        Nodes currentNode = frontier.top();

        frontier.pop();

        //Optimitzacio de crides
        short x = currentNode.tile.x;
        short y = currentNode.tile.y;

        int index = (y * world.widthTiles) + x;

        if (tileFounds[index])
            continue;

        tileFounds[index] = true;


        //Comprova si el currentNode es el objectiu
        if (currentNode.tile == objective)
            break;
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
                if ((isDiagonal) && (!world.isWalkable(ax, y) || !world.isWalkable(x, ay)))
                    continue;
                //Guardo l'index del vei
                int neighborIndex = (ay * world.widthTiles) + ax;
                //Comprova si ja ha sigut recorregut
                if (tileFounds[neighborIndex])
                    continue;
                //Assigna a una variable el cost del pas
                float cost;
                //TO DO: Recta = 1 Diagonal = Raiz de 2
                if (isDiagonal)
                    cost = sqrt(2);
                else
                    cost = 1;
                //TO DO: el g de la casella actual més el cost del pas
                float totalCost = g[index] + cost;
                //TO DO: Si el cost nou es menor que el del vei, actualitza el cost del vei, apunta el index dels pares al index actual i crea un Node per a la veïna i fer push amb la Tile, priority i el numero d'interseccio
                if (totalCost < g[neighborIndex])
                {
                    g[neighborIndex] = totalCost;
                    parents[neighborIndex] = index;
                    Nodes newNode;
                }
            }
        }
    }
    return PathFindingResult();
}
