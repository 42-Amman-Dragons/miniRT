#ifndef MINIRT_H
# define MINIRT_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define WIN_W 800
# define WIN_H 600
# define KEY_ESC 65307
# define EV_KEYPRESS 2
# define EV_EXPOSE 12
# define EV_DESTROY 17
# define MASK_KEYPRESS 1L
# define MASK_EXPOSE 32768L

typedef struct s_tuple
{
    float x;
    float y;
    float z;
    float w;
} t_tuple;


typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

// typedef struct s_color
// {
//     float red;
//     float green;
//     float blue;
// } t_color;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_canvas
{
    int width;
    int height;
    t_color *pixels;
} t_canvas;

typedef struct s_matrix
{
    float **data;
    int row;
    int col;
} t_matrix;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_obj_type;

typedef struct s_sphere
{
	int				todo;
}					t_sphere;

typedef struct s_plane
{
	int				todo;
}					t_plane;

typedef struct s_cylinder
{
	int				todo;
}					t_cylinder;

typedef union u_shape
{
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
}					t_shape;

typedef struct s_object
{
	t_obj_type		type;
	t_color			color;
	t_shape			shape;
	struct s_object	*next;
}					t_object;

typedef struct s_ambient
{
	int				todo;
}					t_ambient;

typedef struct s_camera
{
	int				todo;
}					t_camera;

typedef struct s_light
{
	int				todo;
}					t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
	int				has_ambient;
	int				has_camera;
	int				has_light;
}					t_scene;

typedef struct s_rt
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	t_scene			scene;
}					t_rt;

int					init_mlx(t_rt *rt);
void				cleanup_rt(t_rt *rt);
int					close_rt(t_rt *rt);

int					on_key(int keycode, t_rt *rt);
int					on_destroy(t_rt *rt);
int					on_expose(t_rt *rt);

int					parse_scene(char *path, t_scene *scene);
int					has_rt_extension(char *path);
int					read_scene(int fd, t_scene *scene);
int					check_scene(t_scene *scene);

int					is_space(char c);
int					count_words(char *s);
int					word_len(char *s);
char				**split_ws(char *line);
void				free_tokens(char **tokens);

int					parse_int(char *s, int *out);
int					parse_double(char *s, double *out);
int					parse_vec3(char *s, t_vec3 *out);
int					parse_color(char *s, t_color *out);

int					parse_line(char *line, t_scene *scene);
int					parse_ambient(char **tokens, t_scene *scene);
int					parse_camera(char **tokens, t_scene *scene);
int					parse_light(char **tokens, t_scene *scene);
int					parse_sphere(char **tokens, t_scene *scene);
int					parse_plane(char **tokens, t_scene *scene);
int					parse_cylinder(char **tokens, t_scene *scene);

int					rt_error(char *msg);
void				free_objects(t_object **head);



t_tuple new_tuple(float x, float y, float z, float w);
t_tuple new_point(float x, float y, float z);
t_tuple new_vector(float x, float y, float z);

// tuple_math1 methods
t_tuple add_tuples(t_tuple t1, t_tuple t2);
t_tuple sub_tuples(t_tuple t1, t_tuple t2);
t_tuple negate_tuple(t_tuple t);
t_tuple scale_tuple(t_tuple t, float scalar);
t_tuple divide_tuple(t_tuple t, float num);


// vector math
float vector_magnitude(t_tuple vector);
t_tuple normalize_vector(t_tuple vector);
float dot_product(t_tuple t1, t_tuple t2);


//tuple_utils.c
int is_equal_f(float a, float b);

// print utils
int print_error_return(char *msg, int err);

// canvas
t_color new_color(float red, float green, float blue);
t_color add_colors(t_color c1, t_color c2);
t_color sub_colors(t_color c1, t_color c2);
t_color scale_color(t_color t, float scalar);
t_color divide_color(t_color t, float num);
t_color mult_color(t_color c1, t_color c2);
t_canvas *new_canvas(int width, int height);
void free_canvas(t_canvas *canvas);
void write_pixel(t_canvas *canvas, int x, int y, t_color color);
t_color get_pixel(t_canvas *canvas, int x, int y);

// matrix
t_matrix *new_matrix(float *values, int col, int row);
void free_matrix(t_matrix *m);
float **create_empty_data(int col, int row);

t_matrix *create_empty_matrix(int col, int row);
t_matrix *create_identity(int num);
t_matrix *create_transpose(t_matrix *m);

float calc_det(t_matrix m);
t_matrix *submatrix(t_matrix m, int row, int col);
float minor(t_matrix m, int row, int col);
float cofactor(t_matrix m, int row, int col);
t_matrix *divide_matrix_by(t_matrix m, float num);
t_matrix *invert_matrix(t_matrix m);
t_matrix *create_cofactor_matrix(t_matrix m);
int is_equal_matrix(t_matrix t1, t_matrix t2);
t_matrix *multi_matrix(t_matrix m1, t_matrix m2);
t_tuple multi_matrix_tuple(t_matrix m, t_tuple t);

// transformations
t_matrix *create_translation(float x, float y, float z);
t_matrix *create_scaling(float x, float y, float z);
t_matrix *rotation_x(float radians);
t_matrix *rotation_y(float radians);
t_matrix *rotation_z(float radians);
t_matrix *create_shear(float xy, float xz, float yx, float yz, float zx, float zy);

#endif
