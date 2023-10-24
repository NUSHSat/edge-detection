//
// Created by zerui on 24/10/2023.
//

#ifndef EDGE_DETECTION_IMAGE_H
#define EDGE_DETECTION_IMAGE_H
#include "stdlib.h"

typedef struct {
    int width;
    int height;
    unsigned char* data;
} Image;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point* data;
    int front;
    int rear;
} Queue;

Queue* create_queue(int size) {
    Queue* queue = malloc(sizeof(Queue));
    queue->data = malloc(size * sizeof(Point));
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void enqueue(Queue* queue, Point point) {
    queue->data[++queue->rear] = point;
}

Point dequeue(Queue* queue) {
    return queue->data[queue->front++];
}

int is_empty(Queue* queue) {
    return queue->front > queue->rear;
}

void free_queue(Queue* queue) {
    free(queue->data);
    free(queue);
}

void magnitude(Image* input, const Image gx, const Image gy);
#endif //EDGE_DETECTION_IMAGE_H
