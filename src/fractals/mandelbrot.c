#include "../../include/fract-ol.h"

void mandelbrot(t_fractal *f) {
    double zx, zy, cx, cy, tmp;
    int iter;
    int progress = 0;

    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            zx = 0.0;
            zy = 0.0;
            cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            iter = 0;

            while (zx * zx + zy * zy < 4 && iter < f->max_iter) {
                tmp = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }

        // Mostrar progreso
        int new_progress = (y * 100) / f->height;
        if (new_progress != progress) {
            progress = new_progress;
            printf("Progreso: %d%%\n", progress);
        }
    }
}