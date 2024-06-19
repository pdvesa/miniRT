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
		return (-42069); //might be useless after changes 
	if (type == 0)
	{
		temp = ft_mod_atoi(str); //this might be problem idk
		if (temp == 0 && str[0] != '0')
			return (-42069); // figure out better number or decide the max limit for size so this can overflow so dont need to make retarded checks
		return (temp);
	}
	else
	{
		ftemp = ft_floatoi(str);
		if ((ftemp == 0.0F && str[0] != '0' && !str[1])
			|| (ftemp == 0.0F && ft_strncmp("0.", str, 2) && ft_strlen(str) > 2)
			|| (ftemp == -1 && ft_strncmp("-1", str, 2))) // fix this garbage monster shit
			return (-42069);
		return (ftemp);
	}
}

void	extract_error(int object)
{
	const char	category[6][3] = {"A", "C", "L", "sp", "pl", "cy"};
	// const char	error_name[3][12] = {"colors", "vectors", "coordinates"};

	ft_putendl_fd("Error: \tTerminating program on first error occured!", 2);
	ft_putstr_fd("\tInput file has illegal data in field: ", 2);
	ft_putendl_fd((char *)category[object], 2);
}
//floatoi has some rounding problems and we still save perhaps too many digits after .

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