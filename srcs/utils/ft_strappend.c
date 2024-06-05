/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:08 by svesa             #+#    #+#             */
/*   Updated: 2024/06/03 16:52:11 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

char	*ft_strappend(char *s1, char *s2, int size)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	ft_memset(s2, 0, size);
	if (s1)
		free(s1);
	return (result);
}
