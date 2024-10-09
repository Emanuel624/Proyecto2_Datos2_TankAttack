#ifndef POWERUPQUEUE_H
#define POWERUPQUEUE_H

#include "PowerUp.h"


class PowerUpQueue {
private:
    struct Node {
        PowerUp* data;
        Node* next;
        Node(PowerUp* powerUp) : data(powerUp), next(nullptr) {}
    };

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
};

#endif // POWERUPQUEUE_H
