#include "Player.h"
#include "PowerUpQueue.h"  // Incluye la implementación completa
#include "PowerUp.h"       // Incluye la implementación completa

Player::Player(int id, const std::string& name) : id(id), powerUps(new PowerUpQueue()) {
    for (int i = 0; i < 4; ++i) {
        tanks[i] = nullptr; // Inicializar los punteros de tanques a nullptr
    }
}

Player::~Player() {
    for (int i = 0; i < 4; ++i) {
        delete tanks[i]; // Liberar la memoria de cada tanque
    }
    delete powerUps; // Liberar la memoria de la cola de PowerUps
}

void Player::setTank(int index, int health, const QString& imagePath) {
    if (index >= 0 && index < 4) {
        delete tanks[index]; // Eliminar el tanque existente si lo hay
        tanks[index] = new Tank(health, imagePath); // Crear y asignar un nuevo tanque
    }
}

Tank* Player::getTank(int index) const {
    if (index >= 0 && index < 4) {
        return tanks[index]; // Retorna el tanque en la posición indicada
    }
    return nullptr; // Retorna nullptr si el índice no es válido
}

void Player::addPowerUp(PowerUp* powerUp) {
    powerUps->enqueue(powerUp); // Agrega el PowerUp a la cola
}

PowerUp* Player::usePowerUp() {
    return powerUps->dequeue(); // Usa y elimina el PowerUp de la cola
}
