#include "../../include/fract-ol.h"


void lyapunov(t_fractal *f) {
    // Implementación del fractal de Lyapunov
    // Este fractal se basa en exponentes de Lyapunov y requiere cálculos específicos.
    // Aquí te dejo un esqueleto básico.
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            // Lógica para calcular el exponente de Lyapunov
            put_pixel(f, x, y, 0xFF00FF); // Color magenta
        }
    }
}