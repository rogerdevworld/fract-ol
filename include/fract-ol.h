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
    void    *mlx_ptr;
    void    *win_ptr;
}   t_fractol;

void    init_window(t_fractol *fractol, int width, int height);
int     close_window(t_fractol *fractol);

#endif
