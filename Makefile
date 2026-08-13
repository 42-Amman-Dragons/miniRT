NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEBUGFLAGS = -g

MLX_DIR		= includes/minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a

LIBFT_DIR	= includes/libft
LIBFT		= $(LIBFT_DIR)/libft.a

INC			= -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)
LIBS		= $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR		= src
OBJ_DIR		= obj

COLOR_DIR = color
RAY_DIR = ray_sphere
TUPLES_DIR = tuples
MATRIX_DIR = matrix
MATRIX_TRANS_DIR = matrix_transformations
LIGHT_SHADING_DIR = light
PLANE_DIR = plane
CAMERA_DIR = camera

SRC			= main.c \
			  parsing/parse.c \
			  parsing/parse_utils.c \
			  parsing/tokenize.c \
			  parsing/parse_num.c \
			  parsing/parse_field.c \
			  parsing/parse_check.c \
			  parsing/parse_elements.c \
			  parsing/parse_objects.c \
			  window/init_mlx.c \
			  window/hooks.c \
			  window/pexils_to_image.c

TUPLES_SRC = tuple.c tuple_utils.c print_utils.c tuple_math1.c vector_math1.c
COLOR_SRC = color.c color_math.c
RAY_SRC = ray.c sphere.c intersections_mangement.c hit.c
MATRIX_SRC = matrix.c matrix_math.c matrices.c invert_matrix.c invert_matrix_utils.c
MATRIX_TRANS_SRC = translation.c scaling.c rotation.c shearing.c
LIGHT_SHADING_SRC = normals.c reflect.c light.c material.c
PLANE_SRC = plane.c
CAMERA_SRC = init-camera.c

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o) \
$(addprefix $(OBJ_DIR)/$(TUPLES_DIR)/, $(TUPLES_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(MATRIX_DIR)/, $(MATRIX_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(MATRIX_TRANS_DIR)/, $(MATRIX_TRANS_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(COLOR_DIR)/, $(COLOR_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(RAY_DIR)/, $(RAY_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(LIGHT_SHADING_DIR)/, $(LIGHT_SHADING_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(PLANE_DIR)/, $(PLANE_SRC:.c=.o)) \
$(addprefix $(OBJ_DIR)/$(CAMERA_DIR)/, $(CAMERA_SRC:.c=.o))

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

debug: CFLAGS+=$(DEBUGFLAGS)
debug: all

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/minirt.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(TUPLES_DIR)/%.o: $(SRC_DIR)/$(TUPLES_DIR)/%.c includes/minirt.h
	mkdir -p $(OBJ_DIR)/$(TUPLES_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(COLOR_DIR)/%.o: $(SRC_DIR)/$(COLOR_DIR)/%.c includes/minirt.h
	mkdir -p $(OBJ_DIR)/$(COLOR_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(RAY_DIR)/%.o: $(SRC_DIR)/$(RAY_DIR)/%.c includes/minirt.h
	mkdir -p $(OBJ_DIR)/$(RAY_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(MATRIX_DIR)/%.o: $(SRC_DIR)/$(MATRIX_DIR)/%.c includes/minirt.h
	mkdir -p $(OBJ_DIR)/$(MATRIX_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(MATRIX_TRANS_DIR)/%.o: $(SRC_DIR)/$(MATRIX_TRANS_DIR)/%.c includes/minirt.h
	mkdir -p $(OBJ_DIR)/$(MATRIX_TRANS_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(LIGHT_SHADING_DIR)/%.o: $(SRC_DIR)/$(LIGHT_SHADING_DIR)/%.c
	mkdir -p $(OBJ_DIR)/$(LIGHT_SHADING_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(PLANE_DIR)/%.o: $(SRC_DIR)/$(PLANE_DIR)/%.c
	mkdir -p $(OBJ_DIR)/$(PLANE_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/$(CAMERA_DIR)/%.o: $(SRC_DIR)/$(CAMERA_DIR)/%.c
	mkdir -p $(OBJ_DIR)/$(CAMERA_DIR)
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
