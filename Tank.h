#ifndef TANK_H
#define TANK_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class Tank {
public:
    // Constructor para inicializar el tanque con vida y una imagen
    Tank(int health, const QString &imagePath, QWidget *parent = nullptr);

    // Métodos para obtener atributos
    int getHealth() const;
    void setHealth(int health);

    // Métodos para mostrar el tanque en la pantalla
    void display(QWidget *parent);

private:
    int health;        // Atributo para almacenar la vida del tanque
    QPixmap pixmap;    // Imagen que representa al tanque
    QLabel *label;     // QLabel para mostrar la imagen
};

#endif //TANK_H
