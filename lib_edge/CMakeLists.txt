cmake_minimum_required(VERSION 3.21.1)
project(edge_detection C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)
add_library(lib_edge inc/edge-detection.h inc/kernals.h inc/stb_image.h inc/stb_image_resize.h inc/stb_image_write.h inc/utils.h src/edge-detection.c src/utils.c inc/stb_image.h inc/stb_image_write.h)