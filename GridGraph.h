#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include <iostream>
#include <cstring>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QRandomGenerator>
#include "Tank.h"

class GridGraph {
private:
    int rows;
    int cols;
    int** adjMatrix;

public:
    GridGraph(int rows, int cols);
    ~GridGraph();

    void addEdge(int u, int v);
    void generateConnections();
    void drawGrid(QGraphicsScene& scene, int screenWidth, int screenHeight, float scaleFactor);
    void generateObstacles(float obstacleDensity);
    void addTank(Tank &tank, int row, int col, QGraphicsScene &scene, int cellWidth, int cellHeight);
    bool isNavigable() const;

private:
    void dfs(int node, bool* visited) const;
};

#endif // GRIDGRAPH_H
