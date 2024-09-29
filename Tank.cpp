#include "Tank.h"
#include <QDebug>

Tank::Tank(int health, const QString &imagePath, QWidget *parent)
    : health(health), label(new QLabel(parent)) {
    // Cargar la imagen en QPixmap
    pixmap = QPixmap(imagePath);

    // Verificar si la imagen fue cargada correctamente
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde" << imagePath;
    }
}

int Tank::getHealth() const {
    return health;
}

void Tank::setHealth(int newHealth) {
    health = newHealth;
}

void Tank::display(QWidget *parent) {
    // Redimensionar la imagen a un tamaño específico (por ejemplo: 75x75)
    QPixmap scaledPixmap = pixmap.scaled(75, 75, Qt::KeepAspectRatio);

    // Asignar el QPixmap redimensionado al QLabel
    label->setPixmap(scaledPixmap);

    // Ajustar la posición y tamaño del QLabel
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(0, 100, 75, 75); // Puedes ajustar la posición como desees

    // Mostrar el QLabel
    label->show();
}
