#include <miniRT.h>

void	print_instructions(void)
{
		printf("In order to select object to transform click it on the screen\n");
		printf("Possible transformable parameters :\n\tdia (num) for diameter\n\twid (num) for width\n\torientation (num,num,num) for change of direction\n\tcord (num,num,num) for relocation\n");
		printf("Examples: 'dia 35' will change selected sphere diameter to 35, 'orientation 1,1,1' will change selected object or element directional vector!\n");
		printf("Only one modification per press of button!@!\n");
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
	mlx_t	*mlx;
	int32_t x;
	int32_t y;
	
	x = 0;
	y = 0;
	mlx = (mlx_t *)param;
	if (click == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		printf("I got it\n");
		mlx_get_mouse_pos(mlx, &x, &y);
		printf("x %d y %d\n", (int)x, (int)y);
	}
}



void	key_function(mlx_key_data_t keydata, void *param)
{
	//t_scene		*scene;
	mlx_t	*mlx;
	static  int	flag = 0;
	
	
	//scene = (t_scene *)param;
	mlx = (mlx_t *)param;
	if (flag == 0)
		print_instructions();
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		flag = 1;
		printf("Input please\n");
		//func to cast ray and save obj ptr, keyhook?
		mlx_mouse_hook(mlx, mouse_function, mlx);
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		flag = 1;
//		modify_camera(scene);
	}
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
	{
		flag = 1;
		printf("Input please\n");
	}
}

