#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class Bullet : public QWidget {
    Q_OBJECT
public:
    explicit Bullet(int x, int y, QWidget *parent = nullptr);

    void start();
    void setTarget(QWidget *target);
    void moveBullet();
    bool checkCollision();

private:
    QLabel *bulletLabel;
    QTimer *bulletTimer;
    QWidget *collisionTarget;
    int direction;  // Nueva variable para controlar la dirección de la bala: -1 = arriba, 1 = abajo
};

#endif // BULLET_H
