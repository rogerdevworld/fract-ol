/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:07:41 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/19 20:24:16 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fractol.h"

static void	process_julia_pixel(t_fractal *f, int x, int y)
{
	double	zx;
	double	zy;
	int		iter;
	double	tmp;

	zx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
	zy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
	iter = 0;
	while (zx * zx + zy * zy < 4 && iter < f->max_iter)
	{
		tmp = zx * zx - zy * zy + f->c_julia_real;
		zy = 2.0 * zx * zy + f->c_julia_imag;
		zx = tmp;
		iter++;
	}
	put_pixel(f, x, y, get_color(iter, f->max_iter, f));
}

void	julia(t_fractal *f)
{
	int	progress;
	int	new_progress;
	int	x;
	int	y;

	progress = 0;
	y = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			process_julia_pixel(f, x, y);
			x++;
		}
		new_progress = (y * 100) / f->height;
		if (new_progress != progress)
		{
			progress = new_progress;
			print_progress(progress);
			//ft_printf("Progreso: %d%%\n", progress);
		}
		y++;
	}
}
