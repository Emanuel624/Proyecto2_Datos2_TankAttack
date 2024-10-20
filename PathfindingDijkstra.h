#ifndef PATHFINDINGDIJKSTRA_H
#define PATHFINDINGDIJKSTRA_H

#include "GridGraph.h"

class PathfindingDijkstra {
public:
    static int* dijkstra(const GridGraph& graph, int startNode, int targetNode, int& pathLength);
};

#endif //PATHFINDINGDIJKSTRA_H
