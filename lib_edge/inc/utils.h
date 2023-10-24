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

Queue* create_queue(int size);
void enqueue(Queue* queue, Point point);
Point dequeue(Queue* queue);
int is_empty(Queue* queue);
void free_queue(Queue* queue);
void magnitude(Image* input, Image gx, Image gy);
#endif //EDGE_DETECTION_IMAGE_H
