#include "../../include/fract-ol.h"

void sierpinski(t_fractal *f) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 0; i < 100000; i++) {
        double r = (double)rand() / RAND_MAX;
        double xn, yn;

        if (r < 0.33) {
            xn = x / 2.0;
            yn = y / 2.0;
        } else if (r < 0.66) {
            xn = x / 2.0 + 0.25;
            yn = y / 2.0 + 0.5;
        } else {
            xn = x / 2.0 + 0.5;
            yn = y / 2.0;
        }

        x = xn;
        y = yn;

        int px = (int)(x * f->width);
        int py = (int)(y * f->height);

        if (px >= 0 && px < f->width && py >= 0 && py < f->height) {
            put_pixel(f, px, py, 0xFFFFFF); // Color blanco
        }
    }
}