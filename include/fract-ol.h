#ifndef FRACT_OL_H
# define FRACT_OL_H

/* MiniLibX */
# include <../minilibx/mlx.h>

/* libft */
# include <../libft/libft.h>

/* lib */
# include <stdlib.h>
# include <stdio.h>
#include <stdio.h>
#include <math.h>

typedef struct s_fractol {
    void    *mlx;             // Instancia de la conexión a MinilibX
    void    *win;             // Ventana creada
    void    *img;             // Imagen que se va a mostrar
    int     zoom_factor;      // Factor de zoom
    double  x_offset;         // Desplazamiento en el eje X
    double  y_offset;         // Desplazamiento en el eje Y
    int     width;            // Ancho de la ventana
    int     height;           // Alto de la ventana
    double  mouse_x;          // Posición X del mouse
    double  mouse_y;          // Posición Y del mouse
    int     is_dragging;      // Estado de arrastre del mouse
    char    *fractal
} t_fractol;

void mandelbrot(t_fractal *fractal);
void julia(t_fractal *fractal, double cx, double cy);
void burning_ship(t_fractal *fractal);

// Prototipos de funciones
void parse_arguments(int argc, char **argv, t_fractol *fractol);
void render_fractal(t_fractol *fractol);
double ft_atof(const char *str);
void zoom(t_fractol *fractol, int direction);
void mouse_move(t_fractol *fractol, int x, int y);
int handle_mouse(int button, int x, int y, t_fractol *fractol);
int handle_mouse_move(int x, int y, t_fractol *fractol);
int handle_key(int keycode, t_fractol *fractol);
int close_window(t_fractol *fractol);

#endif
