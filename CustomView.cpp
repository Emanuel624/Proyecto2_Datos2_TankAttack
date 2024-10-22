#include "CustomView.h"
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>  // Incluir QMessageBox para mostrar mensajes

// Constructor
// Updated Constructor
CustomView::CustomView(QGraphicsScene* scene, GridGraph& graph, int cellWidth, int cellHeight, Player& player1, Player& player2, int& currentPlayerTurn, QWidget* parent)
    : QGraphicsView(scene, parent),
      graph(graph),
      cellWidth(cellWidth),
      cellHeight(cellHeight),
      player1(player1),
      player2(player2),
      currentPlayerTurn(currentPlayerTurn),
      selectedTank(nullptr),
      routeLines(nullptr),
      routeSize(0) {
    setRenderHint(QPainter::Antialiasing);
}

// Metodo para seleccionar un tanque
void CustomView::selectTank(Tank* tank) {
    clearRouteLines();  // Borrar la ruta anterior si existe
    selectedTank = tank;
}

// Reimplementación del metodo mousePressEvent
void CustomView::mousePressEvent(QMouseEvent* event) {
    if (selectedTank) {
        // Obtener la posición del clic en la escena
        QPointF scenePos = mapToScene(event->pos());
        int targetCol = static_cast<int>(scenePos.x()) / cellWidth;
        int targetRow = static_cast<int>(scenePos.y()) / cellHeight;

        // Escoger el tipo de algoritmo de movimiento basado en probabilidad
        int movementType = selectedTank->selectMovementForTank(); // Decidir entre BFS, Dijkstra o Línea Vista

        int pathLength;
        int startNode = selectedTank->currentRow * graph.getCols() + selectedTank->currentCol;
        int targetNode = targetRow * graph.getCols() + targetCol;

        int* path = nullptr;

        if (movementType == 0) {
            // Usar BFS
            qDebug() << "Usando BFS para mover el tanque.";
            path = graph.bfs(startNode, targetNode, pathLength);
        } else if (movementType == 1) {
            // Usar Dijkstra
            qDebug() << "Usando Dijkstra para mover el tanque.";
            path = graph.dijkstra(startNode, targetNode, pathLength);
        } else {
            // Usar Línea Vista
            qDebug() << "Usando Línea Vista para mover el tanque.";
            path = PathfindingLineaVista::lineaVista(graph, selectedTank->currentRow, selectedTank->currentCol, targetRow, targetCol, pathLength, selectedTank, *scene(), cellWidth, cellHeight);
        }

        // Mover el tanque y dibujar la ruta con el mismo camino
        if (path != nullptr && pathLength > 0) {
            drawRoute(path, pathLength); // Dibuja la ruta utilizando el mismo path calculado
            selectedTank->moveToPath(graph, path, pathLength, *scene(), cellWidth, cellHeight); // Mover el tanque siguiendo exactamente ese path
            delete[] path;  // Liberar el arreglo de camino
        } else {
            qDebug() << "No se pudo encontrar una ruta válida.";
        }

        selectedTank = nullptr;  // Deseleccionar el tanque
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

// CustomView class - handle key events
void CustomView::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Shift) {
        // Check whose turn it is
        if (currentPlayerTurn == player1.getId()) {
            // Player 1 uses a power-up
            player1.useNextPowerUp(scene(), 1510, 50); // Actualiza la escena con el uso del PowerUp del Jugador 1

            // Reset actions and update the power-ups on screen
            player1.resetActions();
            player1.clearPowerUpsFromScene(scene(), 1510, 50); // Limpiar la representación anterior de los PowerUps
            player1.showPowerUpsOnScene(scene(), 1510, 50);    // Volver a dibujar la lista actualizada de PowerUps

            // Switch turn after using the power-up
            currentPlayerTurn = player2.getId();
            QString nextPlayerName = QString::fromStdString(player2.getName());
            QMessageBox::information(this, "Cambio de turno", "Es el turno del jugador " + nextPlayerName);

        } else {
            // Player 2 uses a power-up
            player2.useNextPowerUp(scene(), 1510, 300); // Actualiza la escena con el uso del PowerUp del Jugador 2

            // Reset actions and update the power-ups on screen
            player2.resetActions();
            player2.clearPowerUpsFromScene(scene(), 1510, 300); // Limpiar la representación anterior de los PowerUps
            player2.showPowerUpsOnScene(scene(), 1510, 300);    // Volver a dibujar la lista actualizada de PowerUps

            // Switch turn after using the power-up
            currentPlayerTurn = player1.getId();
            QString nextPlayerName = QString::fromStdString(player1.getName());
            QMessageBox::information(this, "Cambio de turno", "Es el turno del jugador " + nextPlayerName);
        }
    }

    // Call the base class's keyPressEvent to ensure other key events are handled
    QGraphicsView::keyPressEvent(event);
}



// Método para borrar las líneas de la ruta anterior
void CustomView::clearRouteLines() {
    if (routeLines) {
        for (int i = 0; i < routeSize; ++i) {
            if (routeLines[i]) {
                scene()->removeItem(routeLines[i]);
                delete routeLines[i];
            }
        }
        delete[] routeLines;
        routeLines = nullptr;
        routeSize = 0;
    }
}

// Método para dibujar la ruta en la escena
void CustomView::drawRoute(int* path, int pathLength) {
    if (pathLength < 2) return;

    clearRouteLines();  // Asegúrate de limpiar la ruta anterior
    routeSize = pathLength - 1;
    routeLines = new QGraphicsLineItem*[routeSize];

    QPen pen(Qt::red, 2);
    for (int i = 0; i < routeSize; ++i) {
        int startNode = path[i];
        int endNode = path[i + 1];

        int startRow = startNode / graph.getCols();
        int startCol = startNode % graph.getCols();
        int endRow = endNode / graph.getCols();
        int endCol = endNode % graph.getCols();

        // Calcular las coordenadas de inicio y fin de la línea
        int startX = startCol * cellWidth + cellWidth / 2;
        int startY = startRow * cellHeight + cellHeight / 2;
        int endX = endCol * cellWidth + cellWidth / 2;
        int endY = endRow * cellHeight + cellHeight / 2;

        // Crear la línea que representa el tramo de la ruta
        routeLines[i] = scene()->addLine(startX, startY, endX, endY, pen);
    }
}