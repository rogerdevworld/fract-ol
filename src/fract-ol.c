/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:05:01 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/19 17:06:02 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

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

void	show_usage(void)
{
	ft_printf("Uso: ./fractol <fractal> <max_iter>\n");
	ft_printf("Opciones de fractal:\n");
	ft_printf("  M: Mandelbrot\n");
	ft_printf("  J: Julia (requiere c_real y c_imag)\n");
	ft_printf("  B: Burning Ship\n");
	ft_printf("Ejemplo para Julia: ./fractol J -0.7 0.27015 100\n");
	ft_printf("Ejemplo para Mandelbrot: ./fractol M 100\n");
	ft_printf("Ejemplo para Burning Ship: ./fractol B 100\n");
}

int	parse_arguments(int argc, char **argv, t_fractal *f)
{
	if (!validate_arguments(argc, argv))
		return (0);
	return (set_fractal_parameters(argc, argv, f));
}

int	main(int argc, char **argv)
{
	t_fractal	f;

	if (!parse_arguments(argc, argv, &f))
		return (1);
	init_fractal(&f);
	render_fractal(&f);
	mlx_hook(f.win, 2, 1L << 0, handle_keypress, &f);
	mlx_hook(f.win, 4, 1L << 2, mouse_hook, &f);
	mlx_hook(f.win, 17, 1L << 17, close_window, &f);
	mlx_loop(f.mlx);
	return (0);
}
