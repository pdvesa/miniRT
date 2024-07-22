/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:58:22 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:58:24 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_utils.h>

void	*ft_putmlx_error(void)
{
	ft_putstr_fd("MiniRT : ", 2);
	ft_putendl_fd((char *) mlx_strerror(mlx_errno), 2);
	return (NULL);
}
