#include "Bullet.h"
#include <QRect>
#include <QDebug>

Bullet::Bullet(int x, int y, QWidget *parent)
    : QWidget(parent), bulletLabel(new QLabel(parent)), bulletTimer(new QTimer(this)), collisionTarget(nullptr), direction(-1) { // Inicializa la dirección hacia arriba

    // Establecer el estilo del disparo
    bulletLabel->setStyleSheet("background-color: red;");
    bulletLabel->setFixedSize(10, 10);  // Tamaño del proyectil
    bulletLabel->move(x, y);            // Posición inicial del disparo
    bulletLabel->show();

    // Conectar el temporizador para mover el disparo
    connect(bulletTimer, &QTimer::timeout, this, &Bullet::moveBullet);
}

void Bullet::start() {
    bulletTimer->start(50);  // Mover el disparo cada 50 ms
}

void Bullet::setTarget(QWidget *target) {
    collisionTarget = target;
}

void Bullet::moveBullet() {
    // Mueve la bala en la dirección actual
    bulletLabel->move(bulletLabel->x(), bulletLabel->y() + (10 * direction));

    // Verificar si el proyectil colisiona con el objetivo (blackRect)
    if (checkCollision()) {
        // Invertir la dirección del movimiento si hay colisión (rebote)
        direction = direction * -1;
        qDebug() << "Colisión detectada con el blackRect! Invirtiendo dirección";
    }

    // Si el proyectil se sale de la pantalla, detener el disparo
    if (bulletLabel->y() < 0 || bulletLabel->y() > parentWidget()->height()) {
        bulletLabel->hide();
        bulletTimer->stop();
        qDebug() << "La bala se salió de la pantalla";
    }
}

bool Bullet::checkCollision() {
    if (!collisionTarget) {
        return false; // Si no hay objetivo, no hay colisión
    }

    // Obtener la geometría de la bala y el objetivo (blackRect)
    QRect bulletRect = bulletLabel->geometry();
    QRect targetRect = collisionTarget->geometry();

    // Verificar si los rectángulos se intersectan (colisión)
    return bulletRect.intersects(targetRect);
}
