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
 * @brief Multiplies the RGB values of a given color with a given factor.
 *
 * This function takes a t_rgb struct representing a color and a float value
 * representing the factor, and multiplies each RGB value of the color with
 * the factor. The result is returned as a new t_rgb struct.
 *
 * @param rgb The color to be multiplied.
 * @param factor The factor to multiply the RGB values with.
 * @return The resulting color after multiplication.
 */

t_rgb	scalar_rgb(t_rgb rgb, float factor)
{
	rgb.r = (int)((float)rgb.r * factor);
	rgb.g = (int)((float)rgb.g * factor);
	rgb.b = (int)((float)rgb.b * factor);
	return (rgb);
}
