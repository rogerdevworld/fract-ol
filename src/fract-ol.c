#include "fract-ol.h"

void init_window(t_fractol *fractol, int width, int height)
{
    fractol->mlx_ptr = mlx_init();
    if (!fractol->mlx_ptr)
        return ;
    fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, width, height, "fract-ol");
    if (!fractol->win_ptr)
    {
        fprintf(stderr, "Error: No se pudo crear la ventana\n");
        mlx_destroy_display(fractol->mlx_ptr);
        free(fractol->mlx_ptr);
        exit(EXIT_FAILURE);
    }
}

int close_window(t_fractol *fractol)
{
    if (fractol->win_ptr)
        mlx_destroy_window(fractol->mlx_ptr, fractol->win_ptr);
    if (fractol->mlx_ptr)
    {
        mlx_destroy_display(fractol->mlx_ptr);
        free(fractol->mlx_ptr);
    }
    exit(0);
}

int main(void)
{
    t_fractol fractol;

    init_window(&fractol, 800, 600);
    mlx_hook(fractol.win_ptr, 17, 0, (int (*)())close_window, &fractol); // Cerrar con la X de la ventana
    mlx_loop(fractol.mlx_ptr);
    return (0);
}