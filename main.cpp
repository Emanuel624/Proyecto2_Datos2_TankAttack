#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QScreen>
#include "GridGraph.h"
#include "Player.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Definir el tamaño de la ventana
    int viewWidth = 1500;
    int viewHeight = 1000;

    int rows = 10;
    int cols = 20;

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, viewWidth, viewHeight);

    GridGraph graph(rows, cols);

    // Generar obstáculos con una densidad del 10% del mapa
    float obstacleDensity = 0.1;
    graph.generateObstacles(obstacleDensity);

    float scaleFactor = 0.8;
    int cellWidth = (viewWidth / cols) * scaleFactor;
    int cellHeight = (viewHeight / rows) * scaleFactor;

    graph.drawGrid(scene, viewWidth, viewHeight, scaleFactor);

    // Crear jugadores y asignar tanques con salud e imagen
    Player player1(1, "Player 1");
    player1.setTank(0, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/RedTank.png");
    player1.setTank(1, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/RedTank.png");
    player1.setTank(2, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/BlueTank.png");
    player1.setTank(3, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/BlueTank.png");

    Player player2(2, "Player 2");
    player2.setTank(0, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/YellowTank.png");
    player2.setTank(1, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/YellowTank.png");
    player2.setTank(2, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/LightBlueTank.png");
    player2.setTank(3, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/LightBlueTank.png");

    // Colocar los tanques en el grid
    for (int i = 0; i < 4; ++i) {
        graph.addTank(*player1.getTank(i), i * 2 + 1, 0, scene, cellWidth, cellHeight);     // Tanques jugador 1 en la izquierda
        graph.addTank(*player2.getTank(i), i * 2 + 1, cols - 1, scene, cellWidth, cellHeight); // Tanques jugador 2 en la derecha
    }

    // Generar los PowerUps en celdas disponibles
    float powerUpDensity = 0.02; // Un 2% de las celdas
    graph.generatePowerUps(scene, powerUpDensity, cellWidth, cellHeight);

    QGraphicsView view(&scene);
    view.setWindowTitle("Tank Attack!");

    // Ajustar el tamaño de la ventana
    view.resize(viewWidth, viewHeight);
    view.show(); // Mostrar con tamaño ajustado, sin pantalla completa

    return app.exec();
}
