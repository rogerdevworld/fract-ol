#include "../../include/fract-ol.h"

void koch(t_fractal *f) {
    // Implementación del copo de nieve de Koch
    // Este fractal es más complejo y requiere recursión o un enfoque iterativo.
    // Aquí te dejo un esqueleto básico.
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            // Lógica para dibujar el copo de nieve de Koch
            put_pixel(f, x, y, 0x00FFFF); // Color cian
        }
    }
}