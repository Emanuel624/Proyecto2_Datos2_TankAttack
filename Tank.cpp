#include "Tank.h"
#include <QtWidgets/QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

Tank::Tank(int health, const QString &imagePath, QWidget *parent)
    : QWidget(parent), health(health), pixmap(imagePath) {
    // Verificar si la imagen fue cargada correctamente
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde" << imagePath;
    }
}

void Tank::display(QGraphicsScene &scene, int row, int col, int cellWidth, int cellHeight) {
    // Redimensionar la imagen del tanque
    QPixmap scaledPixmap = pixmap.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio);

    // Crear un QGraphicsPixmapItem para mostrar el tanque en el grid
    QGraphicsPixmapItem *tankItem = new QGraphicsPixmapItem(scaledPixmap);

    // Calcular la posición en el grid
    int x = col * cellWidth;
    int y = row * cellHeight;

    // Posicionar el tanque en la escena
    tankItem->setPos(x, y);
    scene.addItem(tankItem);
}
