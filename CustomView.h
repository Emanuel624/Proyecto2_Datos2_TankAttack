#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "GridGraph.h"
#include "Tank.h"
#include "PathfindingLineaVista.h"

class CustomView : public QGraphicsView {
    Q_OBJECT
public:
    CustomView(QGraphicsScene* scene, GridGraph& graph, int cellWidth, int cellHeight, QWidget* parent = nullptr);
    void selectTank(Tank* tank);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    GridGraph& graph;              // Referencia al grafo
    int cellWidth;                 // Ancho de la celda
    int cellHeight;                // Alto de la celda
    Tank* selectedTank;            // Puntero al tanque seleccionado
    QGraphicsLineItem** routeLines; // Arreglo dinámico de líneas para mostrar la ruta
    int routeSize;                 // Tamaño actual del arreglo de líneas

    void clearRouteLines();        // Metodo para borrar las líneas de la ruta
    void drawRoute(int* path, int pathLength); // Metodo para dibujar la ruta desde un arreglo
};

#endif // CUSTOMVIEW_H
