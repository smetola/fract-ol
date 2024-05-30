/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:56:58 by sanmetol          #+#    #+#             */
/*   Updated: 2024/05/29 18:45:39 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	scale(double unscaled_num, double new_min,
	double new_max, double old_max)
{
	return ((new_max - new_min) * unscaled_num / old_max + new_min);
}

t_complex	sum_complex(t_complex z, t_complex c, char *name)
{
	t_complex	result;

	if (!ft_strncmp(name, "mandelbrot_2", 12))
	{
		result.r = (z.r * z.r * z.r * z.r) - (6 * z.r * z.r * z.i * z.i)
			+ (z.i * z.i * z.i * z.i) + c.r;
		result.i = (4 * z.r * z.r * z.r * z.i)
			- (4 * z.r * z.i * z.i * z.i) + c.i;
	}
	else
	{
		result.r = pow(z.r, 2) - z.i * z.i + c.r;
		result.i = 2 * z.r * z.i + c.i;
	}
	return (result);
}
