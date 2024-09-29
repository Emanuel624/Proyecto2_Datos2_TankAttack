#include "prueba.h"
#include <QKeyEvent>
#include <QDebug>

ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent) {
    // Crear una instancia del tanque amarillo con 100 puntos de vida
    yellowTank = new Tank(100, "/home/emanuel/CLionProjects/Proyecto2_TankAttack/Tanks/YellowTank.png", this);

    // Mostrar el tanque en la ventana
    yellowTank->display(this);

    // Establecer un tamaño fijo para la ventana (ejemplo: 1000x700)
    this->setFixedSize(1000, 700);

    // Crear un widget que representará el rectángulo negro en la parte superior
    blackRect = new QWidget(this);  // Inicializamos blackRect aquí
    blackRect->setGeometry(0, 0, 1000, 100);
    blackRect->setStyleSheet("background-color: black;");

    // Asegurarse de que la ventana captura eventos de teclado
    setFocusPolicy(Qt::StrongFocus);  // Esto permite que capture eventos de teclado
}

void ImageWindow::keyPressEvent(QKeyEvent *event) {
    // Detectar si la tecla presionada es la barra espaciadora
    if (event->key() == Qt::Key_Space) {
        qDebug() << "Barra espaciadora presionada: disparo activado";
        yellowTank->shoot(blackRect);  // Pasa el blackRect como objetivo de colisión
    }
}
