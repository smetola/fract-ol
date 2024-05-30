/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:25:28 by sanmetol          #+#    #+#             */
/*   Updated: 2024/05/30 16:13:54 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (fractal->julia_fractal != NULL)
	{
		fractal->julia_fractal->julia_x
			= scale(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
		fractal->julia_fractal->julia_y
			= scale(y, 2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
		fractal_render(fractal->julia_fractal);
	}
	else
		fractal_render(fractal);
	return (0);
}

void	julia_handler(t_fractal *fractal)
{
	if (fractal->julia_fractal != NULL)
	{
		mlx_destroy_image(fractal->julia_fractal->mlx_connection,
			fractal->julia_fractal->img.img);
		mlx_destroy_window(fractal->julia_fractal->mlx_connection,
			fractal->julia_fractal->mlx_window);
		free(fractal->julia_fractal->mlx_connection);
		free(fractal->julia_fractal);
		fractal->julia_fractal = NULL;
	}
	else
	{
		fractal->julia_fractal = (t_fractal *)malloc(sizeof(t_fractal));
		if (fractal->julia_fractal == NULL)
			malloc_error();
		fractal->julia_fractal->name = "julia";
		fractal_init(fractal->julia_fractal);
	}
}

int	close_handler(t_fractal *fractal)
{
	if (fractal->julia_fractal)
	{
		mlx_destroy_image(fractal->julia_fractal->mlx_connection,
			fractal->julia_fractal->img.img);
		mlx_destroy_window(fractal->julia_fractal->mlx_connection,
			fractal->julia_fractal->mlx_window);
		free(fractal->julia_fractal->mlx_connection);
		free(fractal->julia_fractal);
		fractal->julia_fractal = NULL;
	}
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	fractal->mlx_connection = NULL;
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x += 0.1;
	else if (keysym == XK_Right)
		fractal->shift_x -= 0.1;
	else if (keysym == XK_Up)
		fractal->shift_y -= 0.1;
	else if (keysym == XK_Down)
		fractal->shift_y += 0.1;
	else if (keysym == XK_plus)
		fractal->iterations += 1;
	else if (keysym == XK_minus && fractal->iterations > 1)
		fractal->iterations -= 1;
	else if (keysym == XK_j)
		julia_handler(fractal);
	else if (keysym == XK_space)
	{
		fractal->zoom = 1;
		fractal->shift_x = 0.0;
		fractal->shift_y = 0.0;
	}
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mouse_re = scale(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
	mouse_im = scale(y, 2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	if (button == Button5)
		zoom_factor = 0.95;
	else if (button == Button4)
		zoom_factor = 1.05;
	else
		return (0);
	fractal->zoom *= zoom_factor;
	fractal->shift_x = mouse_re - scale(x, -2, 2, WIDTH) * fractal->zoom;
	fractal->shift_y = mouse_im - scale(y, 2, -2, HEIGHT) * fractal->zoom;
	fractal_render(fractal);
	return (0);
}
