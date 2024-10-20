#include "Tank.h"
#include "GridGraph.h"
#include "PathfindingBFS.h"
#include "PathfindingLineaVista.h"
#include <QtWidgets/QGraphicsScene>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QLabel>
#include <QThread>

// Constructor para inicializar el tanque con vida, imagen y tipo
Tank::Tank(int health, const QString &imagePath, int type)
    : health(health), pixmap(imagePath), Tank_type(type) {
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde" << imagePath;
    }
    setPixmap(pixmap);
}

// Seleccionar el tipo de movimiento del tanque basado en su tipo y probabilidad
int Tank::selectMovementForTank() const {
    int probability = QRandomGenerator::global()->bounded(100); // Genera un número aleatorio entre 0 y 99

    // Tanques celeste/azul
    if (Tank_type == 1) {
        return (probability < 50) ? 0 : 2; // 50% BFS, 50% Línea Vista
    }
    // Tanques amarillo/rojo
    if (Tank_type == 0) {
        return (probability < 80) ? 1 : 2; // 80% Dijkstra, 20% Línea Vista
    }

    return 2; // Default a Línea Vista si hay algún error
}

void Tank::display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight) {
    QPixmap scaledPixmap = pixmap.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio);
    setPixmap(scaledPixmap);
    int x = col * cellWidth;
    int y = row * cellHeight;
    setPos(x, y);
    currentRow = row;
    currentCol = col;
    scene.addItem(this);
}

void Tank::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit tankSelected(this);
    qDebug() << "Tanque seleccionado en posición (" << currentRow << "," << currentCol << ")";

    // Mostrar las coordenadas del clic en la escena
    QPointF clickPos = event->scenePos();
    qDebug() << "Coordenadas del clic: (" << clickPos.x() << "," << clickPos.y() << ")";

    // Llamar a la implementación base para asegurarse de que se manejen otros eventos
    QGraphicsPixmapItem::mousePressEvent(event);
}

// Movimiento del tanque, basado en el algoritmo seleccionado
void Tank::moveToPath(GridGraph &graph, int* path, int pathLength, QGraphicsScene &scene, int cellWidth, int cellHeight) {
    // Si se encontró un camino
    if (path != nullptr && pathLength > 0) {
        for (int i = 0; i < pathLength; ++i) {
            int nextNode = path[i];
            int nextRow = nextNode / graph.getCols();
            int nextCol = nextNode % graph.getCols();

            // Verificar si el nodo siguiente está dentro de los límites
            if (nextRow < 0 || nextRow >= graph.getRows() || nextCol < 0 || nextCol >= graph.getCols()) {
                qDebug() << "El tanque alcanzó el límite del mapa.";
                break;
            }

            if (graph.isObstacle(nextRow, nextCol)) {
                qDebug() << "Encontrado obstáculo en el camino.";
                break;
            }

            // Actualizar la posición del tanque en cada paso
            this->display(scene, nextRow, nextCol, cellWidth, cellHeight);

            // Actualizar la posición interna del tanque en cada paso
            currentRow = nextRow;
            currentCol = nextCol;

            QThread::msleep(200);
            QApplication::processEvents();
        }

        // Emitir la señal cuando el movimiento ha terminado
        emit movementCompleted();
    } else {
        qDebug() << "No se encontró un camino para mover el tanque.";
    }
}



