//
// Created by zerui on 24/10/2023.
//

#ifndef EDGE_DETECTION_KERNALS_H
#define EDGE_DETECTION_KERNALS_H
#define ROWS 3
#define COLS 3

typedef struct {
    int arr[COLS];
} array;

typedef struct {
    array arr[ROWS];
} matrix;

const matrix sobelx = {{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}};
const matrix sobely = {{{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}}};
const matrix prewittx = {{{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}}};
const matrix prewitty = {{{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}}};
const matrix robertsx = {{{1, 0}, {0, -1}}};
const matrix robertsy = {{{0, 1}, {-1, 0}}};
const matrix scharrx = {{{3, 10, 3}, {0, 0, 0}, {-3, -10, -3}}};
const matrix scharry = {{{3, 0, -3}, {10, 0, -10}, {3, 0 ,-3}}};

#endif //EDGE_DETECTION_KERNALS_H
