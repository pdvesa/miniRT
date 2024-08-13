/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:57:22 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:57:25 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

/**
 * @brief Multiplies each component of an RGB color by a factor.
 *
 * This function multiplies the red (r), green (g), and blue (b) components
 * of the given RGB color by the specified factor. The result is returned
 * as a new RGB color.
 *
 * ACHTUNG factor must be included within 0.f and 1.f !!
 *
 * @param rgb The RGB color to multiply.
 * @param factor The factor by which to multiply the RGB components.
 * @return The resulting RGB color after multiplication.
 */

t_rgb	multiply_rgb(t_rgb rgb, float factor)
{
	rgb.r = (int)((float)rgb.r * factor);
	rgb.g = (int)((float)rgb.g * factor);
	rgb.b = (int)((float)rgb.b * factor);
	return (rgb);
}
