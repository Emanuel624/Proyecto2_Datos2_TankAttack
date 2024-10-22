#include "PowerUpQueue.h"
#include <iostream>

// Constructor
PowerUpQueue::PowerUpQueue() : front(nullptr), rear(nullptr), size(0) {}

// Destructor
PowerUpQueue::~PowerUpQueue() {
    while (!isEmpty()) {
        dequeue(); // Eliminar todos los nodos de la cola
    }
}

// Enqueue: Añadir un PowerUp al final de la cola
void PowerUpQueue::enqueue(PowerUp* powerUp) {
    Node* newNode = new Node(powerUp);
    if (isEmpty()) {
        front = rear = newNode;  // Si la cola está vacía, el nuevo nodo es tanto el frente como el final
    } else {
        rear->next = newNode;
        rear = newNode;  // El nuevo nodo se convierte en el último
    }
    size++;
}

// Dequeue: Remover un PowerUp del frente de la cola
PowerUp* PowerUpQueue::dequeue() {
    if (isEmpty()) {
        std::cerr << "Error: La cola está vacía, no se puede hacer dequeue." << std::endl;
        return nullptr;
    }

    Node* temp = front;
    PowerUp* powerUp = front->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;  // Si la cola queda vacía después de la operación
    }

    delete temp;  // Liberar la memoria del nodo
    size--;
    return powerUp;
}

// Peek: Ver el primer PowerUp sin removerlo
PowerUp* PowerUpQueue::peek() const {
    if (isEmpty()) {
        std::cerr << "Error: La cola está vacía, no se puede hacer peek." << std::endl;
        return nullptr;
    }
    return front->data;
}

// Verificar si la cola está vacía
bool PowerUpQueue::isEmpty() const {
    return size == 0;
}

// Obtener el tamaño de la cola
int PowerUpQueue::getSize() const {
    return size;
}

