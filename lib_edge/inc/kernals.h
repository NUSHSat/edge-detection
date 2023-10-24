//
// Created by zerui on 24/10/2023.
//

#ifndef EDGE_DETECTION_KERNALS_H
#define EDGE_DETECTION_KERNALS_H
#include "math.h"

const float sobelx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const float sobely[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
const float prewittx[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
const float prewitty[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
const float scharrx[3][3] = {{3, 10, 3}, {0, 0, 0}, {-3, -10, -3}};
const float scharry[3][3] = {{3, 0, -3}, {10, 0, -10}, {3, 0 ,-3}};

float gaussian_kernel(float sigma, int x, int y) {
    float s = 2 * sigma * sigma;
    return exp(-(x * x + y * y) / s) / s / M_PI;
}

void get_gaussian_kernel(float sigma, int l, float kernel[l][l]) {
    float sum = 0;
    for (int x = -2; x <= 2; x++)
        for (int y = -2; y <= 2; y++)
            sum += (kernel[x + 2][y + 2] = gaussian_kernel(sigma, x, y));
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            kernel[i][j] /= sum;
}
#endif //EDGE_DETECTION_KERNALS_H
