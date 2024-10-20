#ifndef QUEUE_H
#define QUEUE_H

class Queue {
private:
    int* data;
    int front, rear, capacity;

public:
    Queue(int size);
    ~Queue();

    bool isEmpty() const;
    void enqueue(int value);
    int dequeue();
};

#endif // QUEUE_H
