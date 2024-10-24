#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include <iostream>
#include <cstring>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QRandomGenerator>
#include "Tank.h"
#include "PowerUp.h"
#include "Queue.h"
#include "PriorityQueue.h"

class GridGraph {
private:
    int rows;
    int cols;
    int** adjMatrix;

public:
    GridGraph(int rows, int cols);
    ~GridGraph();

    // Métodos getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int** getAdjMatrix() const { return adjMatrix; }


    void addEdge(int u, int v);
    void generateConnections();
    void drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor);
    void generateObstacles(float obstacleDensity);
    void addTank(Tank &tank, int row, int col, QGraphicsScene &scene, int cellWidth, int cellHeight);
    void generatePowerUps(QGraphicsScene& scene, float powerUpDensity, int cellWidth, int cellHeight);
    bool isNavigable() const;

    //Metodos de busqueda
    int* bfs(int startNode, int targetNode, int& pathLenght);
    int* dijkstra(int startNode, int targetNode, int& pathLenght);
    bool lineOfSight(int startRow, int startCol, int targetRow, int targetCol);

    bool isObstacle(int row, int col) const;

private:
    void dfs(int node, bool* visited) const;
};

#endif // GRIDGRAPH_H