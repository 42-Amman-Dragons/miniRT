#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 800
# define WIN_H 600
# define KEY_ESC 65307
# define EV_KEYPRESS 2
# define EV_EXPOSE 12
# define EV_DESTROY 17
# define MASK_KEYPRESS 1L
# define MASK_EXPOSE 32768L

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

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

#endif
