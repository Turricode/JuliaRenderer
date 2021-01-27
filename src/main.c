#include "libbmp.h"

#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

#define CA 0.355f
#define CB 0.355f

#define MAX_ITERATIONS 1000

//Y = (X-A)/(B-A) * (D-C) + C
float map(float x, float A, float B, float C, float D){
    float final = (x - A) / (B - A) * (D - C) + C;
    return final;
}

float *mandlebrot(){

    float *final = malloc(sizeof(float) * WIDTH * HEIGHT);

    float brightness;

    float w = 5;
    float h = (w * HEIGHT) / WIDTH;

    float xmin = -w/2;
    float ymin = -h/2;

    float xmax = xmin + w;
    float ymax = ymin + h;

    float dx = (xmax - xmin) / (WIDTH);
    float dy = (ymax - ymin) / (HEIGHT);

    float y = ymin;

    for (int j = 0; j < HEIGHT; j++) {
    float x = xmin;
        for (int i = 0; i < WIDTH; i++) {

            float a = x;
            float b = y;
            int n = 0;
            while (n < MAX_ITERATIONS) {
                float aa = a * a;
                float bb = b * b;

                if (aa + bb > 4.0) {
                    break;  // Bail
                }

                float twoab = 2.0 * a * b;
                a = aa - bb + CA;
                b = twoab + CB;
                n++;
            }

            if(n == MAX_ITERATIONS){
                brightness = 0;
            }else
            {
                brightness = 255 * sqrtf((float)n / MAX_ITERATIONS);
            }

            final[j * HEIGHT + i] = brightness;

            x += dx;
        }
        y += dy;
    }
            

    return final;
}

int main(int argc, char const *argv[])
{
    bmp_img img;
    bmp_img_init_df(&img, WIDTH, HEIGHT);

    float * m = mandlebrot();

    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            bmp_pixel_init(&img.img_pixels[y][x], m[y * HEIGHT + x],  m[y * HEIGHT + x],  m[y * HEIGHT + x]);
        }
    }

    bmp_img_write(&img, "test.bmp");
    bmp_img_free(&img);

    return 0;
}
