/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atois.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:59 by svesa             #+#    #+#             */
/*   Updated: 2024/06/05 20:16:08 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>


static float	make_float(int n, char *s)
{
	double	result;

	result = n;
	while (ft_isdigit(*s))
	{
		result /= 10.f;
		s++;
	}
	return ((double) result);
}

double	ft_floatoi(char *s)
{
	double		n;
	int			d_part;
	int			neg;

	neg = 1;
	n = (double) ft_atoi(s);
	if (n > 16777216 || n < -16777216)
		return (-1.0f);
	if (*s == '+' || (*s == '-' && n == 0.0))
	{
		if ((*s == '-' && n == 0.0))
			neg = -1;
		s++;
	}
	s += ft_intlen((int) n);
	if (*s != '.')
		return (n);
	if (!ft_isdigit(*(s + 1)))
		return (-1.0f);
	d_part = ft_atoi(++s);
	if (d_part < 0)
		return (-1.0f);
	n += (make_float(d_part, s));
	return ((n * (double)neg));
}
