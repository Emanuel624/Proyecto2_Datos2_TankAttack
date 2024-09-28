#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Inicia la aplicación Qt

    QWidget window;  // Crea una ventana básica
    window.resize(250, 150);  // Establece el tamaño de la ventana
    window.setWindowTitle("Ventana Basica");  // Establece el título de la ventana
    window.show();  // Muestra la ventana

    return app.exec();  // Inicia el bucle de eventos de Qt
}
