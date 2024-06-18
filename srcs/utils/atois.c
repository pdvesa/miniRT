/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atois.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:59 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 15:50:05 by svesa            ###   ########.fr       */
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

int	ft_mod_atoi(const char *str)
{
	int		i;
	int		sign;
	long	ret;

	sign = 1;
	i = 0;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
		if ((ret > 2147483647 && sign == 1) || (ret > 2147483648 && sign == -1))
			return (0);
	}
	if (str[i])
		return (0);
	return (ret * sign);
}
