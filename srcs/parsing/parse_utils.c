/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:32:17 by svesa             #+#    #+#             */
/*   Updated: 2024/06/18 19:46:44 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

char	*skip_white(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}

char	*find_content_str(char **content, char *item)
{
	char	*temp;
	int		i;

	i = 0;
	while (content[i])
	{
		temp = skip_white(content[i]);
		if (!(ft_strncmp(item, temp, ft_strlen(item)))
			&& *(temp + ft_strlen(item)) == ' ')
			return (content[i]);
		i++;
	}
	return (NULL);
}

double	get_numbers(char *str, int type)
{
	int		temp;
	float	ftemp;

	if (!str)
		return (-42069);
	if (type == 0)
	{
		temp = ft_mod_atoi(str);
		if (temp == 0 && str[0] != '0')
			return (-42069);
		return (temp);
	}
	else
	{
		ftemp = ft_floatoi(str);
		if ((ftemp == 0.0F && str[0] != '0' && !str[1])
			|| (ftemp == 0.0F && ft_strncmp("0.", str, 2) && ft_strlen(str) > 2)
			|| (ftemp == -1 && ft_strncmp("-1", str, 2)))
			return (-42069);
		return (ftemp);
	}
}

void	extract_error(int object)
{
	const char	category[6][3] = {"A", "C", "L", "sp", "pl", "cy"};

	ft_putendl_fd("Error: \tTerminating program on first error occured!", 2);
	ft_putstr_fd("\tInput file has illegal data in field: ", 2);
	ft_putendl_fd((char *)category[object], 2);
}

void	convert_tabs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
