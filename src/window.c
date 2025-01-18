#include "../include/fract-ol.h"

//inicializacion de ventana 
void init_window(t_fractol *fractol, int width, int height)
{
    fractol->mlx = mlx_init();
    if (!fractol->mlx)
        return ;
    fractol->win = mlx_new_window(fractol->mlx, width, height, "fract-ol");
    if (!fractol->win)
    {
        fprintf(stderr, "Error: No se pudo crear la ventana\n");
        mlx_destroy_display(fractol->mlx);
        free(fractol->mlx);
        exit(EXIT_FAILURE);
    }
}

//cierre de la venta
int close_window(t_fractol *fractol)
{
    if (fractol->win)
        mlx_destroy_window(fractol->mlx, fractol->win);
    if (fractol->mlx)
    {
        mlx_destroy_display(fractol->mlx);
        free(fractol->mlx);
    }
    exit(0);
}