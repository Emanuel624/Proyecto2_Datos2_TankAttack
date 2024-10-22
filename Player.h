#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "PowerUpQueue.h"
#include "PowerUp.h"  // Asegurarse de incluir PowerUp
#include "Tank.h"

class Player {
public:
    Player(int id, const std::string& name);
    ~Player();

    void setTank(int index, int health, const QString& imagePath, int type);
    Tank* getTank(int index) const;
    int getId();
    std::string getName();  // Metodo getName

    void addPowerUp(PowerUp* powerUp);
    PowerUp* usePowerUp();
    void showPowerUps() const;
    void showPowerUpsOnScene(QGraphicsScene* scene, int xPosition, int yPosition);
    void clearPowerUpsFromScene(QGraphicsScene* scene, int xPosition, int yPosition);
    void useNextPowerUp(QGraphicsScene* scene, int xPosition, int yPosition);


    // Nuevos métodos para control de acciones del turno
    bool hasMoved() const;
    bool hasShot() const;
    bool hasUsedPowerUp() const;
    bool canTakeAction() const; // Verifica si puede realizar alguna acción
    void markMove();
    void markShot();
    void markPowerUp();
    void resetActions(); // Reinicia las acciones al inicio del turno

private:
    int id;
    std::string name;
    Tank* tanks[4];
    PowerUpQueue* powerUps;

    // Variables para rastrear si el jugador ya realizó alguna acción
    bool moved;      // Indica si ya movió el tanque
    bool shot;       // Indica si ya disparó
    bool usedPowerUp; // Indica si ya usó un PowerUp
};

#endif // PLAYER_H
