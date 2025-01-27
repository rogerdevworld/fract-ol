#include "../include/fract-ol.h"

void show_usage()
{
    printf("Uso: ./fractol <fractal>\n");
    printf("Opciones de fractal:\n");
    printf("  M: Mandelbrot\n");
    printf("  J: Julia (requiere c_real y c_imag)\n");
    printf("  B: Burning Ship\n");
    printf("  T: Tricorn\n");
    printf("  N: Newton\n");
    printf("  F: Barnsley Fern\n");
    printf("  S: Sierpinski\n");
    printf("  K: Koch\n");
    printf("  L: Lyapunov\n");
    printf("Ejemplo para Julia: ./fractol J -0.7 0.27015\n");
}

int parse_arguments(int argc, char **argv, t_fractal *f) {
    if (argc < 2) {
        show_usage();
        return (0); // Error: no se proporcionó ningún fractal
    }

    // Validar el nombre del fractal
    char *valid_fractals = "MJBTNFSKL"; // Fractales válidos
    if (strchr(valid_fractals, argv[1][0]) == NULL) {
        printf("Error: fractal no válido.\n");
        show_usage();
        return (0); // Error: fractal no válido
    }

    // Asignar el nombre del fractal
    f->name = argv[1];

    // Validar los parámetros adicionales para Julia
    if (f->name[0] == 'J') {
        if (argc != 4) {
            printf("Error: Julia requiere c_real y c_imag.\n");
            show_usage();
            return (0); // Error: argumentos faltantes para Julia
        }
        f->c_julia_real = atof(argv[2]); // Parte real de c
        f->c_julia_imag = atof(argv[3]); // Parte imaginaria de c
    } else if (argc > 2) {
        printf("Error: este fractal no requiere parámetros adicionales.\n");
        show_usage();
        return (0); // Error: parámetros adicionales no necesarios
    }

    return (1); // Éxito: los argumentos son válidos
}