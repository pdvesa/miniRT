/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:32:17 by svesa             #+#    #+#             */
/*   Updated: 2024/06/06 21:46:24 by svesa            ###   ########.fr       */
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
		temp = skip_white(content[i]);  //need better checking, will give false positives
		if (item == *temp)
			return (content[i]);
	i++;		
	}
	return (NULL);
}

double get_numbers(char *str, int type)
{
	int		temp;
	float	ftemp;
	
	if (!str)
		return (-42069); // i think useless with new mods
	if (type == 0)
	{
		temp = ft_atoi(str); //this might be problem idk
		if ((temp == -1 && ft_strncmp("-1", str, 2)) || (temp == 0 && str[0] != '0'))
			return(-42069); // figure out better number or decide the max limit for size so this can overflow so dont need to make retarded checks
		return (temp); 
	}
	else
	{	
		ftemp = ft_floatoi(str);
		if ((ftemp == 0.0F && str[0] != '0' && !str[1])
			|| (ftemp == 0.0F && ft_strncmp("0.", str, 2) && ft_strlen(str) > 2)
				|| (ftemp == -1 && ft_strncmp("-1", str, 2))) // fix this garbage monster shit
		{
			printf("float %f and str %s\n", ftemp, str);
			return(-42069);
		}
		return (ftemp);
	}
}

//also caller function dont check for -420, check what hules atoi does on overflow etc.
//then again dont really need this function anymore
//floatoi has some rounding problems and we still save perhaps too many digits after .