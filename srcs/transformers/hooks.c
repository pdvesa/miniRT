#include <miniRT_render.h>

void	print_instructions(void)
{
	printf("In order to select object to transform click it on the screen\n");
	printf("Possible transformable parameters :\n\tdia (num) for diameter\n\twid (num) for width\n\thgt (num) for height\n\torient (num,num,num) for change of direction\n\tcord (num,num,num) for relocation\n");
	printf("Examples: 'dia 35' will change selected sphere diameter to 35, 'orient 1,1,1' will change selected object or element directional vector!\n");
	printf("Only one modification per press of button!@!\n");
	printf("If situation occurs where you lost your memories and you need to reprint these instructions press A (for acute amnesia)\n");
}

//void	modify_camera(t_scene *scene)
//{
//	char *input;
//
//	printf("Input please\n");
//	input = get_next_line(1);
//	printf("%s\n", input);
	//validate_input(input);
//}

void	mouse_function(mouse_key_t click, action_t action, modifier_key_t mods, void *param)
{
	t_hook_container	*data;
	int32_t				x;
	int32_t				y;
	t_pixel_cdts		pixel;
	t_viewport			view;
	t_ray				object_ray;
	
	(void) mods;
	data = (t_hook_container *)param;
	view = initialise_viewport(data->image, data->scene->camera);
	x = 0;
	y = 0;
	if (click == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		printf("I got it\n");
		mlx_get_mouse_pos(data->mlx, &x, &y);
		printf("x %d y %d\n", (int)x, (int)y);
		pixel.x = x;
		pixel.y = y;
		object_ray = ray_to_object(data->scene, &view, &pixel);
		printf("test object you monkey %d\n", object_ray.inter_point.object_type);
	}
}
//the mousehook keeps running after first initialized, saving the clicks
//cant find terminate hook func so need to do it manually or ignore if it causes no problems after testing
//there was mlx func that returns boolean when clicked if needed

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
		printf("Input please\n");
		mlx_mouse_hook(data->mlx, mouse_function, data);
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		printf("Input please\n");
//		modify_camera(data->scene);
	}
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	{
		printf("Input please\n");
//		modify_light(data->scene);
	}
}

