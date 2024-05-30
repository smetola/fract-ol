/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:10:18 by sanmetol          #+#    #+#             */
/*   Updated: 2024/05/29 15:36:42 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL || n <= 0)
		return (0);
	while ((*s1 || *s2) && n > 0)
	{
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

double	atodbl(char *str)
{
	long	int_part;
	double	fraction_part;
	double	pow;
	int		neg;

	int_part = 0;
	fraction_part = 0;
	neg = 1;
	pow = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			neg = -1;
	while (*str != '.' && *str)
		int_part = int_part * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str)
	{
		pow /= 10;
		fraction_part += (*str++ - '0') * pow;
	}
	return ((int_part + fraction_part) * neg);
}
