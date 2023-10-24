//
// Created by zerui on 24/10/2023.
//

#include "edge-detection.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <time.h>

int main() {
    int width, height, channels;
    unsigned char *data = stbi_load("../boat.512.bmp", &width, &height, &channels, 1);
    printf("loaded image\nwidth    : %5d\nheight   : %5d\nchannels : %5d\n", width, height, channels);

//    printf(data);
    clock_t begin, end;
    begin = clock();
    Image img = {width, height, data};
    Image img2 = canny(&img, 1, 50, 120);
    end = clock();
    printf("time taken: %lf\n", (float)(end-begin)/CLOCKS_PER_SEC);
    stbi_write_bmp("../output.bmp", img2.width, img2.height, 1, img2.data);
}