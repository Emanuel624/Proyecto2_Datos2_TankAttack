#include "Tank.h"
#include "GridGraph.h"
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

    // Crear la etiqueta de vida y configurarla cerca del tanque
    lifeLabel = new QGraphicsTextItem(QString::number(health), this);
    lifeLabel->setDefaultTextColor(Qt::white);  // Color del texto
    lifeLabel->setPos(0, -20);  // Posiciona la etiqueta encima del tanque
}



void Tank::setPrecisionMovimientoEffect(bool isActive) {
    precisionMovimientoActive = isActive;
}


// Seleccionar el tipo de movimiento del tanque basado en su tipo y probabilidad
int Tank::selectMovementForTank() const {
    int probability = QRandomGenerator::global()->bounded(100); // Generates a random number between 0 and 99

    if (precisionMovimientoActive) {
        // 90% BFS/Dijkstra and 10% random movement
        std::cout << "90% SI"<< std::endl;
        if (probability < 90) {
            return (Tank_type == 0) ? 0 : 1;  // 0 for BFS, 1 for Dijkstra
        } else {
            return 2;  // 10% random movement (Línea de Vista or other)
        }
    } else {
        // Original logic based on Tank_type
        if (Tank_type == 0) {
            return (probability < 50) ? 0 : 2; // 50% BFS, 50% Línea Vista
        } else if (Tank_type == 1) {
            return (probability < 80) ? 1 : 2; // 80% Dijkstra, 20% Línea Vista
        }
        return 2;  // Default to Línea Vista if error
    }
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

//Metodo de disparo
void Tank::shoot(Player* player, QGraphicsScene* scene, GridGraph* graph, int targetRow, int targetCol, int cellWidth, int cellHeight) {
    int damage = 50;
    Bullet* bullet = new Bullet(graph, player, this, currentRow, currentCol, targetRow, targetCol, damage);
    bullet->startMovement(scene, cellWidth, cellHeight);

    connect(bullet, &Bullet::movementCompleted, [this]() {
        emit movementCompleted();
    });
}



void Tank::setHealth(int newHealth) {
    if (newHealth < 0) {
        health = 0;  // La vida no puede ser menor a 0
    } else {
        health = newHealth;  // Asigna la nueva vida
    }

    int maxHealth = 100;
    if (health > maxHealth) {
        health = maxHealth;  // La vida no puede superar el límite máximo
    }

    // Actualizar la etiqueta de vida
    lifeLabel->setPlainText(QString::number(health));

    // Verificar si el tanque fue destruido
    if (health == 0) {
        qDebug() << "Tanque destruido!";
        if (scene()) {
            scene()->removeItem(this);
        }
    }
}


int Tank::getType() const {
    return Tank_type;
}




