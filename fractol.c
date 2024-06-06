/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:41:25 by sanmetol          #+#    #+#             */
/*   Updated: 2024/06/06 17:57:09 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
		|| (argc == 2 && !ft_strncmp(argv[1], "mandelbrot_2", 12))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)
		&& (is_numeric(argv[2]) || is_numeric(argv[3])))
		)
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
		ft_putstr_fd(ERROR_MS, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
