/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:07:54 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/19 19:08:18 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/fract-ol.h"

void	process_pixel_m(t_fractal *f, int x, int y)
{
	double	zx;
	double	zy;
	int		iter;
	double	tmp;

	zx = 0.0;
	zy = 0.0;
	iter = 0;
	tmp = 0;
	while (zx * zx + zy * zy < 4 && iter < f->max_iter)
	{
		tmp = zx * zx - zy * zy + (x - f->width / 2.0) * 4.0 / (f->width
				* f->zoom) + f->move_x;
		zy = 2.0 * zx * zy + (y - f->height / 2.0) * 4.0 / (f->height * f->zoom)
			+ f->move_y;
		zx = tmp;
		iter++;
	}
	put_pixel(f, x, y, get_color(iter, f->max_iter, f));
}

void	mandelbrot(t_fractal *f)
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
			process_pixel_m(f, x, y);
			x++;
		}
		new_progress = (y * 100) / f->height;
		if (new_progress != progress)
		{
			progress = new_progress;
			ft_printf("Progreso: %d%%\n", progress);
		}
		y++;
	}
}
