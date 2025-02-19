/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:05:01 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/19 17:06:02 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fract-ol.h"

int	key_hook(int keycode, t_fractal *f)
{
	if (keycode == 65307)
	{
		close_window(f);
		exit(0);
	}
	else if (keycode == 49)
		f->color_scheme = 1;
	else if (keycode == 50)
		f->color_scheme = 2;
	else if (keycode == 51)
		f->color_scheme = 3;
	else if (keycode == 52)
		f->color_scheme = 4;
	render_fractal(f);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractal *f)
{
	if (button == 4)
	{
		f->zoom *= 1.1;
		f->move_x += (x - f->width / 2.0) * 0.001 / f->zoom;
		f->move_y += (y - f->height / 2.0) * 0.001 / f->zoom;
	}
	else if (button == 5)
	{
		f->zoom /= 1.1;
		f->move_x += (x - f->width / 2.0) * 0.001 / f->zoom;
		f->move_y += (y - f->height / 2.0) * 0.001 / f->zoom;
	}
	render_fractal(f);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	f;

	if (!parse_arguments(argc, argv, &f))
		return (1);
	init_fractal(&f);
	render_fractal(&f);
	mlx_key_hook(f.win, key_hook, &f);
	mlx_hook(f.win, 4, 1L << 2, mouse_hook, &f);
	mlx_hook(f.win, 17, 1L << 17, close_window, &f);
	mlx_loop(f.mlx);
	return (0);
}
