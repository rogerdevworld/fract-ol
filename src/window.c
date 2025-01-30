#include "../include/fract-ol.h"

void init_fractal(t_fractal *f) {
    f->mlx = mlx_init();
    f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
    f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
    f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel, &f->line_length, &f->endian);
    f->width = WIDTH;
    f->height = HEIGHT;
    f->cx = -0.5; // Centro en el eje real
    f->cy = -0.5; // Centro en el eje imaginario
    f->zoom = 1.0;
    f->move_x = 0.0;
    f->move_y = 0.0;
}


void render_fractal(t_fractal *f) {
    if (f->name[0] == 'M')
        mandelbrot(f);
    else if (f->name[0] == 'J')
        julia(f);
    else if (f->name[0] == 'B')
        burning_ship(f);
    mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

int close_window(t_fractal *f) {
    mlx_destroy_image(f->mlx, f->img);
    mlx_destroy_window(f->mlx, f->win);
    exit(0);
    return (0);
}

int key_hook(int keycode, t_fractal *f) {
    if (keycode == 53) // Tecla ESC
        close_window(f);
    return (0);
}

int mouse_hook(int button, int x, int y, t_fractal *f) {
    if (button == 4) { // Rueda del ratón hacia arriba (zoom in)
        f->zoom *= 1.1;
        f->move_x += (x - f->width / 2.0) * 0.001 / f->zoom;
        f->move_y += (y - f->height / 2.0) * 0.001 / f->zoom;
    } else if (button == 5) { // Rueda del ratón hacia abajo (zoom out)
        f->zoom /= 1.1;
        f->move_x += (x - f->width / 2.0) * 0.001 / f->zoom;
        f->move_y += (y - f->height / 2.0) * 0.001 / f->zoom;
    }
    render_fractal(f);
    return (0);
}

void put_pixel(t_fractal *f, int x, int y, int color) {
    char *dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int get_color(int iter, int max_iter) {
    if (iter == max_iter) {
        return 0x000000; // Color negro para los puntos dentro del fractal
    }

    double t = (double)iter / max_iter;
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return (r << 16 | g << 8 | b);
}