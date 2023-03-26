#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "my_timer.h"
#include "stb_image_write.h"

// Default size of image
// #define X 1920
// #define Y 1080
#define X 1280
#define Y 720
#define MAX_ITER 100

void calc_mandelbrot(uint8_t image[Y][X]) {
    for(int i = 0; i < X; i++) {
        for(int j = 0; j < Y; j++) {
            float x = 0;
            float y = 0;
            float cx = ((i / (float)X) * 3.5) - 2.5;
            float cy = ((j / (float)Y) * 2) - 1;
            int iteration = 0;
            while(x * x + y * y <= 4 && iteration < MAX_ITER) {
                float x_temp = x * x - y * y + cx;
                y = 2 * x * y + cy;
                x = x_temp;
                iteration++;
            }
            uint8_t norm_iteration = (iteration / (float)MAX_ITER) * 255;
            image[j][i] = norm_iteration;
        }
    }
}

int main() {
    uint8_t image[Y][X];
    double timer = start_to_record();
    calc_mandelbrot(image);
    stop_record(timer);

    const int channel_nr = 1, stride_bytes = 0;
    stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
    return EXIT_SUCCESS;
}
