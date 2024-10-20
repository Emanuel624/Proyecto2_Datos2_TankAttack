#include "PathfindingLineaVista.h"
#include <QDebug>
#include <QRandomGenerator>

int* PathfindingLineaVista::lineaVista(GridGraph& graph, int startRow, int startCol, int targetRow, int targetCol, int& pathLength, Tank* tank, QGraphicsScene& scene, int cellWidth, int cellHeight) {
    int rowStep = targetRow > startRow ? 1 : (targetRow < startRow ? -1 : 0);
    int colStep = targetCol > startCol ? 1 : (targetCol < startCol ? -1 : 0);

    int nextRow = startRow;
    int nextCol = startCol;

    pathLength = 0;
    int* path = new int[graph.getRows() * graph.getCols()];

    // Agregar la posición inicial al camino
    path[pathLength++] = startRow * graph.getCols() + startCol;

    // Moverse en línea recta paso a paso
    while (nextRow != targetRow || nextCol != targetCol) {
        nextRow += rowStep;
        nextCol += colStep;

        // Verificar si se ha alcanzado el objetivo (target)
        if (nextRow == targetRow && nextCol == targetCol) {
            qDebug() << "El tanque ha alcanzado el objetivo en (" << nextRow << "," << nextCol << ")";
            path[pathLength++] = nextRow * graph.getCols() + nextCol;
            break;  // Detener si se ha alcanzado el objetivo
        }

        // Verificar si se sale de los límites del mapa
        if (nextRow < 0 || nextRow >= graph.getRows() || nextCol < 0 || nextCol >= graph.getCols()) {
            qDebug() << "El tanque alcanzó el límite del mapa en línea vista.";
            break;  // Detener si alcanzamos los límites del mapa
        }

        // Verificar si hay un obstáculo
        if (graph.isObstacle(nextRow, nextCol)) {
            qDebug() << "Obstáculo encontrado en línea vista en (" << nextRow << "," << nextCol << ")";

            // Hacer un movimiento aleatorio dentro de un radio si se encuentra un obstáculo
            int randomRow, randomCol;
            bool moved = false;
            int maxDistance = 1; // El radio definido para el movimiento aleatorio

            // Escoger una posición aleatoria válida
            for (int i = 0; i < 10; ++i) {
                randomRow = nextRow + QRandomGenerator::global()->bounded(-maxDistance, maxDistance + 1);
                randomCol = nextCol + QRandomGenerator::global()->bounded(-maxDistance, maxDistance + 1);

                if (randomRow >= 0 && randomRow < graph.getRows() &&
                    randomCol >= 0 && randomCol < graph.getCols() &&
                    !graph.isObstacle(randomRow, randomCol)) {

                    qDebug() << "Moviendo a posición aleatoria (" << randomRow << "," << randomCol << ")";
                    nextRow = randomRow;
                    nextCol = randomCol;

                    // Agregar la posición aleatoria al camino
                    path[pathLength++] = nextRow * graph.getCols() + nextCol;

                    moved = true;
                    break;
                }
            }

            // Si no se encuentra una posición aleatoria válida, detenerse
            if (!moved) {
                qDebug() << "No se encontró una posición válida para moverse después del obstáculo.";
                break;
            }

            // Intentar nuevamente aplicar línea vista desde la nueva posición aleatoria
            rowStep = targetRow > nextRow ? 1 : (targetRow < nextRow ? -1 : 0);
            colStep = targetCol > nextCol ? 1 : (targetCol < nextCol ? -1 : 0);

            // Continuar la línea vista desde la posición aleatoria
            while (nextRow != targetRow || nextCol != targetCol) {
                nextRow += rowStep;
                nextCol += colStep;

                // Verificar si se ha alcanzado el objetivo (target)
                if (nextRow == targetRow && nextCol == targetCol) {
                    qDebug() << "El tanque ha alcanzado el objetivo en el segundo intento en (" << nextRow << "," << nextCol << ")";
                    path[pathLength++] = nextRow * graph.getCols() + nextCol;
                    break;
                }

                // Verificar si se sale de los límites del mapa
                if (nextRow < 0 || nextRow >= graph.getRows() || nextCol < 0 || nextCol >= graph.getCols()) {
                    qDebug() << "El tanque alcanzó el límite del mapa en el segundo intento de línea vista.";
                    break;
                }

                // Verificar si hay otro obstáculo
                if (graph.isObstacle(nextRow, nextCol)) {
                    qDebug() << "Obstáculo encontrado en el segundo intento de línea vista en (" << nextRow << "," << nextCol << ")";
                    break;
                }

                // Guardar la posición en el camino
                path[pathLength++] = nextRow * graph.getCols() + nextCol;
            }

            break; // Detener después de aplicar la línea vista y el movimiento aleatorio
        }

        // Guardar la posición en el camino
        path[pathLength++] = nextRow * graph.getCols() + nextCol;
    }

    // Si no se encontró un camino, limpiar y devolver nullptr
    if (pathLength == 0) {
        delete[] path;
        return nullptr;
    }

    return path;  // Devolver el camino
}
