#include "Queue.h"
#include <iostream>

Queue::Queue(int size) : capacity(size), front(0), rear(0) {
    data = new int[capacity];
}

Queue::~Queue() {
    delete[] data;
}

bool Queue::isEmpty() const {
    return front == rear;
}

void Queue::enqueue(int value) {
    if (rear < capacity) {
        data[rear++] = value;
    } else {
        std::cerr << "Error: Queue overflow\n";
    }
}

int Queue::dequeue() {
    if (!isEmpty()) {
        return data[front++];
    } else {
        std::cerr << "Error: Queue underflow\n";
        return -1;
    }
}
