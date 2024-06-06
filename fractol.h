/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:43:14 by sanmetol          #+#    #+#             */
/*   Updated: 2024/06/06 17:25:01 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

# define ERROR_MS "Please enter: \n\t\"./fractol mandelbrot\" or "\
		"\n\t\"./fractol julia <value_1> <value_2>\" or "\
		"\n\t\"./fractol mandelbrot_2\""
# define WIDTH 800
# define HEIGHT 800
# define BLACK 0x000000
# define WHITE 0xFFFFFF

typedef struct s_complex
{
	double		r;
	double		i;
}				t_complex;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_fractal
{
	char				*name;
	void				*mlx_connection;
	void				*mlx_window;
	t_image				img;
	int					iterations;
	double				shift_x;
	double				shift_y;
	double				zoom;
	double				julia_x;
	double				julia_y;
	struct s_fractal	*julia_fractal;
}				t_fractal;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			is_numeric(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		malloc_error(void);
double		atodbl(char *str);
void		fractal_init(t_fractal *fractal);
double		scale(double unscaled_num, double new_min,
				double new_max, double old_max);
void		fractal_render(t_fractal *fractal);
t_complex	sum_complex(t_complex z, t_complex c, char *name);
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
void		julia_handler(t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);

#endif