// PriorityQueue.h
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

class PriorityQueue {
private:
    int* data;
    int* priorities;
    int capacity, size;

public:
    PriorityQueue(int capacity);
    ~PriorityQueue();

    bool isEmpty() const;
    void enqueue(int value, int priority);
    int dequeue();
};

#endif // PRIORITYQUEUE_H
