#include <get_next_line.h>
#include <miniRT_render.h>
#include <miniRT_parsing.h>

void	print_instructions(void)
{
	printf("In order to select object to transform click it on the screen\n");
	printf("Possible transformable parameters :\n\tdia (num) for diameter\n\twid (num) for width\n\thgt (num) for height\n\torient (num,num,num) for change of direction\n\tcord (num,num,num) for relocation\n");
	printf("Examples: 'dia 35' will change selected sphere diameter to 35, 'orient 1,1,1' will change selected object or element directional vector!\n");
	printf("Only one modification per press of button!@!\n");
	printf("If situation occurs where you lost your memories and you need to reprint these instructions press A (for acute amnesia)\n");
}

char	**sanitize_input(char *str)
{
	char	**cont_arr;
	int		i;

	i = 0;
	cont_arr = ft_split(str, ' ');
	if (!cont_arr)
		return (NULL);
	if (ft_strarray_len(cont_arr) != 2)
		return (ft_strarray_free(cont_arr), NULL);
	while(cont_arr[1][i])
	{
		if (cont_arr[1][i] == '\n' || cont_arr[1][i] == '\t' || cont_arr[1][i] == '\r')
			cont_arr[1][i] = '\0';
		i++;
	}
	return (cont_arr);
}

void	modify_camera(t_scene *scene)
{
	char 			*input;
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;

	input = get_next_line(1);
	input_arr = sanitize_input(input);
	free (input);
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "orient", ft_strlen(input_arr[0]))))
	{
		if (extract_vector(&vector, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		scene->camera->vector = vector;
	}
	else if (!(ft_strncmp(input_arr[0], "cord", ft_strlen(input_arr[0]))))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		scene->camera->center = cords;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	modify_light(t_scene *scene)
{
	char 			*input;
	char			**input_arr;
	t_coordinates	cords;

	input = get_next_line(1);
	input_arr = sanitize_input(input);
	free (input);
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", ft_strlen(input_arr[0]))))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		scene->light->center = cords;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_sphere(t_hook_container *data, t_sphere *object)
{
	char 			*input;
	char			**input_arr;
	t_coordinates	cords;
	float			dia;

	printf("Input please\n");
	input = get_next_line(1);
	input_arr = sanitize_input(input);
	free (input);
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", ft_strlen(input_arr[0]))))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->center = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "dia", ft_strlen(input_arr[0]))))
	{
		dia = get_numbers(input_arr[1], 1);
		if (dia < 0.0F || dia > HEIGHT)
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->diameter = dia;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
	ray_trace(data->image, data->scene);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) //does it leak? idk
	{
		mlx_delete_image(data->mlx, data->image);
		return ; //error somewhere
	}
}



void	modify_object(t_hook_container *data)
{
	int32_t				x;
	int32_t				y;
	t_pixel_cdts		pixel;
	t_viewport			view;
	t_ray				object_ray;
	
	view = initialise_viewport(data->image, data->scene->camera);
	x = 0;
	y = 0;
	
	printf("I got it\n");
	mlx_get_mouse_pos(data->mlx, &x, &y);
	printf("x %d y %d\n", (int)x, (int)y);
	pixel.x = x;
	pixel.y = y;
	object_ray = ray_to_object(data->scene, &view, &pixel);
	printf("test object you monkey %d\n", object_ray.inter_point.object_type);
	if (object_ray.inter_point.object_type == 3)
		mod_sphere(data, (t_sphere *)(object_ray.inter_point.object));
/*	else if (object_ray.inter_point.object_type == 4)
		mod_plane();
	else if (object_ray.inter_point.object_type == 5)
		mod_cyka();*/	
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
		modify_object(data);
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		printf("Input please\n");
		modify_camera(data->scene);
		ray_trace(data->image, data->scene);
		if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) //does it leak? idk
		{
			mlx_delete_image(data->mlx, data->image);
			return ; //error somewhere
		}
	}
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	{
		printf("Input please\n");
		modify_light(data->scene);
		ray_trace(data->image, data->scene);
		if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) //does it leak? idk
		{
			mlx_delete_image(data->mlx, data->image);
			return ; //error somewhere
		}
	}
}

