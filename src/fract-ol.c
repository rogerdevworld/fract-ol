#include "../include/fract-ol.h"

int main(void)
{
    t_fractol fractol;

    init_window(&fractol, 640, 480);
    mlx_hook(fractol.win, 17, 0, (int (*)())close_window, &fractol); // Cerrar con la X de la ventana
    mlx_loop(fractol.mlx);
    return (0);
}

/* funcion de las ventanas */
/* funcion para el tipo de fractal */
/* funciones para menejar los fractales 1 a 1 */