#include "../../include/fract-ol.h"

void mandelbrot(t_fractal *f) {
    int x, y;
    int progress = 0;
    int new_progress;
    
    y = 0;
    while (y < f->height) {
        x = 0;
        while (x < f->width) {
            process_pixel(f, x, y);
            x++;
        }
        new_progress = (y * 100) / f->height;
        if (new_progress != progress) {
            progress = new_progress;
            printf("Progreso: %d%%\n", progress);
        }
        y++;
    }
}