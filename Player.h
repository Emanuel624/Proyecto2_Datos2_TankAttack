#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>  // Incluir QObject
#include <string>
#include "Tank.h"
#include "PowerUpQueue.h"
#include <QGraphicsScene>

class Player {
public:
    Player(int id, const std::string& name);
    ~Player();

    void setTank(int index, int health, const QString& imagePath, int type);
    Tank* getTank(int index) const;
    int getId();
    std::string getName();  // Metodo getName
    int getHealth() const;

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

    //Parametros para powerUp de dobles turnos
    void setDoubleTurn(bool value);
    bool getDoubleTurn() const;

    int countActiveTanks() const;

    void activateFullDamagePowerUp();
    void deactivateFullDamagePowerUp();
    bool isFullDamagePowerUpActive() const;

private:
    int id;
    std::string name;
    Tank* tanks[4];
    PowerUpQueue* powerUps;

    // Variables para rastrear si el jugador ya realizó alguna acción
    bool moved;      // Indica si ya movió el tanque
    bool shot;       // Indica si ya disparó
    bool usedPowerUp; // Indica si ya usó un PowerUp
    bool hasDoubleTurn = false; // Indica si tiene el PowerUP de doble turno activo
    int health;

    bool fullDamagePowerUpActive = false;
};

#endif // PLAYER_H
