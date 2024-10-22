#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsTextItem>
#include <QString>

class Player; // Declaración anticipada

// En PowerUp.h
class PowerUp : public QGraphicsTextItem {
public:
    PowerUp(const QString& name, int cellWidth, int cellHeight);
    virtual void applyEffect(Player& player) = 0;
    QString getName() const { return name; }
    virtual ~PowerUp() = default;

private:
    QString name;
};

class DobleTurno : public PowerUp {
public:
    DobleTurno(int cellWidth, int cellHeight) : PowerUp("Doble Turno", cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

class PrecisionMovimiento : public PowerUp {
public:
    PrecisionMovimiento(int cellWidth, int cellHeight) : PowerUp("Precisión Movimiento", cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

class PrecisionAtaque : public PowerUp {
public:
    PrecisionAtaque(int cellWidth, int cellHeight) : PowerUp("Precisión Ataque", cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

class PoderAtaque : public PowerUp {
public:
    PoderAtaque(int cellWidth, int cellHeight) : PowerUp("Poder de Ataque", cellWidth, cellHeight) {}
    void applyEffect(Player& player) override;
};

#endif // POWERUP_H
