/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:42:58 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/20 18:30:00 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER_MIN 1
#define MAX_ITER_MAX 10000
#define JULIA_REAL_MIN -2.0
#define JULIA_REAL_MAX 2.0
#define JULIA_IMAG_MIN -2.0
#define JULIA_IMAG_MAX 2.0

void show_usage(void)
{
    ft_printf("Uso: ./fractol <fractal> <max_iter>\n");
    ft_printf("Opciones de fractal:\n");
    ft_printf("  M: Mandelbrot\n");
    ft_printf("  J: Julia (requiere c_real y c_imag)\n");
    ft_printf("  B: Burning Ship\n");
    ft_printf("Ejemplo para Julia: ./fract-ol J -0.7 0.27015 100\n");
    ft_printf("Ejemplo para Mandelbrot: ./fract-ol M 100\n");
    ft_printf("Ejemplo para Burning Ship: ./fract-ol B 100\n");
}

int is_valid_number(const char *str)
{
    char *endptr;
    strtod(str, &endptr);
    return (*endptr == '\0');
}

int is_valid_integer(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str) && *str != '-')
            return (0);
        str++;
    }
    return (1);
}

int validate_arguments(int argc, char **argv)
{
    char *valid_fractals = "MJB";
    
    if (argc < 3)
    {
        show_usage();
        return (0);
    }
    if (!argv[1] || ft_strlen(argv[1]) != 1 || ft_strchr(valid_fractals, argv[1][0]) == NULL)
    {
        ft_printf("Error: fractal no válido.\n");
        show_usage();
        return (0);
    }
    return (1);
}

int validate_julia_params(char **argv, t_fractal *f)
{
    if (!is_valid_number(argv[2]) || !is_valid_number(argv[3]) || !is_valid_integer(argv[4]))
    {
        ft_printf("Error: Julia requiere c_real, c_imag y max_iter como números válidos.\n");
        show_usage();
        return (0);
    }
    f->c_julia_real = ft_atof(argv[2]);
    f->c_julia_imag = ft_atof(argv[3]);
    f->max_iter = ft_atoi(argv[4]);

    if (f->c_julia_real < JULIA_REAL_MIN || f->c_julia_real > JULIA_REAL_MAX ||
        f->c_julia_imag < JULIA_IMAG_MIN || f->c_julia_imag > JULIA_IMAG_MAX)
    {
        ft_printf("Error: Valores de Julia fuera de rango (%.1f a %.1f).\n", JULIA_REAL_MIN, JULIA_REAL_MAX);
        return (0);
    }
    return (1);
}

int set_fractal_parameters(int argc, char **argv, t_fractal *f)
{
    f->name = argv[1];
    if (f->name[0] == 'J')
    {
        if (argc != 5 || !validate_julia_params(argv, f))
            return (0);
    }
    else
    {
        if (argc != 3 || !is_valid_integer(argv[2]))
        {
            ft_printf("Error: este fractal no requiere parámetros adicionales o el max_iter no es válido.\n");
            show_usage();
            return (0);
        }
        f->max_iter = ft_atoi(argv[2]);
    }
    
    if (f->max_iter < MAX_ITER_MIN || f->max_iter > MAX_ITER_MAX)
    {
        ft_printf("Error: max_iter debe estar entre %d y %d.\n", MAX_ITER_MIN, MAX_ITER_MAX);
        return (0);
    }
    return (1);
}

int parse_arguments(int argc, char **argv, t_fractal *f)
{
    if (!validate_arguments(argc, argv))
        return (0);
    return set_fractal_parameters(argc, argv, f);
}