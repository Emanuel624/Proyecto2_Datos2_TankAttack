#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "Player.h"
#include "PowerUpQueue.h"
#include "PowerUp.h"
#include "Tank.h"

Player::Player(int id, const std::string& name)
    : id(id), name(name), powerUps(new PowerUpQueue()), moved(false), shot(false), usedPowerUp(false) {
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

// Añadir un PowerUp a la cola del jugador
void Player::addPowerUp(PowerUp* powerUp) {
    powerUps->enqueue(powerUp); // Agrega el PowerUp a la cola
}

// Usar (y remover) el PowerUp de la cola
PowerUp* Player::usePowerUp() {
    return powerUps->dequeue(); // Usa y elimina el PowerUp de la cola
}



void Player::useNextPowerUp(QGraphicsScene* scene, int xPosition, int yPosition) {
    if (PowerUp* powerUp = usePowerUp()) {  // Usamos el siguiente PowerUp
        powerUp->applyEffect(*this);        // Aplica el efecto al jugador
        markPowerUp();                      // Marca que un PowerUp ha sido utilizado en este turno
        delete powerUp;                     // Elimina el PowerUp usado

        // Actualizar la lista de PowerUps en la escena
        clearPowerUpsFromScene(scene, xPosition, yPosition);  // Limpia los PowerUps anteriores de la escena
        showPowerUpsOnScene(scene, xPosition, yPosition);     // Muestra la lista actualizada de PowerUps
    } else {
        qDebug() << "No hay PowerUps disponibles para usar.";  // Maneja el caso de no tener PowerUps
    }
}



// Mostrar los PowerUps en la cola (utilizando el método displayQueue de PowerUpQueue)
void Player::showPowerUps() const {
    powerUps->displayQueue();  // Mostrar los PowerUps en la terminal
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


//Mostrar los PowerUps en la ventana grafica
void Player::showPowerUpsOnScene(QGraphicsScene* scene, int xPosition, int yPosition) {
    int yOffset = 0;  // Espacio entre cada PowerUp
    PowerUpQueue::Node* current = powerUps->getFront();  // Accedemos al primer nodo de la cola
    while (current != nullptr) {
        PowerUp* powerUp = current->data;
        QGraphicsTextItem* textItem = scene->addText(powerUp->getName());  // Añadimos el nombre del PowerUp como texto
        textItem->setPos(xPosition, yPosition + yOffset);  // Coloca el texto en la posición deseada
        yOffset += 20;  // Incrementar el desplazamiento vertical para el siguiente PowerUp
        current = current->next;  // Pasamos al siguiente nodo
    }
}

void Player::clearPowerUpsFromScene(QGraphicsScene* scene, int xPosition, int yPosition) {
    // Buscar todos los ítems de texto en el área donde están los PowerUps
    QList<QGraphicsItem*> items = scene->items(QRectF(xPosition, yPosition, 200, 100)); // Ajustar el rectángulo según el área
    for (QGraphicsItem* item : items) {
        if (QGraphicsTextItem* textItem = dynamic_cast<QGraphicsTextItem*>(item)) {
            scene->removeItem(textItem);  // Eliminar el ítem de la escena
            delete textItem;  // Liberar memoria
        }
    }
}


