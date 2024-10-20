#include "PriorityQueue.h"
#include <iostream>

PriorityQueue::PriorityQueue(int capacity) : capacity(capacity), size(0) {
    data = new int[capacity];
    priorities = new int[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] data;
    delete[] priorities;
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

void PriorityQueue::enqueue(int value, int priority) {
    if (size == capacity) {
        std::cerr << "Error: Queue overflow\n";
        return;
    }
    data[size] = value;
    priorities[size] = priority;
    size++;
}

int PriorityQueue::dequeue() {
    if (isEmpty()) {
        std::cerr << "Error: Queue underflow\n";
        return -1;
    }

    int minPriorityIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (priorities[i] < priorities[minPriorityIndex]) {
            minPriorityIndex = i;
        }
    }

    int value = data[minPriorityIndex];
    data[minPriorityIndex] = data[size - 1];
    priorities[minPriorityIndex] = priorities[size - 1];
    size--;
    return value;
}
