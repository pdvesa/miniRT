#include <get_next_line.h>
#include <miniRT_render.h>
#include <miniRT_parsing.h>
#include <miniRT.h>

void	print_instructions(void)
{
	printf("In order to select object to transform click it on the screen\n"); //change
	printf("Possible transformable parameters :\n\tdia (num) for diameter\n\thgt (num) for height\n\torient (num,num,num) for change of direction\n\tcord (num,num,num) for relocation\n");
	printf("Examples: 'dia 35' will change selected sphere diameter to 35, 'orient 1,1,1' will change selected object or element directional vector!\n");
	printf("Only one modification per press of button!@!\n");
	printf("If situation occurs where you lost your memories and you need to reprint these instructions press A (for acute amnesia)\n");
}

void	ft_re_render(t_hook_container *data)
{
	ray_trace(data->image, data->scene);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) // dont know if we can just re_render without deleting or do we need to make new image for not leaking
	{
		mlx_delete_image(data->mlx, data->image);
		ft_putmlx_error();
	}
}

char	**sanitize_input(void)
{
	char	*input;
	char	**cont_arr;
	int		i;

	printf("Input please\n");
	input = get_next_line(1);
	cont_arr = ft_split(input, ' ');
	free(input);
	if (!cont_arr)
		return (NULL);
	if (ft_strarray_len(cont_arr) != 2)
		return (ft_strarray_free(cont_arr), NULL);
	i = 0;
	while(cont_arr[1][i])
	{
		if (cont_arr[1][i] == '\n' || cont_arr[1][i] == '\t' || cont_arr[1][i] == '\r')
			cont_arr[1][i] = '\0';
		i++;
	}
	return (cont_arr);
}

void	modify_statics(t_scene *scene, int key)
{
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "orient", 7)) && key == MLX_KEY_C)
	{
		if (extract_vector(&vector, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		scene->camera->vector = vector;
	}
	else if (!(ft_strncmp(input_arr[0], "cord", 5)))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		if (key == MLX_KEY_C)
			scene->camera->center = cords;
		else if (key == MLX_KEY_L)
			scene->light->center = cords;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_sphere(t_sphere *object)
{
	char			**input_arr;
	t_coordinates	cords;
	float			dia;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", 5)))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->center = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "dia", 3)))
	{
		dia = get_numbers(input_arr[1], 1);
		if (dia < 0.0F || dia > HEIGHT)
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->diameter = dia;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_plane(t_plane *object)
{
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", 5)))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->coordinates = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "orient", 7)))
	{
		if (extract_vector(&vector, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->vector = vector;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_cyka(t_cylinder *object)
{
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;
	float			height;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", 5)))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->center = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "orient", 7)))
	{
		if (extract_vector(&vector, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->vector = vector;
	}
	else if	(!(ft_strncmp(input_arr[0], "hgt", 4)))
	{
		height = get_numbers(input_arr[1], 1);
		if (height < 0.0F || height > HEIGHT)
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->height = height;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	modify_objects(t_hook_container *data)
{
	int32_t				x;
	int32_t				y;
	t_pixel_cdts		pixel;
	t_viewport			view;
	t_ray				object_ray;
	
	view = initialise_viewport(data->image, data->scene->camera);
	x = 0;
	y = 0;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	printf("x %d y %d\n", (int)x, (int)y);
	pixel.x = x;
	pixel.y = y;
	object_ray = ray_to_object(data->scene, &view, &pixel);
	printf("test object you monkey %d\n", object_ray.inter_point.object_type);
	if (object_ray.inter_point.object_type == 3)
		mod_sphere((t_sphere *)(object_ray.inter_point.object));
	else if (object_ray.inter_point.object_type == 4)
		mod_plane((t_plane *)(object_ray.inter_point.object));
	else if (object_ray.inter_point.object_type == 5)
		mod_cyka((t_cylinder *)(object_ray.inter_point.object));
}

void	key_function(mlx_key_data_t keydata, void *param)
{
	t_hook_container	*data;
	static  int			flag = 0;

	data = (t_hook_container *)param;
	if (flag == 0)
		print_instructions();
	flag = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		print_instructions();
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		modify_objects(data);
		ft_re_render(data);	
	}
	if ((keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS) 
		|| (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS))
	{
		modify_statics(data->scene, keydata.key);
		ft_re_render(data);
	}
}

//esc prints instructions also dont know if we exit properly in general

/*bool mlx_is_mouse_up(mlx_t* mlx, mouse_key_t key)
{
	//MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_RELEASE);
}

void	resize_function(int32_t width, int32_t height, void *param)
{
	t_hook_container	*data;
//	static int			count = 1;

	data = (t_hook_container *)param;
	while(1)
	{
		if ((mlx_is_mouse_up(data->mlx, MLX_MOUSE_BUTTON_LEFT)))
			break;
	}
	if (count % 2 != 0)
	{
		mlx_get_monitor_size(0, &width, &height);
		mlx_set_window_size(data->mlx, width, height);
		mlx_resize_image(data->image, width, height);
		//count++;
	}
	else
	{
		mlx_set_window_size(data->mlx, WIDTH, HEIGHT);
		mlx_resize_image(data->image, WIDTH, HEIGHT);
		count++;
	}
	sleep(1);
}*/

/*void	resize_function(int32_t width, int32_t height, void *param)
{
	t_hook_container	*data;

	(void)width;
	(void)height;
	data = (t_hook_container *)param;
	printf("stuff 1 %d %d\n", data->mlx->width, data->mlx->height);
//	if (data->mlx->height != HEIGHT && data->mlx->width != WIDTH)
//	{
		printf("stuff 2 %d %d\n", data->mlx->width, data->mlx->height);
//		mlx_set_window_size(data->mlx, data->mlx->width, data->mlx->height);
		mlx_resize_image(data->image, data->mlx->height , data->mlx->height);
		ray_trace(data->image, data->scene);
		if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) // dont know if we can just re_render without deleting or do we need to make new image for not leaking
		{
			mlx_delete_image(data->mlx, data->image);
			ft_putmlx_error();
		}
//	}
}*/


