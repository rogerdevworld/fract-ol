#include "../include/fract-ol.h"

// Función para procesar argumentos
void parse_arguments(int argc, char **argv, t_fractol *fractol)
{
    if (argc < 2)
    {
        fprintf(stderr, "Uso: ./fractol <fractal_name> [params]\n");
        exit(1);
    }

    // Convertir el primer argumento a mayúsculas
    ft_upper(argv[1]);
    
    // Manejar el tipo de fractal
    if (strcmp(argv[1], "MANDELBROT") == 0)
    {
        fractol->fractal = MANDELBROT;
    }
    else if (strcmp(argv[1], "JULIA") == 0)
    {
        fractol->fractal = JULIA;
        if (argc == 4) // Si se proporcionan parámetros para Julia
        {
            fractol->julia_cx = ft_atof(argv[2]); // Asegúrate de tener ft_atof
            fractol->julia_cy = ft_atof(argv[3]);
        }
        else
        {
            fprintf(stderr, "Uso: ./fractol JULIA <cx> <cy>\n");
            exit(1);
        }
    }
    else if (strcmp(argv[1], "BURNING_SHIP") == 0)
    {
        fractol->fractal = BURNING_SHIP;
    }
    else
    {
        fprintf(stderr, "Fractal no reconocido. Usa MANDELBROT, JULIA o BURNING_SHIP.\n");
        exit(1);
    }
}

#include <stdio.h>

double ft_atof(const char *str)
{
    double result = 0.0;
    double decimal_place = 1.0;
    int sign = 1;

    // Ignorar espacios en blanco
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;

    // Manejar el signo
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }

    // Convertir la parte entera
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    // Manejar la parte decimal
    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            decimal_place *= 0.1;
            result += (*str - '0') * decimal_place;
            str++;
        }
    }

    return result * sign;
}