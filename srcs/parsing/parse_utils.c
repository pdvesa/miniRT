/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:32:17 by svesa             #+#    #+#             */
/*   Updated: 2024/06/05 20:41:25 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

char	*skip_white(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}

char	*find_content_str(char **content, char item)
{
	char	*temp;
	int		i;

	i = 0;
	while (content[i])
	{
		temp = skip_white(content[i]);
		if (item == *temp)
			return (content[i]);
	i++;		
	}
	return (NULL);
}

char	**find_content_array(char **content, char item, int size)
{
	char	**array;
	int 	i;

	array = malloc(sizeof(char *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < size)
	{
	}
	return (array); 
}

double get_numbers(char *str, int type)
{
	if (!str)
		return (-420);
	if (type == 0)
	{
		return (ft_atoi(str)); //this might be problem idk
	}
	else if (type == 1)
	{	
		return (ft_floatoi(str));
	}
	else
		return (-420);
}

//also caller function dont check for -420, check what hules atoi does on overflow etc.
//then again dont really need this function anymore