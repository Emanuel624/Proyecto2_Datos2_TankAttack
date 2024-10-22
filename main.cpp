#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QScreen>
#include <QRandomGenerator>
#include <QMessageBox>  // Incluir QMessageBox para mostrar mensajes
#include "GridGraph.h"
#include "Player.h"
#include "CustomView.h"
#include "PowerUp.h"


// Variable global para controlar el turno
int currentPlayerTurn = 0;

void switchTurn(Player& player1, Player& player2, QWidget* parent);

// Función para manejar la selección del tanque
void handleTankSelection(Tank* tank, CustomView& view, Player& currentPlayer, QWidget* parent) {
    if (currentPlayerTurn == currentPlayer.getId()) {  // Solo permitir la selección si es el turno del jugador correcto
        if (currentPlayer.canTakeAction()) {
            view.selectTank(tank);  // Seleccionar el tanque usando CustomView
            // No mostrar ningún mensaje aquí para eliminar el mensaje de "Esperando el movimiento..."
        } else {
            QMessageBox::information(parent, "Acción no permitida", QString::fromStdString(currentPlayer.getName()) + " ya ha realizado una acción en este turno.");
        }
    } else {
        QMessageBox::information(parent, "Turno incorrecto", "No es el turno de " + QString::fromStdString(currentPlayer.getName()) + ". No puedes seleccionar este tanque.");
    }
}

// Función para cambiar de turno
void switchTurn(Player& player1, Player& player2, QWidget* parent) {
    // Resetear las acciones del jugador anterior
    if (currentPlayerTurn == player1.getId()) {
        player1.resetActions();  // Reiniciar acciones al cambiar de turno
        // Reset precision movement for player1's tanks
        for (int i = 0; i < 4; ++i) {
            Tank* tank = player1.getTank(i);
            if (tank) {
                tank->setPrecisionMovimientoEffect(false);  // Reset after the turn
            }
        }
    } else {
        player2.resetActions();
        // Reset precision movement for player2's tanks
        for (int i = 0; i < 4; ++i) {
            Tank* tank = player2.getTank(i);
            if (tank) {
                tank->setPrecisionMovimientoEffect(false);  // Reset after the turn
            }
        }
    }

    // Change the current player's turn
    currentPlayerTurn = (currentPlayerTurn == player1.getId()) ? player2.getId() : player1.getId();
    QString nextPlayerName = (currentPlayerTurn == player1.getId()) ? QString::fromStdString(player1.getName()) : QString::fromStdString(player2.getName());
    QMessageBox::information(parent, "Cambio de turno", "Es el turno del jugador " + nextPlayerName);
}


// Función para generar un PowerUp aleatorio
PowerUp* generateRandomPowerUp(int cellWidth, int cellHeight) {
    int powerUpType = QRandomGenerator::global()->bounded(4);  // Generar un número aleatorio entre 0 y 3
    switch (powerUpType) {
        case 0:
            return new DobleTurno(cellWidth, cellHeight);
        case 1:
            return new PrecisionMovimiento(cellWidth, cellHeight);
        case 2:
            return new PrecisionAtaque(cellWidth, cellHeight);
        case 3:
            default:
                return new PoderAtaque(cellWidth, cellHeight);
    }
}

// Función para asignar PowerUps aleatorios a un jugador
void assignRandomPowerUpsToPlayer(Player& player, int numberOfPowerUps, int cellWidth, int cellHeight) {
    for (int i = 0; i < numberOfPowerUps; ++i) {
        PowerUp* powerUp = generateRandomPowerUp(cellWidth, cellHeight);
        player.addPowerUp(powerUp);  // Añadir el PowerUp a la cola del jugador
    }
}

//Funcion que ejecuta el programa.
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Configuración de la pantalla
    int viewWidth = 1500;
    int viewHeight = 1000;
    int rows = 10;
    int cols = 20;

    // Crear la escena gráfica
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, viewWidth, viewHeight);

    // Crear el grafo que representa la cuadrícula
    GridGraph graph(rows, cols);

    // Generar obstáculos en el grafo
    float obstacleDensity = 0.1;
    graph.generateObstacles(obstacleDensity);

    // Configuración de las celdas
    float scaleFactor = 0.8;
    int cellWidth = (viewWidth / cols) * scaleFactor;
    int cellHeight = (viewHeight / rows) * scaleFactor;

    // Dibujar el grid en la escena
    graph.drawGrid(scene, viewWidth, viewHeight, scaleFactor);

    // Crear jugadores y asignar tanques con sus propiedades
    Player player1(1, "Player 1");
    player1.setTank(0, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/RedTank.png", 1);
    player1.setTank(1, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/RedTank.png", 1);
    player1.setTank(2, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/BlueTank.png", 0);
    player1.setTank(3, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/BlueTank.png", 0);

    Player player2(2, "Player 2");
    player2.setTank(0, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/YellowTank.png", 1);
    player2.setTank(1, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/YellowTank.png", 1);
    player2.setTank(2, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/LightBlueTank.png", 0);
    player2.setTank(3, 100, "/home/emanuel/CLionProjects/Proyecto2_Datos2_TankAttack/Tanks/LightBlueTank.png", 0);

    // Colocar los tanques en el grid
    for (int i = 0; i < 4; ++i) {
        graph.addTank(*player1.getTank(i), i * 3, 0, scene, cellWidth, cellHeight);         // Tanques jugador 1 a la izquierda
        graph.addTank(*player2.getTank(i), i * 3, cols - 1, scene, cellWidth, cellHeight);  // Tanques jugador 2 a la derecha
    }

    // Asignar PowerUps aleatorios a ambos jugadores
    int numberOfPowerUpsPerPlayer = 4;  // Puedes ajustar el número de PowerUps que recibe cada jugador
    assignRandomPowerUpsToPlayer(player1, numberOfPowerUpsPerPlayer, cellWidth, cellHeight);
    assignRandomPowerUpsToPlayer(player2, numberOfPowerUpsPerPlayer, cellWidth, cellHeight);

    // Crear un QFont para usarlo con texto en negrita
    QFont boldFont;
    boldFont.setBold(true);

    // Añadir texto de "Jugador 1" y "Jugador 2" en la escena y aplicar el estilo en negrita
    QGraphicsTextItem* player1Label = scene.addText("Jugador 1");
    player1Label->setFont(boldFont);  // Aplicar fuente en negrita
    player1Label->setPos(viewWidth + 10, 10);  // Posición para el texto del jugador 1

    QGraphicsTextItem* player2Label = scene.addText("Jugador 2");
    player2Label->setFont(boldFont);  // Aplicar fuente en negrita
    player2Label->setPos(viewWidth + 10, 260);  // Posición para el texto del jugador 2

    // Mostrar los PowerUps de cada jugador en la escena
    player1.showPowerUpsOnScene(&scene, viewWidth + 10, 50);  // Posición de los PowerUps del jugador 1
    player2.showPowerUpsOnScene(&scene, viewWidth + 10, 300);  // Posición de los PowerUps del jugador 2

    // Crear la vista personalizada (aquí se pasa player1, player2, y currentPlayerTurn)
    CustomView view(&scene, graph, cellWidth, cellHeight, player1, player2, currentPlayerTurn);
    view.setWindowTitle("Tank Attack!");
    view.resize(viewWidth, viewHeight);
    view.show(); // Mostrar la vista

    // Seleccionar aleatoriamente cuál jugador comienza la partida
    currentPlayerTurn = QRandomGenerator::global()->bounded(1, 3); // Jugador 1 o 2
    QMessageBox::information(&view, "Inicio del juego", "Comienza el jugador " + QString::number(currentPlayerTurn));

    // Conectar la señal de selección del tanque para los tanques del jugador 1
    for (int i = 0; i < 4; ++i) {
        QObject::connect(player1.getTank(i), &Tank::tankSelected, [&view, &player1](Tank* tank) {
            handleTankSelection(tank, view, player1, &view);
        });
        QObject::connect(player2.getTank(i), &Tank::tankSelected, [&view, &player2](Tank* tank) {
            handleTankSelection(tank, view, player2, &view);
        });
    }

    // Conectar la señal de movimiento completado para los tanques del jugador 1
    for (int i = 0; i < 4; ++i) {
        QObject::connect(player1.getTank(i), &Tank::movementCompleted, [&player1, &player2, &view]() {
            switchTurn(player1, player2, &view);
        });
        QObject::connect(player2.getTank(i), &Tank::movementCompleted, [&player1, &player2, &view]() {
            switchTurn(player1, player2, &view);
        });
    }

    return app.exec();
}

