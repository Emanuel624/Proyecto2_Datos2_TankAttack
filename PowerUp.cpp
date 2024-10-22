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
    // Lógica para aplicar el efecto "Doble Turno" en el jugador
    // Por ejemplo, permitirle al jugador realizar dos movimientos en su turno
    qDebug() << "Aplicando efecto de Doble Turno al jugador: " << QString::fromStdString(player.getName());
}

// Implementación de PrecisionMovimiento
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

// Implementación de PrecisionAtaque
void PrecisionAtaque::applyEffect(Player& player) {
    // Lógica para aplicar el efecto "Precisión Ataque" en el jugador
    // Por ejemplo, mejorar la precisión de los ataques del jugador
    qDebug() << "Aplicando efecto de Precisión Ataque al jugador: " << QString::fromStdString(player.getName());
}

// Implementación de PoderAtaque
void PoderAtaque::applyEffect(Player& player) {
    // Lógica para aplicar el efecto "Poder de Ataque" en el jugador
    // Por ejemplo, aumentar el daño de los ataques del jugador
    qDebug() << "Aplicando efecto de Poder de Ataque al jugador: " << QString::fromStdString(player.getName());
}
