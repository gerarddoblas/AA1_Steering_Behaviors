#include "PathFinding.hpp"
#include "Node.hpp"
#include <queue>
#include <limits>

PathFindingResult PathFinding::Find(Tiles start,Tiles objective, World& world)
{

    bool isDiagonal;
    const int tiles = world.widthTiles * world.heightTiles;
    std::vector<bool> tileFounds(tiles);
    std::priority_queue<Node> frontier;
    //StartNode
    Node startNode;
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

    //Contador de insercions
    int inserctionCount = 0;

    //Boolea que serveix per saber si ha trobat el cami o no
    float isFound = false;


    PathFindingResult result;

    while (!frontier.empty())
    {
        Node currentNode = frontier.top();

        frontier.pop();

        //Optimitzacio de crides
        short x = currentNode.tile.x;
        short y = currentNode.tile.y;

        int index = (y * world.widthTiles) + x;

        if (tileFounds[index])
            continue;

        tileFounds[index] = true;

        //S'emmagatzema al vector de result les tiles que s'exploren
        result._explorationOrder.push_back(currentNode.tile);

        //Comprova si el currentNode es l'objectiu
        if (currentNode.tile == objective)
        {
            isFound = true;
            break;
        }
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
                //Recta = 1 si es Diagonal = Raiz de 2
                if (isDiagonal)
                    cost = sqrt(2);
                else
                    cost = 1;
                //El g de la casella actual més el cost del pas
                //Seguiment del cost acumulat
                float totalCost = g[index] + cost;
                //Si el cost nou es menor que el del vei, actualitza el cost del vei, apunta el index dels pares al index actual i crea un Node per a la veïna i fer push amb la Tile, priority i el numero d'interseccio
                //Si es mes barat el cost nou, llavors es la millor ruta
                if (totalCost < g[neighborIndex])
                {
                    //S'actualitza el cost del vector y la posició del pare
                    g[neighborIndex] = totalCost;
                    parents[neighborIndex] = index;
                    //El node vei que sera l'actual
                    Node neighbourNode;
                    neighbourNode.tile.x = ax;
                    neighbourNode.tile.y = ay;
                    neighbourNode.priority = totalCost;
                    neighbourNode.intersection = inserctionCount;

                    inserctionCount++;

                    frontier.push(neighbourNode);
                }
            }
        }
    }


    result.isFound = isFound;

    if (!isFound)
        return result;


    result.time;
    result._cost = g[g.size() - 1];
    result._exploredNodes = result._explorationOrder.size();
    
    int index = objective.y * world.widthTiles + objective.x;
    do
    {
        Tiles tile;
        tile.x = parents[index];
        tile.y = parents[index];
        result._path.push_back(tile);

        index--;
    } while (index != -1);
    

    return result;
}
