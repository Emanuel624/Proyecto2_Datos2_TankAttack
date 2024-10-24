#include "Bullet.h"
#include "GridGraph.h"
#include <QBrush>
#include <QDebug>
#include <QtMath>  // Para funciones matemáticas

Bullet::Bullet(GridGraph* graph, int startRow, int startCol, int targetRow, int targetCol)
    : graph(graph), currentRow(startRow), currentCol(startCol),
      targetRow(targetRow), targetCol(targetCol), reboteCount(0), speed(0.1f), line(nullptr) {

    // Crear un círculo (punto) como representación de la bala
    int size = 10;  // Tamaño del punto
    setRect(0, 0, size, size);
    setBrush(QBrush(Qt::black));  // Usar color negro para la bala

    // Crear un timer para el movimiento
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Bullet::moveStep);

    // Calcular la dirección inicial hacia el objetivo
    calculateDirection();
}

Bullet::~Bullet() {
    // Eliminar la línea cuando se destruya la bala
    if (line) {
        delete line;
        line = nullptr;
    }
}

void Bullet::startMovement(QGraphicsScene* scene, int cellWidth, int cellHeight) {
    scene->addItem(this);
    setPos(currentCol * cellWidth, currentRow * cellHeight);

    // Dibujar una línea desde el tanque hasta la casilla objetivo
    line = scene->addLine(currentCol * cellWidth + cellWidth / 2, currentRow * cellHeight + cellHeight / 2,
                          targetCol * cellWidth + cellWidth / 2, targetRow * cellHeight + cellHeight / 2,
                          QPen(Qt::red, 2));  // Línea roja de 2 px de ancho

    movementTimer->start(20);  // Movimiento suave (20 ms)
}

void Bullet::moveStep() {
    // Calcular la distancia hacia la casilla objetivo
    float distanceX = targetCol - currentCol;
    float distanceY = targetRow - currentRow;
    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    // Verificar si la bala ha llegado al destino
    if (distance < 0.1f) {  // Si está muy cerca del objetivo
        movementTimer->stop();
        emit movementCompleted();
        if (line) {
            delete line;  // Eliminar la línea cuando termina el movimiento
        }
        deleteLater();  // Liberar la bala de la memoria
        return;
    }

    // Mover la bala en la escena suavemente
    currentCol += directionX * speed;
    currentRow += directionY * speed;
    setPos(currentCol * 50, currentRow * 50);  // Actualizar la posición en la escena

    // Si está cerca de un obstáculo o fuera de los límites del mapa, manejar el rebote
    if (reboteCount == 0 && (graph->isObstacle(currentRow, currentCol) || currentRow < 0 || currentRow >= graph->getRows() || currentCol < 0 || currentCol >= graph->getCols())) {
        handleRebound();
        reboteCount++;
    }
}

void Bullet::calculateDirection() {
    // Calcular la dirección hacia la casilla objetivo
    float deltaX = targetCol - currentCol;
    float deltaY = targetRow - currentRow;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 0) {
        // Normalizar la dirección para moverse correctamente
        directionX = deltaX / distance;
        directionY = deltaY / distance;
    } else {
        directionX = 0;
        directionY = 0;
    }
}

void Bullet::handleRebound() {
    // Invertir la dirección al tocar un obstáculo o borde
    if (currentRow < 0 || currentRow >= graph->getRows()) {
        directionY = -directionY;
    }
    if (currentCol < 0 || currentCol >= graph->getCols()) {
        directionX = -directionX;
    }
}
