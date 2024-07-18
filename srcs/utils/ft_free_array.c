/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:57:43 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:57:44 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

void	*ft_free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}
