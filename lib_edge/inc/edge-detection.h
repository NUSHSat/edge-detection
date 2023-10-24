//
// Created by zerui on 24/10/2023.
//

#ifndef EDGE_DETECTION_EDGE_DETECTION_H
#define EDGE_DETECTION_EDGE_DETECTION_H
#include "utils.h"
Image sobel(Image* input);
Image scharr(Image* input);
Image prewitt(Image* input);
Image canny(Image* input, float sigma, float tmin, float tmax);
#endif //EDGE_DETECTION_EDGE_DETECTION_H
