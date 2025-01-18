#ifndef FRACT_OL_H
# define FRACT_OL_H

/* MiniLibX */
# include <../minilibx/mlx.h>

/* libft */
# include <../libft/libft.h>

/* lib */
# include <stdlib.h>
# include <stdio.h>

typedef struct s_fractol {
    void    *mlx;         // Instancia de la conexión a MinilibX
    void    *win;         // Ventana creada
    void    *img;         // Imagen que se va a mostrar
    int     zoom_factor;  // Factor de zoom
    int     x_offset;     // Desplazamiento en el eje X
    int     y_offset;     // Desplazamiento en el eje Y
    int     width;        // Ancho de la ventana
    int     height;       // Alto de la ventana
} t_fractol;

void    init_window(t_fractol *fractol, int width, int height);
int     close_window(t_fractol *fractol);

#endif
