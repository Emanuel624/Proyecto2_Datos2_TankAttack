#ifndef PATHFINDINGBFS_H
#define PATHFINDINGBFS_H

#include "GridGraph.h"
#include "Queue.h"

class PathfindingBFS {
public:
    static int* bfs(const GridGraph& graph, int startNode, int targetNode, int& pathLength);
};

#endif //PATHFINDINGBFS_H
