#include "Player.h"
#include "PowerUpQueue.h"
#include "PowerUp.h"
#include "Tank.h"

Player::Player(int id, const std::string& name) : id(id), name(name), powerUps(new PowerUpQueue()), moved(false), shot(false), usedPowerUp(false) {
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

void Player::setTank(int index, int health, const QString& imagePath, int type) {
    if (index >= 0 && index < 4) {
        delete tanks[index]; // Eliminar el tanque existente si lo hay
        tanks[index] = new Tank(health, imagePath, type); // Crear y asignar un nuevo tanque con tipo
    }
}

Tank* Player::getTank(int index) const {
    if (index >= 0 && index < 4) {
        return tanks[index]; // Retorna el tanque en la posición indicada
    }
    return nullptr; // Retorna nullptr si el índice no es válido
}

int Player::getId() {
    return id;
}

std::string Player::getName() {
    return name;
}

void Player::addPowerUp(PowerUp* powerUp) {
    powerUps->enqueue(powerUp); // Agrega el PowerUp a la cola
}

PowerUp* Player::usePowerUp() {
    return powerUps->dequeue(); // Usa y elimina el PowerUp de la cola
}

// Nuevos métodos para rastrear acciones del turno

bool Player::hasMoved() const {
    return moved;
}

bool Player::hasShot() const {
    return shot;
}

bool Player::hasUsedPowerUp() const {
    return usedPowerUp;
}

// Verifica si puede realizar alguna acción
bool Player::canTakeAction() const {
    return !moved && !shot && !usedPowerUp; // Solo si no ha hecho ninguna acción
}

// Marcar acciones
void Player::markMove() {
    moved = true;
}

void Player::markShot() {
    shot = true;
}

void Player::markPowerUp() {
    usedPowerUp = true;
}

// Reiniciar las acciones para el nuevo turno
void Player::resetActions() {
    moved = false;
    shot = false;
    usedPowerUp = false;
}
