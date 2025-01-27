#include "../../include/fract-ol.h"

void tricorn(t_fractal *f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            double zx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            double zy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            double cx = zx;
            double cy = zy;
            int iter = 0;

            while (zx * zx + zy * zy < 4.0 && iter < f->max_iter) {
                double tmp = zx * zx - zy * zy + cx;
                zy = -2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }
    }
}