#include "../../include/fract-ol.h"

static void process_julia_pixel(t_fractal *f, int x, int y) {
    double zx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
    double zy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
    double cx = f->c_julia_real;
    double cy = f->c_julia_imag;
    double tmp;
    int iter = 0;

    while (zx * zx + zy * zy < 4 && iter < f->max_iter) {
        tmp = zx * zx - zy * zy + cx;
        zy = 2.0 * zx * zy + cy;
        zx = tmp;
        iter++;
    }
    put_pixel(f, x, y, get_color(iter, f->max_iter, f));
}

void julia(t_fractal *f) {
    int x, y;
    int progress = 0;
    int new_progress;
    
    y = 0;
    while (y < f->height) {
        x = 0;
        while (x < f->width) {
            process_julia_pixel(f, x, y);
            x++;
        }
        new_progress = (y * 100) / f->height;
        if (new_progress != progress) {
            progress = new_progress;
            ft_printf("Progreso: %d%%\n", progress);
        }
        y++;
    }
}