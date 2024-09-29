#include "prueba.h"
#include <QDebug>

ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent) {
    // Crear una instancia del tanque amarillo con 100 puntos de vida
    yellowTank = new Tank(100, "/home/emanuel/CLionProjects/Proyecto2_TankAttack/Tanks/YellowTank.png", this);

    // Mostrar el tanque en la ventana
    yellowTank->display(this);

    // Establecer un tamaño fijo para la ventana (ejemplo: 1000x700)
    this->setFixedSize(1000, 700);

    // Crear un widget que representará el rectángulo negro en la parte superior
    QWidget *blackRect = new QWidget(this);

    // Definir el tamaño y la posición del rectángulo (ejemplo: 1000x100 píxeles en la parte superior)
    blackRect->setGeometry(0, 0, 500, 100);

    // Aplicar el color negro al widget
    blackRect->setStyleSheet("background-color: black;");
}
