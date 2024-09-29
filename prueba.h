#ifndef PRUEBA_H
#define PRUEBA_H

#include "Tank.h"
#include <QLabel>
#include <QPixmap>

class ImageWindow : public QWidget {
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);
    ~ImageWindow() override = default;

private:
    Tank *yellowTank;  // Instancia de un tanque
};

#endif //PRUEBA_H
