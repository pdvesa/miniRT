NAME			:= miniRT
CFLAGS			:= -Wextra -Wall -Werror
LIBMLX_DIR		:= ./lib/MLX42

LIBFT			:= ./lib/libft/libft.a
LIBFT_DIR		:= ./lib/libft

HEADERS			:= -I ./include -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)
LIBS			:= $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm

SRCS_DIR		:= srcs

SRCS			:=

OBJS			:= ${SRCS:.c=.o}

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