#include "../include/fract-ol.h"

void show_usage()
{
    printf("Uso: ./fractol <fractal> <max_iter>\n");
    printf("Opciones de fractal:\n");
    printf("  M: Mandelbrot\n");
    printf("  J: Julia (requiere c_real y c_imag)\n");
    printf("  B: Burning Ship\n");
    printf("Ejemplo para Julia: ./fract-ol J -0.7 0.27015 100\n");
    printf("Ejemplo para Mandelbrot: ./fract-ol M 100\n");
    printf("Ejemplo para Burning Ship: ./fract-ol B 100\n");
}

int parse_arguments(int argc, char **argv, t_fractal *f)
{
    if (argc < 3) {
        show_usage();
        return (0);
    }
    char *valid_fractals = "MJB";
    if (strchr(valid_fractals, argv[1][0]) == NULL)
    {
        printf("Error: fractal no válido.\n");
        show_usage();
        return (0);
    }
    f->name = argv[1];
    if (f->name[0] == 'J') {
        if (argc != 5) {
            printf("Error: Julia requiere c_real, c_imag y max_iter.\n");
            show_usage();
            return (0);
        }
        f->c_julia_real = atof(argv[2]);
        f->c_julia_imag = atof(argv[3]);
        f->max_iter = atoi(argv[4]);
    }
    else if (argc != 3)
    {
        printf("Error: este fractal no requiere parámetros adicionales.\n");
        show_usage();
        return (0);
    } else {
        f->max_iter = atoi(argv[2]);
    }
    return (1);
}