/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:24:56 by rmarrero          #+#    #+#             */
/*   Updated: 2025/02/22 20:24:59 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

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

int	adjust_iterations(int keycode, t_fractal *f)
{
	if (keycode == 65451 || keycode == 61)
	{
		f->max_iter += 10;
		if (f->max_iter > MAX_ITER_MAX)
			f->max_iter = MAX_ITER_MAX;
	}
	else if (keycode == 65453 || keycode == 45)
	{
		f->max_iter -= 10;
		if (f->max_iter < MAX_ITER_MIN)
			f->max_iter = MAX_ITER_MIN;
	}
	render_fractal(f);
	return (0);
}

int	move_fractal(int keycode, t_fractal *f)
{
	if (keycode == 65362)
		f->move_y -= 0.1 / f->zoom;
	else if (keycode == 65364)
		f->move_y += 0.1 / f->zoom;
	else if (keycode == 65361)
		f->move_x -= 0.1 / f->zoom;
	else if (keycode == 65363)
		f->move_x += 0.1 / f->zoom;
	render_fractal(f);
	return (0);
}

// Función que imprime el keycode y la acción asignada según la tecla
void	print_key_action(int keycode)
{
	ft_printf("Tecla presionada: %d ", keycode);
	if (keycode == 65307)
		ft_printf("🛑\n");
	else if (keycode == 49)
		ft_printf("🎨\n");
	else if (keycode == 50)
		ft_printf("🎨\n");
	else if (keycode == 51)
		ft_printf("🎨\n");
	else if (keycode == 52)
		ft_printf("🎨\n");
	else if (keycode == 65451)
		ft_printf("➕\n");
	else if (keycode == 65453)
		ft_printf("➖\n");
	else if (keycode == 65362)
		ft_printf("⬆️\n");
	else if (keycode == 65364)
		ft_printf("⬇️\n");
	else if (keycode == 65361)
		ft_printf("⬅️\n");
	else if (keycode == 65363)
		ft_printf("➡️\n");
	else
		ft_printf("❓\n");
}

// Función para imprimir el progreso
void	print_progress(int progress)
{
	const char	*spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
	static int	spinner_index = 0;

	ft_printf("\r%s Processing [%d%%]", spinner[spinner_index], progress);
	spinner_index = (spinner_index + 1) % 10;
	fflush(stdout);
}
