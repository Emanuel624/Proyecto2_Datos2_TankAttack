#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsLineItem>

class GridGraph;
class Tank;
class Player;

class Bullet : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // Constructor que incluye el tanque que dispara
    Bullet(GridGraph* graph, Player* shooterPlayer, Tank* shooterTank, int startRow, int startCol, int targetRow, int targetCol, int damage);

    void startMovement(QGraphicsScene* scene, int cellWidth, int cellHeight);
    ~Bullet();

    int maxRebotes = 1;  // Número máximo de rebotes

signals:
    void movementCompleted();  // Señal para indicar que el movimiento ha finalizado

private slots:
    void moveStep();  // Método que controla los pasos del movimiento de la bala

private:
    GridGraph* graph;  // Grafo para el cálculo de trayectorias
    int currentRow;    // Posición actual en fila
    int currentCol;    // Posición actual en columna
    int targetRow;     // Posición objetivo en fila
    int targetCol;     // Posición objetivo en columna
    int reboteCount;   // Conteo de rebotes
    int damage;        // Daño que la bala causará
    QTimer* movementTimer;  // Temporizador para controlar el movimiento

    Player* shooterPlayer;  // Añadido: Puntero al jugador que disparó
    Tank* shooterTank;
    QGraphicsLineItem* line;  // Para dibujar líneas en el camino de la bala

    int* path;          // Array que contiene la ruta de la bala
    int pathIndex;      // Índice actual en el array de ruta
    int pathLength;     // Longitud de la ruta

    int cellWidth;      // Ancho de cada celda en el mapa
    int cellHeight;     // Altura de cada celda en el mapa

    QList<QGraphicsLineItem*> pathLines;  // Lista para almacenar los segmentos de la línea de trayectoria

    // Métodos auxiliares
    void handleRebound();                // Método para manejar el rebote
    void applyDamageToTank(Tank* tank);  // Aplica daño a un tanque
    void endMovement();                  // Finaliza el movimiento de la bala
};

#endif // BULLET_H
