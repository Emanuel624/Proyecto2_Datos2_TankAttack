#ifndef TANK_H
#define TANK_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include "Bullet.h"  // Asegúrate de tener la clase Bullet para manejar los disparos

class Tank : public QWidget {
    Q_OBJECT
public:
    // Constructor para inicializar el tanque con vida y una imagen
    Tank(int health, const QString &imagePath, QWidget *parent = nullptr);

    // Métodos para obtener y establecer la vida del tanque
    int getHealth() const;
    void setHealth(int health);

    // Metodo para mostrar el tanque en la ventana
    void display(QWidget *parent);

    // Metodo para disparar
    void shoot(QWidget *collisionTarget);

private:
    int health;          // Vida del tanque
    QPixmap pixmap;      // Imagen que representa al tanque
    QLabel *label;       // QLabel para mostrar la imagen del tanque

    // Temporizador para el movimiento del proyectil
    QTimer *bulletTimer;

    // Proyectil (bala) representado por una clase Bullet
    Bullet *bullet;  // <- Aquí declaramos la variable bullet

    // Metodo para mover el proyectil
    void moveBullet();

    //Metodo de colisiones
    bool checkCollision();
};

#endif // TANK_H
