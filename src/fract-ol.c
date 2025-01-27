#include "../include/fract-ol.h"

int main(int argc, char **argv) {
    t_fractal f;

    // Parsear los argumentos
    if (!parse_arguments(argc, argv, &f)) {
        return (1); // Salir si los argumentos no son válidos
    }

    // Inicializar el fractal
    init_fractal(&f);

    // Renderizar el fractal
    render_fractal(&f);

    // Configurar los hooks de eventos
    mlx_hook(f.win, 2, 1L << 0, key_hook, &f);
    mlx_hook(f.win, 4, 1L << 2, mouse_hook, &f);
    mlx_hook(f.win, 17, 1L << 17, close_window, &f);

    // Iniciar el bucle de la ventana
    mlx_loop(f.mlx);
    return (0);
}