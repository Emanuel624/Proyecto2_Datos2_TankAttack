#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QScreen>
#include "GridGraph.h"
#include "Tank.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int rows = 15;
    int cols = 30;

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, screenWidth, screenHeight);

    GridGraph graph(rows, cols);

    // Generar obstáculos con una densidad del 10% del mapa
    float obstacleDensity = 0.1;
    graph.generateObstacles(obstacleDensity);

    float scaleFactor = 0.8;
    int cellWidth = (screenWidth / cols) * scaleFactor;
    int cellHeight = (screenHeight / rows) * scaleFactor;

    graph.drawGrid(scene, screenWidth, screenHeight, scaleFactor);

    //Tanques jugador 1
    Tank player1TankRed1(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/RedTank.png");
    Tank player1TankRed2(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/RedTank.png");
    Tank player1TankBlue1(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/BlueTank.png");
    Tank player1TankBlue2(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/BlueTank.png");


    //Tanques jugador 2
    Tank player2TankYellow1(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/YellowTank.png");
    Tank player2TankYellow2(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/YellowTank.png");
    Tank player2TankLight1(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/LightBlueTank.png");
    Tank player2TankLight2(100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/LightBlueTank.png");


    // Colocar los tanques en diferentes celdas del grid
    graph.addTank(player1TankRed1, 2, 0, scene, cellWidth, cellHeight);
    graph.addTank(player1TankRed2, 5, 1, scene, cellWidth, cellHeight);
    graph.addTank(player1TankBlue1, 9, 0, scene, cellWidth, cellHeight);
    graph.addTank(player1TankBlue2, 12, 1, scene, cellWidth, cellHeight);

    graph.addTank(player2TankYellow1, 2, 29, scene, cellWidth, cellHeight);
    graph.addTank(player2TankYellow2, 5, 28, scene, cellWidth, cellHeight);
    graph.addTank(player2TankLight1, 9, 29, scene, cellWidth, cellHeight);
    graph.addTank(player2TankLight2, 12, 28, scene, cellWidth, cellHeight);

    QGraphicsView view(&scene);
    view.setWindowTitle("Tank Attack!");
    view.showFullScreen();

    return app.exec();
}
