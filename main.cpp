#include <QApplication>
#include "prueba.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Crear y mostrar la ventana de la imagen
    ImageWindow window;
    window.show();

    return app.exec();
}