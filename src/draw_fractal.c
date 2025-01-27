#include "../include/fract-ol.h"

//dibujar los fractales 
void render_fractal(t_fractol *fractol)
{
    int x, y;

    // Limpiar la imagen
    mlx_clear_window(fractol->mlx, fractol->win);
    // O si estás usando una imagen:
    // mlx_destroy_image(fractol->mlx, fractol->img);
    // fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);

    // Recorrer cada píxel de la ventana
    for (y = 0; y < fractol->height; y++)
    {
        for (x = 0; x < fractol->width; x++)
        {
            // Establecer las coordenadas del fractal
            fractol->x = x;
            fractol->y = y;

            // Llamar a la función de fractal correspondiente
            if (fractol->current_fractal == BURNING_SHIP)
            {
                burning_ship(fractol);
            }
            else if (fractol->current_fractal == JULIA)
            {
                julia(fractol, fractol->julia_cx, fractol->julia_cy);
            }
            else if (fractol->current_fractal == MANDELBROT)
            {
                mandelbrot(fractol);
            }
        }
    }

    // Actualizar la ventana con la nueva imagen
    mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

void put_color_to_pixel(t_fractol *fractal, int x, int y, int color)
{
    char *img_data;
    int bpp; // bits por pixel
    int size_line; // tamaño de línea
    int endian; // endian

    img_data = mlx_get_data_addr(fractal->img, &bpp, &size_line, &endian);
    int pixel_index = (y * size_line) + (x * (bpp / 8));
    *(int *)(img_data + pixel_index) = color; // Asignar el color al píxel
}