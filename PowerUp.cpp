#include "PowerUp.h"
#include "Player.h"
#include <QGraphicsScene>

// Constructor de PowerUp
PowerUp::PowerUp(const QString& name, int cellWidth, int cellHeight)
    : QGraphicsTextItem(), name(name) {
    setPlainText(name);  // Mostrar el nombre como texto
}


// Implementación de DobleTurno
void DobleTurno::applyEffect(Player& player) {
    qDebug() << "Aplicando efecto de Doble Turno al jugador: " << QString::fromStdString(player.getName());
    player.setDoubleTurn(true);  // Set the player for double turn
}



// Implementación de PrecisionMovimiento
void PrecisionMovimiento::applyEffect(Player& player) {
    // Lógica para aplicar el efecto "Precisión Movimiento" en el jugador
    qDebug() << "Aplicando efecto de Precisión Movimiento al jugador: " << QString::fromStdString(player.getName());

    // Cambiar la lógica de movimiento del tanque
    for (int i = 0; i < 4; ++i) {
        Tank* tank = player.getTank(i);
        if (tank) {
            // Aplicar la lógica temporal de movimiento
            tank->setPrecisionMovimientoEffect(true);
        }
    }
}

// Implementación de PoderAtaque
void PoderAtaque::applyEffect(Player& player) {
    qDebug() << "Aplicando efecto de Poder de Ataque al jugador: " << QString::fromStdString(player.getName());
    player.activateFullDamagePowerUp();  // Activa el PowerUp de daño completo
}

// Implementación de PrecisionAtaque
void PrecisionAtaque::applyEffect(Player& player) {
    // Lógica para aplicar el efecto "Precisión Ataque" en el jugador
    // Por ejemplo, mejorar la precisión de los ataques del jugador
    qDebug() << "Aplicando efecto de Precisión Ataque al jugador: " << QString::fromStdString(player.getName());
}