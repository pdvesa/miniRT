//
// Created by Jules Cayot on 5/18/24.
//

#include <ft_utils.h>

int	ft_putmlx_error(void)
{
	ft_putstr_fd("MiniRT : ", 2);
	ft_putendl_fd((char *) mlx_strerror(mlx_errno), 2);
	return (EXIT_FAILURE);
}
