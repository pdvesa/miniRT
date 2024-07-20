//
// Created by jules on 20/07/2024.
//

#include <miniRT_render.h>

void	init_render_data(t_render_data *data, t_scene *scene,
							t_viewport *vp, void *render)
{
	unsigned int	render_height;
	unsigned int	y_min;
	unsigned int	y_max;
	int				i;

	i = 0;
	render_height = vp->h / THREAD_NUMBER;
	y_min = 0;
	y_max = render_height;
	while (i < THREAD_NUMBER)
	{
		data[i].scene = scene;
		data[i].viewport = vp;
		data[i].render = render;
		data[i].x_min = 0;
		data[i].x_max = vp->w;
		data[i].y_min = y_min;
		data[i].y_max = y_max;
		y_min = y_max;
		if (i < THREAD_NUMBER - 1)
			y_max += render_height;
		else
			y_max = vp->h;
		i++;
	}
}

void	wait_threads(int n, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	multi_thread_render(t_scene* scene, t_viewport* vp, void* render)
{
	pthread_t		threads[THREAD_NUMBER];
	t_render_data	data[THREAD_NUMBER];
	int				i;

	ft_putstr_fd("MiniRT : Rendering on ", 1);
	ft_putnbr_fd(THREAD_NUMBER, 1);
	ft_putendl_fd(" threads", 1);
	init_render_data(data, scene, vp, render);
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
