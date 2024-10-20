#include "PathfindingBFS.h"

int* PathfindingBFS::bfs(const GridGraph& graph, int startNode, int targetNode, int& pathLength) {
    int totalNodes = graph.getRows() * graph.getCols();
    int* prev = new int[totalNodes];
    bool* visited = new bool[totalNodes];

    // Inicializar los arreglos
    for (int i = 0; i < totalNodes; ++i) {
        prev[i] = -1;
        visited[i] = false;
    }

    Queue q(totalNodes);
    q.enqueue(startNode);
    visited[startNode] = true;

    while (!q.isEmpty()) {
        int node = q.dequeue();

        if (node == targetNode) {
            break;
        }

        for (int i = 0; i < totalNodes; ++i) {
            if (graph.getAdjMatrix()[node][i] == 1 && !visited[i]) {
                q.enqueue(i);
                visited[i] = true;
                prev[i] = node;
            }
        }
    }

    // Reconstruir el camino desde targetNode hasta startNode
    int* path = new int[totalNodes];
    pathLength = 0;
    for (int at = targetNode; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }

    // Invertir el arreglo para tener el camino de startNode a targetNode
    for (int i = 0; i < pathLength / 2; ++i) {
        int temp = path[i];
        path[i] = path[pathLength - i - 1];
        path[pathLength - i - 1] = temp;
    }

    // Verificar si el camino encontrado comienza con el nodo inicial
    if (path[0] != startNode) {
        pathLength = 0; // Vaciar el camino si no se encontró una ruta válida
    }

    // Liberar la memoria usada por los arreglos temporales
    delete[] prev;
    delete[] visited;

    return path; // El llamador debe liberar este arreglo
}

