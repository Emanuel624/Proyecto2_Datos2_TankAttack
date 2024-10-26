#include "Bullet.h"
#include "GridGraph.h"
#include "Player.h"
#include "Tank.h"
#include <QBrush>
#include <QDebug>
#include <QtMath>

Bullet::Bullet(GridGraph* graph, Player* shooterPlayer, Tank* shooterTank, int startRow, int startCol, int targetRow, int targetCol, int damage)
    : graph(graph), shooterPlayer(shooterPlayer), shooterTank(shooterTank), reboteCount(0), line(nullptr),
      path(nullptr), pathIndex(0), pathLength(0), damage(damage), targetRow(targetRow), targetCol(targetCol) {

    // Calcular dirección hacia la posición de destino
    int dRow = targetRow - startRow;
    int dCol = targetCol - startCol;

    // Ajustar la posición inicial una casilla adelante en la dirección del disparo
    currentRow = startRow + (dRow != 0 ? (dRow / std::abs(dRow)) : 0);
    currentCol = startCol + (dCol != 0 ? (dCol / std::abs(dCol)) : 0);

    // Configuración del tamaño y apariencia de la bala
    int size = 20;
    setRect(0, 0, size, size);
    setBrush(QBrush(Qt::black));

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Bullet::moveStep);

    // Inicializar el movimiento en la dirección calculada
    path = graph->lineOfSight(currentRow, currentCol, targetRow, targetCol, pathLength);
    if (!path) {
        qDebug() << "No se encontró trayectoria para la bala.";
    } else {
        pathIndex = 0;
    }
}

Bullet::~Bullet() {
    if (line) {
        delete line;
        line = nullptr;
    }
    if (path) {
        delete[] path;
        path = nullptr;
    }
    for (QGraphicsLineItem* line : pathLines) {
        if (line) {
            scene()->removeItem(line);
            delete line;
        }
    }
}

void Bullet::startMovement(QGraphicsScene* scene, int cellWidth, int cellHeight) {
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;

    if (!path || pathLength == 0) {
        qDebug() << "No hay trayectoria, no se puede mover la bala.";
        deleteLater();
        return;
    }

    if (!scene->items().contains(this)) {
        scene->addItem(this);
    }

    setPos((currentCol * cellWidth) + cellWidth / 2 - rect().width() / 2,
           (currentRow * cellHeight) + cellHeight / 2 - rect().height() / 2);
    movementTimer->start(80);
}

void Bullet::moveStep() {
    if (path == nullptr) {
        endMovement();
        return;
    }

    for (QGraphicsItem* item : collidingItems()) {
        Tank* tank = dynamic_cast<Tank*>(item);
        if (tank) {
            applyDamageToTank(tank);
            endMovement();
            return;
        }
    }

    if (pathIndex >= pathLength) {
        if (reboteCount < 1) { // Limitar a un solo rebote
            reboteCount++;

            // Invertir la dirección actual sin un destino fijo
            int dRow = (targetRow - currentRow) == 0 ? 0 : -1 * (targetRow - currentRow) / std::abs(targetRow - currentRow);
            int dCol = (targetCol - currentCol) == 0 ? 0 : -1 * (targetCol - currentCol) / std::abs(targetCol - currentCol);
            targetRow = currentRow + dRow * 1000;  // Multiplicar para prolongar la trayectoria
            targetCol = currentCol + dCol * 1000;

            // Calcular una nueva trayectoria sin un objetivo limitado
            delete[] path;
            path = graph->lineOfSight(currentRow, currentCol, targetRow, targetCol, pathLength);

            if (!path || pathLength == 0) {
                endMovement();
                return;
            }

            pathIndex = 0;
            qDebug() << "Rebote detectado, cambiando de dirección.";
        } else {
            endMovement();
            return;
        }
    }

    int nextNode = path[pathIndex];
    int nextRow = nextNode / graph->getCols();
    int nextCol = nextNode % graph->getCols();

    if (graph->isObstacle(nextRow, nextCol)) {
        if (reboteCount < 1) { // Limitar a un solo rebote
            reboteCount++;

            // Invertir dirección en caso de obstáculo
            int dRow = (nextRow - currentRow) == 0 ? 0 : -1 * (nextRow - currentRow) / std::abs(nextRow - currentRow);
            int dCol = (nextCol - currentCol) == 0 ? 0 : -1 * (nextCol - currentCol) / std::abs(nextCol - currentCol);
            targetRow = currentRow + dRow * 1000;
            targetCol = currentCol + dCol * 1000;

            delete[] path;
            path = graph->lineOfSight(currentRow, currentCol, targetRow, targetCol, pathLength);

            if (!path || pathLength == 0) {
                endMovement();
                return;
            }

            pathIndex = 0;
            qDebug() << "Rebote detectado, cambiando de dirección.";
            return;
        } else {
            endMovement();
            return;
        }
    }

    currentRow = nextRow;
    currentCol = nextCol;

    qreal prevX = x() + rect().width() / 2;
    qreal prevY = y() + rect().height() / 2;

    setPos((currentCol * cellWidth) + cellWidth / 2 - rect().width() / 2,
           (currentRow * cellHeight) + cellHeight / 2 - rect().height() / 2);

    QGraphicsLineItem* pathLine = new QGraphicsLineItem(prevX, prevY, x() + rect().width() / 2, y() + rect().height() / 2);
    pathLine->setPen(QPen(Qt::blue, 2));
    scene()->addItem(pathLine);
    pathLines.append(pathLine);

    pathIndex++;
}

void Bullet::applyDamageToTank(Tank* tank) {
    int actualDamage;

    // Verificar si el jugador tiene el PowerUp de daño completo activo
    if (shooterPlayer->isFullDamagePowerUpActive()) {
        actualDamage = tank->getHealth();  // Hacer que el daño sea igual a la salud del tanque para "100% de daño"
    } else {
        // Daño normal basado en el tipo de tanque
        int maxHealth = 100;
        int tankType = tank->getType();

        if (tankType == 0) {
            actualDamage = maxHealth * 0.25;
        } else if (tankType == 1) {
            actualDamage = maxHealth * 0.50;
        }
    }

    tank->setHealth(tank->getHealth() - actualDamage);
    qDebug() << "Tanque impactado! Daño:" << actualDamage << " Vida restante:" << tank->getHealth();
}


void Bullet::endMovement() {
    movementTimer->stop();
    emit movementCompleted();

    if (line) {
        scene()->removeItem(line);
        delete line;
        line = nullptr;
    }

    for (QGraphicsLineItem* pathLine : pathLines) {
        scene()->removeItem(pathLine);
        delete pathLine;
    }
    pathLines.clear();

    scene()->removeItem(this);
    deleteLater();
}
