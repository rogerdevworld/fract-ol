#include "../include/fract-ol.h"

int main(int argc, char **argv) {
    t_fractal f;

    if (!parse_arguments(argc, argv, &f)) {
        return (1);
    }
    init_fractal(&f);
    render_fractal(&f);
    mlx_hook(f.win, 2, 1L << 0, key_hook, &f);
    mlx_hook(f.win, 4, 1L << 2, mouse_hook, &f);
    mlx_hook(f.win, 17, 1L << 17, close_window, &f);
    mlx_loop(f.mlx);
    return (0);
}