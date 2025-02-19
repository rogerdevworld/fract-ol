#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	cx;
	double	cy;
	double	zoom;
	int		max_iter;
	int		width;
	int		height;
	double	move_x;
	double	move_y;
	int		color_scheme;
	char	*name;
	double	c_julia_real;
	double	c_julia_imag;
}			t_fractal;

// Funciones principales
void		init_fractal(t_fractal *f);
void		render_fractal(t_fractal *f);
int			close_window(t_fractal *f);
int			key_hook(int keycode, t_fractal *f);
int			mouse_hook(int button, int x, int y, t_fractal *f);

// Funciones de fractales
void		mandelbrot(t_fractal *f);
void		julia(t_fractal *f);
void		burning_ship(t_fractal *f);

// Utils
void		put_pixel(t_fractal *f, int x, int y, int color);
int			get_color(int iter, int max_iter, t_fractal *f);
void		show_usage(void);
int			parse_arguments(int argc, char **argv, t_fractal *f);
void		process_pixel_m(t_fractal *f, int x, int y);
void		process_pixel(t_fractal *f, int x, int y);
int			validate_arguments(int argc, char **argv);

#endif