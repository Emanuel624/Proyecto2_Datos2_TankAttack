#include "Tank.h"
#include <QDebug>

Tank::Tank(int health, const QString &imagePath, QWidget *parent)
    : QWidget(parent), health(health), label(new QLabel(parent)), bullet(nullptr), bulletTimer(new QTimer(this)) {
    // Cargar la imagen del tanque
    pixmap = QPixmap(imagePath);

    // Verificar si la imagen fue cargada correctamente
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde" << imagePath;
    }
}

void Tank::shoot(QWidget *collisionTarget) {
    // Crear un nuevo proyectil si no existe ya
    if (!bullet) {
        bullet = new Bullet(label->x() + label->width() / 2 - 5, label->y() - 10, parentWidget());
    }

    // Establecer el objetivo de colisión (en este caso, el blackRect)
    bullet->setTarget(collisionTarget);

    // Iniciar el disparo
    bullet->start();
}

void Tank::display(QWidget *parent) {
    // Redimensionar la imagen a un tamaño específico (por ejemplo: 75x75)
    QPixmap scaledPixmap = pixmap.scaled(75, 75, Qt::KeepAspectRatio);

    // Asignar el QPixmap redimensionado al QLabel
    label->setPixmap(scaledPixmap);

    // Ajustar la posición y tamaño del QLabel
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(500, 400, 75, 75);
    label->show();
}

void Tank::moveBullet() {
    // Verificar si la bala existe y está activa
    if (bullet) {
        bullet->moveBullet();  // Delegar el movimiento a la clase Bullet
    }
}
