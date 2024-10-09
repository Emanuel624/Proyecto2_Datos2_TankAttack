#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Tank.h"

// Declaración anticipada de PowerUpQueue
class PowerUp;
class PowerUpQueue;

class Player {
private:
    int id;
    Tank* tanks[4];  // Un array que contiene los 4 tanques por jugador
    PowerUpQueue* powerUps; // Puntero a PowerUpQueue para manejar PowerUps

public:
    Player(int id, const std::string& name);
    ~Player();  // Destructor para liberar la memoria

    void setTank(int index, int health, const QString& imagePath);
    Tank* getTank(int index) const;

    // Métodos relacionados con los PowerUps
    void addPowerUp(PowerUp* powerUp);  // Agregar un PowerUp a la cola
    PowerUp* usePowerUp();              // Usar y sacar un PowerUp de la cola
};

#endif // PLAYER_H
