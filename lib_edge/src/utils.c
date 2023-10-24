//
// Created by zerui on 24/10/2023.
//
#include <math.h>
#include "utils.h"

void magnitude(Image* input, const Image gx, const Image gy) {
    unsigned char *line;
    const unsigned char *gx_line, *gy_line;

    for (int y = 0; y < input->height; y++) {
        line = input->data + y * input->width;
        gx_line = gx.data + y * gx.width;
        gy_line = gy.data + y * gy.width;

        for (int x = 0; x < input->width; x++)
            line[x] = fmin(255, hypot(gx_line[x], gy_line[x]));
    }
}

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
