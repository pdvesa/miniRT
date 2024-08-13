/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:58:02 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:58:04 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_utils.h>

t_rgb	get_pixel_color(void *address)
{
	t_rgb	color;

	color.r = (int) *((uint8_t *) address);
	color.g = (int) *((uint8_t *) address + sizeof (uint8_t));
	color.b = (int) *((uint8_t *) address + (2 * sizeof (uint8_t)));
	return (color);
}
