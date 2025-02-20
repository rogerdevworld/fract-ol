/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:34:31 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/19 19:07:39 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

void	init_fractal(t_fractal *f)
{
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->addr = mlx_get_data_addr(
			f->img, &f->bits_per_pixel,
			&f->line_length, &f->endian);
	f->width = WIDTH;
	f->height = HEIGHT;
	f->cx = -0.5;
	f->cy = -0.5;
	f->zoom = 1.0;
	f->move_x = 0.0;
	f->move_y = 0.0;
}

void	render_fractal(t_fractal *f)
{
	if (f->name[0] == 'M')
		mandelbrot(f);
	else if (f->name[0] == 'J')
		julia(f);
	else if (f->name[0] == 'B')
		burning_ship(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

int	close_window(t_fractal *f)
{
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
	return (0);
}

void	put_pixel(t_fractal *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(int iter, int max_iter, t_fractal *f)
{
	int	gray;

	if (iter == max_iter)
		return (0x000000);
	if (f->color_scheme == 1)
		return ((iter * 10 % 256) << 16
			| (iter * 7 % 256) << 8 | (iter * 5 % 256));
	else if (f->color_scheme == 2)
		return ((iter * 5 % 256) << 16
			| (iter * 7 % 256) << 8 | (iter * 10 % 256));
	else if (f->color_scheme == 3)
	{
		gray = iter * 255 / max_iter;
		return ((gray << 16) | (gray << 8) | gray);
	}
	else if (f->color_scheme == 4)
		return ((iter * 123 % 256) << 16
			| (iter * 321 % 256) << 8 | (iter * 213 % 256));
	return (0xFFFFFF);
}
