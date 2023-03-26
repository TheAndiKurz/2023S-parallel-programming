#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "my_timer.h"
#include "stb_image_write.h"

// Default size of image
#define X 1920
#define Y 1080
// #define X 1280
// #define Y 720
#define MAX_ITER 80

#define CX_SCALE 4.9
#define CX_OFFS 2.8
#define CY_SCALE 2.8
#define CY_OFFS 1.4

void calc_mandelbrot(uint8_t image[Y][X]) {
    for(int i = 0; i < X; i++) {
        for(int j = 0; j < Y; j++) {
            // code adapted from
            // https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
            float x = 0, y = 0;
            float x2 = 0, y2 = 0;
            float cx = ((i / (float)X) * CX_SCALE) - CX_OFFS;
            float cy = ((j / (float)Y) * CY_SCALE) - CY_OFFS;
            int iteration = 0;
            while(x2 + y2 <= 4 && iteration < MAX_ITER) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
                x2 = x * x;
                y2 = y * y;
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
