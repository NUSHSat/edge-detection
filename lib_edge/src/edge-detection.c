//
// Created by zerui on 24/10/2023.
//
#include "kernals.h"
#include "math.h"
#include "utils.h"
#include "stdlib.h"
#include "string.h"


Image convolution(const int kernel[3][3], const Image* image) {
    int offsetx = 3 / 2, offsety = 3 / 2;
    Image out = {image->width, image->height, malloc(image->width * image->height)};

    int sum;
    unsigned char *line;
    const unsigned char *lookup_line;

    for (int y = 0; y < image->height; y++) {
        line = out.data + y * image->width;
        for (int x = 0; x < image->width; x++) {
            sum = 0;
            for (int j = 0; j < 3; j++) {
                if (y + j < offsety || y + j >= image->height) continue;
                lookup_line = image->data + (y + j - offsety) * image->width;
                for (int i = 0; i < 3; i++) {
                    if (x + i < offsetx || x + i >= image->width)
                        continue;
                    sum += kernel[j][i] * lookup_line[x + i - offsetx];
                }
            }
            line[x] = sum > 255 ? 255 : sum < 0 ? 0 : sum;
        }
    }

    return out;
}

void hysteresis(const Image* image, float tmin, float tmax, Image* res) {
    const unsigned char *original_line;
    unsigned char *result_line;
    int ni, nj;
    Queue* edges = create_queue(image->width * image->height);
    Point point;
    for (int y = 1; y < res->height - 1; y++) {
        original_line = image->data + y * image->width;
        result_line = res->data + y * res->width;
        for (int x = 1; x < res->width - 1; x++) {
            if (original_line[x] >= tmax && result_line[x] == 0x00) {
                result_line[x] = 0xFF;
                enqueue(edges, (Point){x, y});
                while (!is_empty(edges)) {
                    point = dequeue(edges);
                    for (int j = -1; j <= 1; j++) {
                        nj = point.y + j;
                        if (nj < 0 || nj >= image->height)
                            continue;
                        original_line = image->data + nj * image->width;
                        result_line = res->data + nj * res->width;
                        for (int i = -1; i <= 1; i++) {
                            if (!i && !j)
                                continue;

                            ni = point.x + i;
                            if (ni < 0 || ni >= image->width)
                                continue;

                            if (original_line[ni] >= tmin && result_line[ni] == 0x00) {
                                result_line[ni] = 0xFF;
                                enqueue(edges, (Point){ni, nj});
                            }
                        }
                    }
                }
            }
        }
    }
    free_queue(edges);
}


Image sobel(Image* input) {
    Image res = {input->width, input->height, malloc(input->width * input->height)};
    magnitude(&res, convolution(sobelx, input), convolution(sobely, input));
    return res;
}

Image prewitt(Image* input) {
    Image res = {input->width, input->height, malloc(input->width * input->height)};
    magnitude(&res, convolution(prewittx, input), convolution(prewitty, input));
    return res;
}

Image scharr(Image* input) {
    Image res = {input->width, input->height, malloc(input->width * input->height)};
    magnitude(&res, convolution(scharrx, input), convolution(scharry, input));
    return res;
}

