NAME				:= miniRT
CFLAGS				:= -Wextra -Wall -Werror
LIBMLX_DIR			:= ./lib/MLX42

LIBFT				:= ./lib/libft/libft.a
LIBFT_DIR			:= ./lib/libft

HEADERS				:= -I ./include -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)
LIBS				:= $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm

SRCS_DIR			:= srcs
PARSING_DIR			:= $(SRCS_DIR)/parsing
RENDER_DIR			:= $(SRCS_DIR)/render
HOOKS_DIR			:= $(SRCS_DIR)/hooks
MATHS_DIR			:= $(SRCS_DIR)/maths
UTILS_DIR			:= $(SRCS_DIR)/utils

INTER_DIR			:= $(RENDER_DIR)/objects_inter

RENDER_UTILS_DIR	:= $(UTILS_DIR)/render_utils
MLX_UTILS_DIR		:= $(UTILS_DIR)/mlx_utils


SRCS				:= $(SRCS_DIR)/miniRT.c \
						$(PARSING_DIR)/parse_file.c \
						$(PARSING_DIR)/read_file.c \
						$(PARSING_DIR)/validate_content.c \
						$(PARSING_DIR)/scene_parser.c \
						$(RENDER_DIR)/render_scene.c \
						$(RENDER_DIR)/ray_trace.c \
						$(RENDER_DIR)/ray_to_object.c \
						$(RENDER_DIR)/ray_direction.c \
						$(RENDER_DIR)/lights.c \
						$(RENDER_DIR)/switch_cam_hook.c \
						$(INTER_DIR)/get_closer_inter.c \
						$(INTER_DIR)/normal_to_inter.c \
						$(INTER_DIR)/sphere_inter.c \
						$(INTER_DIR)/plane_inter.c \
						$(INTER_DIR)/cylinder_inter.c \
						$(MATHS_DIR)/points_distance.c \
						$(MATHS_DIR)/vector_arithmetics.c \
						$(MATHS_DIR)/orthogonal_vector.c \
						$(MATHS_DIR)/poly_root.c \
						$(MATHS_DIR)/translate_point.c \
						$(MATHS_DIR)/far_point.c \
						$(MATHS_DIR)/points_equals.c \
						$(UTILS_DIR)/ft_strappend.c \
						$(UTILS_DIR)/ft_free_array.c \
						$(UTILS_DIR)/ft_array_len.c \
						$(RENDER_UTILS_DIR)/add_rgb.c \
						$(RENDER_UTILS_DIR)/get_cyka_circles_planes.c \
						$(MLX_UTILS_DIR)/ft_mlx_error.c \
						$(MLX_UTILS_DIR)/get_color_int.c

OBJS					:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

$(LIBFT) :	$(LIBFT_DIR)
			@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX_DIR)/build
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libmlx