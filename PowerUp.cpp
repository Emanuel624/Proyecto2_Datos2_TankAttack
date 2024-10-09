#include "PowerUp.h"

// Constructor de PowerUp con tamaño de celda
PowerUp::PowerUp(const QString& imagePath, int cellWidth, int cellHeight) {
    QPixmap pixmap(imagePath);
    setPixmap(pixmap.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio));
}

bool PowerUp::checkCollision(const QGraphicsItem* other) const {
    return collidesWithItem(other);
}

// Implementaciones de los efectos de cada PowerUp
void DobleTurno::applyEffect(Player& player) {
    // Implementar lógica para aplicar doble turno al jugador
}

void PrecisionMovimiento::applyEffect(Player& player) {
    // Implementar lógica para mejorar precisión de movimiento
}

void PrecisionAtaque::applyEffect(Player& player) {
    // Implementar lógica para mejorar precisión de ataque
}

void PoderAtaque::applyEffect(Player& player) {
    // Implementar lógica para aumentar poder de ataque
}
