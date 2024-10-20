#ifndef PATHFINDINGLINEAVISTA_H
#define PATHFINDINGLINEAVISTA_H

#include "GridGraph.h"
#include <QGraphicsScene>

class PathfindingLineaVista {
public:
    static int* lineaVista(GridGraph& graph, int startRow, int startCol, int targetRow, int targetCol, int& pathLength, Tank* tank, QGraphicsScene& scene, int cellWidth, int cellHeight);
};

#endif // PATHFINDINGLINEAVISTA_H
