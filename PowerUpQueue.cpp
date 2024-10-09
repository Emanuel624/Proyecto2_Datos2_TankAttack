#include "PowerUpQueue.h"
#include "PowerUp.h"

PowerUpQueue::PowerUpQueue() : front(nullptr), rear(nullptr), size(0) {}

PowerUpQueue::~PowerUpQueue() {
    while (!isEmpty()) {
        delete dequeue(); // Dequeue and delete each PowerUp
    }
}

void PowerUpQueue::enqueue(PowerUp* powerUp) {
    Node* newNode = new Node(powerUp);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    ++size;
}

PowerUp* PowerUpQueue::dequeue() {
    if (isEmpty()) return nullptr;

    Node* temp = front;
    PowerUp* powerUp = front->data;
    front = front->next;
    if (!front) rear = nullptr;

    delete temp;
    --size;
    return powerUp;
}

PowerUp* PowerUpQueue::peek() const {
    if (isEmpty()) return nullptr;
    return front->data;
}

bool PowerUpQueue::isEmpty() const {
    return front == nullptr;
}

int PowerUpQueue::getSize() const {
    return size;
}
