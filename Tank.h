#ifndef TANK_H
#define TANK_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include "Bullet.h"  // Incluir la clase Bullet

// Declaración adelantada de GridGraph
class GridGraph;

class Tank : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    // Constructor para inicializar el tanque con vida y una imagen
    Tank(int health, const QString &imagePath, int type);

    // Métodos getter
    int getHealth() const;
    int getCurrentRow() const;   // Getter para currentRow
    int getCurrentCol() const;
    void setHealth(int health);
    int getType() const;
    bool shouldUseBFS() const;
    int selectMovementForTank() const;


    // Metodo para mostrar el tanque en la ventana
    void display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight);

    // Metodo para mover el tanque
    void moveToPath(GridGraph &graph, int* path, int pathLength, QGraphicsScene &scene, int cellWidth, int cellHeight);

    // Método para disparar
    void shoot(QGraphicsScene* scene, GridGraph* graph, int targetRow, int targetCol, int cellWidth, int cellHeight);

    // Eventos de click
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        void tankSelected(Tank* tank);  // Señal para notificar que un tanque ha sido seleccionado
    void movementCompleted();  // Señal para notificar cuando un tanque ha terminado de moverse o disparar

private:
    int health;
    int Tank_type;
    QPixmap pixmap;
    int currentRow;
    int currentCol;
    // Columna actual
};

#endif // TANK_H
