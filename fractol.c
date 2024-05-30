/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:41:25 by sanmetol          #+#    #+#             */
/*   Updated: 2024/05/30 16:14:28 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
		|| (argc == 2 && !ft_strncmp(argv[1], "mandelbrot_2", 12)))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
		close_handler(&fractal);
	}
	else
	{
		ft_putstr_fd("Please enter: \n\t\"./fractol mandelbrot\" or "\
		"\n\t\"./fractol julia <value_1> <value_2>\"", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

//gcc *c minilibx-linux/libmlx.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz