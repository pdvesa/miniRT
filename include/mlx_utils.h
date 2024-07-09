//
// Created by jules on 27/05/2024.
//

#ifndef MLX_UTILS_H
#define MLX_UTILS_H

# include <libft.h>
# include <MLX42/MLX42.h>

int		ft_putmlx_error(void);
void	set_pixel_color(void *address, u_int8_t r, u_int8_t g, u_int8_t b);
double	ft_floatoi(char *s);
int		ft_mod_atoi(const char *str);

#endif //MLX_UTILS_H
