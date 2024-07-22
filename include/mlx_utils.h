/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:28:01 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/11 18:28:03 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <libft.h>
# include <MLX42/MLX42.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

void	*ft_putmlx_error(void);
t_rgb	get_pixel_color(void *address);
void	set_pixel_color(void *address, u_int8_t r, u_int8_t g, u_int8_t b);
double	ft_floatoi(char *s);
int		ft_mod_atoi(const char *str);

#endif //MLX_UTILS_H
