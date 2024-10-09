// PowerUp.h
#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>

class Player; // Declaración anticipada

class PowerUp : public QGraphicsPixmapItem {
public:
    PowerUp(const QString& imagePath, int cellWidth, int cellHeight);
    virtual void applyEffect(Player& player) = 0;
    bool checkCollision(const QGraphicsItem* other) const;
    virtual ~PowerUp() = default;
};

class DobleTurno : public PowerUp {
public:
    DobleTurno(const QString& imagePath, int cellWidth, int cellHeight) : PowerUp(imagePath, cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

class PrecisionMovimiento : public PowerUp {
public:
    PrecisionMovimiento(const QString& imagePath, int cellWidth, int cellHeight) : PowerUp(imagePath, cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

class PrecisionAtaque : public PowerUp {
public:
    PrecisionAtaque(const QString& imagePath, int cellWidth, int cellHeight) : PowerUp(imagePath, cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

class PoderAtaque : public PowerUp {
public:
    PoderAtaque(const QString& imagePath, int cellWidth, int cellHeight) : PowerUp(imagePath, cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

#endif // POWERUP_H
