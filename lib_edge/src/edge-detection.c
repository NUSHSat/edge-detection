//
// Created by zerui on 24/10/2023.
//
#include "kernals.h"
#include "math.h"
#include "utils.h"
#include "stdlib.h"
#include "string.h"


Image convolution(const Image* image, int l, const float kernel[l][l]) {
    int offsetx = l / 2, offsety = l / 2;
    Image out = {image->width, image->height, malloc(image->width * image->height)};

    float sum;
    unsigned char *line;
    const unsigned char *lookup_line;

    for (int y = 0; y < image->height; y++) {
        line = out.data + y * image->width;
        for (int x = 0; x < image->width; x++) {
            sum = 0;
            for (int j = 0; j < l; j++) {
                if (y + j < offsety || y + j >= image->height) continue;
                lookup_line = image->data + (y + j - offsety) * image->width;
                for (int i = 0; i < l; i++) {
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

Image hysteresis(const Image* image, float tmin, float tmax) {
    Image res = {image->width, image->height, malloc(image->width * image->height)};
    const unsigned char *original_line;
    unsigned char *result_line;
    int ni, nj;
    Queue* edges = create_queue(image->width * image->height);
    Point point;
    for (int y = 1; y < res.height - 1; y++) {
        original_line = image->data + y * image->width;
        result_line = res.data + y * res.width;
        for (int x = 1; x < res.width - 1; x++) {
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
                        result_line = res.data + nj * res.width;
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
    magnitude(&res, convolution(input, 3, sobelx), convolution(input, 3, sobely));
    return res;
}

Image prewitt(Image* input) {
    Image res = {input->width, input->height, malloc(input->width * input->height)};
    magnitude(&res, convolution(input, 3, prewittx), convolution(input, 3, prewitty));
    return res;
}

Image scharr(Image* input) {
    Image res = {input->width, input->height, malloc(input->width * input->height)};
    magnitude(&res, convolution(input, 3, scharrx), convolution(input, 3, scharry));
    return res;
}


Image canny(Image* input, float sigma, float tmin, float tmax) {
    float kernel[5][5] = {};
    get_gaussian_kernel(sigma, 5, kernel);
    Image res = convolution(input, 5, kernel),
        gx = convolution(&res, 3, sobelx),
        gy = convolution(&res, 3, sobely);

    magnitude(&res, gx, gy);

    unsigned char *line;
    const unsigned char *prev_line, *next_line, *gx_line, *gy_line;

    for (int y = 1; y < res.height - 1; y++) {
        line = &res.data[y * res.width];
        prev_line = &res.data[(y - 1) * res.width];
        next_line = &res.data[(y + 1) * res.width];
        gx_line = &gx.data[y * gx.width];
        gy_line = &gy.data[y * gy.width];

        for (int x = 1; x < res.width - 1; x++) {
            double at = atan2(gy_line[x], gx_line[x]);
            const double dir = fmod(at + M_PI, M_PI) / M_PI * 8;

            if (((1 >= dir || dir > 7) && line[x - 1] < line[x] && line[x + 1] < line[x]) ||
                ((1 < dir || dir <= 3) && prev_line[x - 1] < line[x] && next_line[x + 1] < line[x]) ||
                ((3 < dir || dir <= 5) && prev_line[x] < line[x] && next_line[x] < line[x]) ||
                ((5 < dir || dir <= 7) && prev_line[x + 1] < line[x] && next_line[x - 1] < line[x]))
                continue;

            line[x] = 0x00;
        }
    }

    return hysteresis(&res, tmin, tmax);
}