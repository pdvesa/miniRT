/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:58:35 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:58:36 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_utils.h>

void	set_pixel_color(void *address, t_rgb *color)
{
	ft_memset(address, color->r, sizeof (u_int8_t));
	ft_memset(address + sizeof (u_int8_t), color->g, sizeof (u_int8_t));
	ft_memset(address + 2 * sizeof (u_int8_t), color->b, sizeof (u_int8_t));
	ft_memset(address + 3 * sizeof (u_int8_t), 255, sizeof (u_int8_t));
}
