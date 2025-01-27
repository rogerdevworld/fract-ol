#include "../../include/fract-ol.h"

void newton(t_fractal *f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            double zx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            double zy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            int iter = 0;

            while (iter < f->max_iter) {
                double zx2 = zx * zx;
                double zy2 = zy * zy;
                double zx2zy2 = zx2 + zy2;
                if (zx2zy2 < 1e-6) break;

                double tmp = (zx * (zx2 - 3 * zy2) + 1) / (3 * (zx2 + zy2));
                zy = (zy * (3 * zx2 - zy2)) / (3 * (zx2 + zy2));
                zx = tmp;
                iter++;
            }

            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }
    }
}