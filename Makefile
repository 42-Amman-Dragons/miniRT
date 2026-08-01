NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= includes/minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a

LIBFT_DIR	= includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a

INC			= -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)
LIBS		= $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= main.c \
			  parsing/parse.c \
			  parsing/parse_utils.c \
			  parsing/tokenize.c \
			  parsing/parse_num.c \
			  parsing/parse_field.c \
			  parsing/parse_elements.c \
			  parsing/parse_objects.c \
			  window/init_mlx.c \
			  window/hooks.c

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/minirt.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
