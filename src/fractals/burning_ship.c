#include "../../include/fract-ol.h"

//burning_ship zₙ₊₁ = abs(zₙ)² + c
void burning_ship(t_fractal *f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            // Convertir las coordenadas de la pantalla a coordenadas del plano complejo
            double zx = 0.0;
            double zy = 0.0;
            double cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            double cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            int iter = 0;

            // Iterar la fórmula del Burning Ship
            while (zx * zx + zy * zy < 4.0 && iter < f->max_iter) {
                double tmp = zx * zx - zy * zy + cx;
                zy = fabs(2.0 * zx * zy) + cy; // Valor absoluto de la parte imaginaria
                zx = fabs(tmp); // Valor absoluto de la parte real
                iter++;
            }

            // Colorear el píxel según el número de iteraciones
            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }
    }
}