/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:48:30 by sanmetol          #+#    #+#             */
/*   Updated: 2024/05/30 17:27:30 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

static void	fractal_select(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->r = fractal->julia_x;
		c->i = fractal->julia_y;
	}
	else
	{
		c->r = z->r;
		c->i = z->i;
	}
}

static void	handle_pixel(int x, int y, t_complex z, t_fractal *fractal)
{
	t_complex	c;
	int			k;
	int			color;

	k = 0;
	fractal_select(&z, &c, fractal);
	while (k < fractal->iterations)
	{
		z = sum_complex(z, c, fractal->name);
		if ((z.r * z.r + z.i * z.i) > 4)
		{
			color = scale(k, BLACK, WHITE, fractal->iterations);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		k++;
	}
	my_pixel_put(x, y, &fractal->img, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	int			x;
	int			y;
	t_complex	z;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		z.i = scale(y, 2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
		x = -1;
		while (++x < WIDTH)
		{
			z.r = scale(x, -2, 2, WIDTH) * fractal->zoom + fractal->shift_x;
			handle_pixel(x, y, z, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection,
		fractal->mlx_window, fractal->img.img, 0, 0);
}
