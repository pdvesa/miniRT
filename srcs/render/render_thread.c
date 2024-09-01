/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:55:43 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/20 14:55:46 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

int	multi_thread_render(t_vp *vp, void *render, t_aa_data *aa_data)
{
	pthread_t		threads[THREAD_NUMBER];
	t_render_data	data[THREAD_NUMBER];
	int				i;

	ft_putstr_fd("MiniRT : Rendering on ", 1);
	ft_putnbr_fd(THREAD_NUMBER, 1);
	ft_putendl_fd(" threads", 1);
	multi_render_data(data, vp, render, aa_data);
	i = 0;
	while (i < THREAD_NUMBER)
	{
		if (pthread_create(&threads[i], NULL, &render_thread, &data[i]) != 0)
		{
			ft_putendl_fd("MiniRT : Error creating threads", 2);
			wait_threads(i, threads);
			return (0);
		}
		i++;
	}
	wait_threads(i, threads);
	return (1);
}

void	*render_thread(void *data_ptr)
{
	t_render_data	*data;
	t_pxl_cdts		p;
	void			*pxl_addr;

	data = (t_render_data *) data_ptr;
	p.y = data->y_min;
	while (p.y < data->y_max)
	{
		p.x = data->x_min;
		while (p.x < data->x_max)
		{
			pxl_addr = data->render + (((p.y * data->vp->w) + p.x)
					* sizeof (uint32_t));
			data->render_f(data->vp, &p, data->aa_data, pxl_addr);
			p.x++;
		}
		p.y++;
	}
	return (NULL);
}
