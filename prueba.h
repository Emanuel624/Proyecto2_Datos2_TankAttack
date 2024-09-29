#ifndef PRUEBA_H
#define PRUEBA_H

#include <QWidget>
#include "Tank.h"  // Incluir la clase Tank

class ImageWindow : public QWidget {
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);

protected:
    // Sobrescribe el metodo para manejar eventos de teclado
    void keyPressEvent(QKeyEvent *event) override;

private:
    Tank *yellowTank;  // Instancia de un tanque
    QWidget *blackRect;  // Declaración del blackRect como miembro de la clase
};

#endif // PRUEBA_H
