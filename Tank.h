#ifndef TANK_H
#define TANK_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsPixmapItem>

class Tank : public QWidget {
    Q_OBJECT
public:
    // Constructor para inicializar el tanque con vida y una imagen
    Tank(int health, const QString &imagePath, QWidget *parent = nullptr);

    // Métodos para obtener y establecer la vida del tanque
    int getHealth() const;
    void setHealth(int health);

    // Metodo para mostrar el tanque en la ventana
    void display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight);

    // Metodo para disparar
    void shoot(QWidget *collisionTarget);

private:
    int health;          // Vida del tanque
    QPixmap pixmap;      // Imagen que representa al tanque
    QLabel *label;       // QLabel para mostrar la imagen del tanque


    // Metodo para mover el proyectil
    void moveBullet();

    //Metodo de colisiones
    bool checkCollision();
};

#endif // TANK_H