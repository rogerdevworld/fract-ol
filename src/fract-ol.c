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
