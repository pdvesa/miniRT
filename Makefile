CC					:= clang
NAME                := miniRT
CFLAGS              := -Wextra -Wall -Werror -g
LIBMLX_DIR          := ./lib/MLX42

LIBFT               := ./lib/libft/libft.a
LIBFT_DIR           := ./lib/libft

HEADERS             := -I ./include -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)
LIBS                := $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS_DIR            := srcs
PARSING_DIR         := $(SRCS_DIR)/parsing
RENDER_DIR          := $(SRCS_DIR)/render
MATHS_DIR           := $(SRCS_DIR)/maths
UTILS_DIR           := $(SRCS_DIR)/utils

INTER_DIR           := $(RENDER_DIR)/objects_inter

RENDER_UTILS_DIR    := $(UTILS_DIR)/render_utils
MLX_UTILS_DIR       := $(UTILS_DIR)/mlx_utils

SRCS                := $(SRCS_DIR)/miniRT.c \
                        $(PARSING_DIR)/parse_file.c \
                        $(PARSING_DIR)/read_file.c \
                        $(PARSING_DIR)/validate_content.c \
                        $(PARSING_DIR)/scene_parser.c \
                        $(PARSING_DIR)/parse_utils.c \
                        $(PARSING_DIR)/extractors.c \
                        $(PARSING_DIR)/array_extractors.c \
                        $(PARSING_DIR)/scene_parser2.c \
                        $(RENDER_DIR)/render_scene.c \
                        $(RENDER_DIR)/ray_trace.c \
                        $(RENDER_DIR)/render_thread.c \
                        $(RENDER_DIR)/init_viewport.c \
                        $(RENDER_DIR)/init_render_data.c \
                        $(RENDER_DIR)/lights.c \
                        $(INTER_DIR)/ray_to_object.c \
                        $(INTER_DIR)/normal_to_inter.c \
                        $(INTER_DIR)/sphere_inter.c \
                        $(INTER_DIR)/plane_inter.c \
                        $(INTER_DIR)/cylinder_inter.c \
                        $(MATHS_DIR)/add_vector.c \
                        $(MATHS_DIR)/cross_product.c \
                        $(MATHS_DIR)/dot_product.c \
                        $(MATHS_DIR)/is_in_bounds.c \
                        $(MATHS_DIR)/normalize_vector.c \
                        $(MATHS_DIR)/point_distance.c \
                        $(MATHS_DIR)/poly_root.c \
                        $(MATHS_DIR)/scalar_vec.c \
                        $(MATHS_DIR)/translate_point.c \
                        $(MATHS_DIR)/vector_from_points.c \
                        $(UTILS_DIR)/ft_strappend.c \
                        $(UTILS_DIR)/ft_free_array.c \
                        $(UTILS_DIR)/get_mst.c \
                        $(UTILS_DIR)/atois.c \
                        $(UTILS_DIR)/wait_threads.c \
                        $(RENDER_UTILS_DIR)/add_rgb.c \
                        $(RENDER_UTILS_DIR)/average_rgb.c \
                        $(RENDER_UTILS_DIR)/multiply_rgb.c \
                        $(RENDER_UTILS_DIR)/get_cyka_circles_planes.c \
                        $(RENDER_UTILS_DIR)/get_object_color.c \
                        $(RENDER_UTILS_DIR)/pixel_is_obj_bound.c \
                        $(MLX_UTILS_DIR)/ft_mlx_error.c \
                        $(MLX_UTILS_DIR)/get_pixel_color.c \
                        $(MLX_UTILS_DIR)/set_pixel_color.c 

BUILD_PATH          := build
OBJS                := $(patsubst %.c,$(BUILD_PATH)/%.o,$(SRCS))

all: libmlx $(BUILD_PATH) $(NAME)

libmlx:
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH) $(dir $(OBJS))

$(BUILD_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(BUILD_PATH)
	@rm -rf $(LIBMLX_DIR)/build
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all clean fclean re libmlx
