#include "../../include/fract-ol.h"

void barnsley_fern(t_fractal *f) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 0; i < 100000; i++) {
        double r = (double)rand() / RAND_MAX;
        double xn, yn;
        if (r < 0.01) {
            xn = 0.0;
            yn = 0.16 * y;
        } else if (r < 0.86) {
            xn = 0.85 * x + 0.04 * y;
            yn = -0.04 * x + 0.85 * y + 1.6;
        } else if (r < 0.93) {
            xn = 0.2 * x - 0.26 * y;
            yn = 0.23 * x + 0.22 * y + 1.6;
        } else {
            xn = -0.15 * x + 0.28 * y;
            yn = 0.26 * x + 0.24 * y + 0.44;
        }
        x = xn;
        y = yn;
        int px = (int)(x * f->width / 10.0 + f->width / 2.0);
        int py = (int)(y * f->height / 10.0);
        if (px >= 0 && px < f->width && py >= 0 && py < f->height) {
            put_pixel(f, px, py, 0x00FF00); // Color verde
        }
    }
}