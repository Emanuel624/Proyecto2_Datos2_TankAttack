#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsLineItem>

// Declaración adelantada de GridGraph
class GridGraph;

class Bullet : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // Constructor para inicializar la bala
    Bullet(GridGraph* graph, int startRow, int startCol, int targetRow, int targetCol);

    // Método para iniciar el movimiento
    void startMovement(QGraphicsScene* scene, int cellWidth, int cellHeight);

    // Destructor para liberar recursos
    ~Bullet();

    signals:
        // Señal para indicar cuando el movimiento ha terminado
        void movementCompleted();

    private slots:
        // Método para mover la bala
        void moveStep();

private:
    GridGraph* graph;  // Grafo que representa el mapa
    int currentRow;    // Fila actual
    int currentCol;    // Columna actual
    int targetRow;     // Fila objetivo
    int targetCol;     // Columna objetivo
    int reboteCount;   // Contador de rebotes
    float directionX;  // Dirección X
    float directionY;  // Dirección Y
    float speed;       // Velocidad de la bala
    QTimer* movementTimer; // Timer para controlar el movimiento

    QGraphicsLineItem* line;  // Línea que muestra el recorrido de la bala

    // Métodos auxiliares
    void calculateDirection();  // Calcular la dirección de la bala
    void handleRebound();  // Manejar los rebotes de la bala
};

#endif // BULLET_H
