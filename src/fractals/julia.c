#include "../include/fract-ol.c"

//juia
void julia(t_fractal *fractal, double cx, double cy)
{
    int  i;
    double tmp;

    //fractal->name = "julia";
    fractal->cx = cx;
    fractal->cy = cy;
    fractal->zx = fractal->x / fractal->zoom + fractal->offset_x;
    fractal->zy = fractal->y / fractal->zoom + fractal->offset_y;
    i = 0;
    while (++i < fractal->max_iterations)
    {
        tmp = fractal->zx;
        fractal->zx = fractal->zx * fractal->zx - fractal->zy * fractal->zy + fractal->cx;
        fractal->zy = 2 * fractal->zy * tmp + fractal->cy;
        if (fractal->zx * fractal->zx + fractal->zy* fractal->zy >= __DBL_MAX__)
            break ;
    }
    if (i == fractal->max_iterations)
        put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
    else
        put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color * (i% 255)));
}