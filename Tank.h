#ifndef TANK_H
#define TANK_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QApplication>


// Declaración adelantada de GridGraph
class GridGraph;

class Tank : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    // Constructor para inicializar el tanque con vida y una imagen
    Tank(int health, const QString &imagePath, int type);

    // Métodos getter
    int getHealth() const;
    void setHealth(int health);
    int getType() const;
    bool shouldUseBFS() const;
    int selectMovementForTank() const;

    // Metodo para mostrar el tanque en la ventana
    void display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight);

    // Metodo para mover el tanque
    void moveToPath(GridGraph &graph, int* path, int pathLength, QGraphicsScene &scene, int cellWidth, int cellHeight);

    // Eventos de click
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // Almacenar las coordenadas actuales
    int currentRow;
    int currentCol;

    signals:
        void tankSelected(Tank* tank);  // Señal para notificar que un tanque ha sido seleccionado
        void movementCompleted();

    // Metodo para disparar
    void shoot(QWidget *collisionTarget);

private:
    int health;          // Vida del tanque
    int Tank_type;
    QPixmap pixmap;      // Imagen que representa al tanque
    QLabel *label;       // QLabel para mostrar la imagen del tanque

};

#endif // TANK_H