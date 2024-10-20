#include "PathfindingDijkstra.h"
#include "PriorityQueue.h"
#include <limits>

int* PathfindingDijkstra::dijkstra(const GridGraph& graph, int startNode, int targetNode, int& pathLength) {
    int totalNodes = graph.getRows() * graph.getCols();
    int* distances = new int[totalNodes];
    int* previous = new int[totalNodes];
    bool* visited = new bool[totalNodes];

    for (int i = 0; i < totalNodes; ++i) {
        distances[i] = std::numeric_limits<int>::max();
        previous[i] = -1;
        visited[i] = false;
    }
    distances[startNode] = 0;

    PriorityQueue pq(totalNodes);
    pq.enqueue(startNode, 0);

    while (!pq.isEmpty()) {
        int currentNode = pq.dequeue();
        if (currentNode == targetNode) break;

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        for (int i = 0; i < totalNodes; ++i) {
            if (graph.getAdjMatrix()[currentNode][i] > 0 && !visited[i]) {
                int newDist = distances[currentNode] + graph.getAdjMatrix()[currentNode][i];
                if (newDist < distances[i]) {
                    distances[i] = newDist;
                    previous[i] = currentNode;
                    pq.enqueue(i, newDist);
                }
            }
        }
    }

    int* path = new int[totalNodes];
    pathLength = 0;

    for (int at = targetNode; at != -1; at = previous[at]) {
        path[pathLength++] = at;
    }

    for (int i = 0; i < pathLength / 2; ++i) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    if (path[0] != startNode) {
        pathLength = 0;
    }

    delete[] distances;
    delete[] previous;
    delete[] visited;

    return path; // El llamador debe liberar este arreglo
}

