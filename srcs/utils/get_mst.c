/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:42:39 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/16 15:42:42 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

u_long	get_mst(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
