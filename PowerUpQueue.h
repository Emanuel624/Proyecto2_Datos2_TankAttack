#ifndef POWERUPQUEUE_H
#define POWERUPQUEUE_H

#include "PowerUp.h"  // Incluir PowerUp para que sea reconocido
#include <iostream>

class PowerUpQueue {
public:
    struct Node {  // Cambiar el acceso de private a public para Node
        PowerUp* data;
        Node* next;
        Node(PowerUp* powerUp) : data(powerUp), next(nullptr) {}
    };

private:
    Node* front;
    Node* rear;
    int size;

public:
    PowerUpQueue();
    ~PowerUpQueue();

    void enqueue(PowerUp* powerUp); // Add a PowerUp to the queue
    PowerUp* dequeue();             // Remove a PowerUp from the queue
    PowerUp* peek() const;          // Peek at the front PowerUp without removing
    bool isEmpty() const;
    int getSize() const;

    // Método para mostrar la cola de PowerUps
    void displayQueue() const {
        Node* current = front;
        while (current != nullptr) {
            std::cout << current->data->getName().toStdString() << std::endl;
            current = current->next;
        }
    }

    // Método para acceder al frente de la cola
    Node* getFront() const { return front; }
};

#endif // POWERUPQUEUE_H
