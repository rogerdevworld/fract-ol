#include "../../include/fract-ol.h"

void process_pixel(t_fractal *f, int x, int y)
{
    double zx = 0.0;
    double zy = 0.0;
    double cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
    double cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
    double tmp;
    int iter = 0;

    while (zx * zx + zy * zy < 4 && iter < f->max_iter) {
        tmp = zx * zx - zy * zy + cx;
        zy = fabs(2.0 * zx * zy) + cy;
        zx = fabs(tmp);
        iter++;
    }

    put_pixel(f, x, y, get_color(iter, f->max_iter));
}

void burning_ship(t_fractal *f) {
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
