/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:22 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/21 03:46:56 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
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
# define EPSILON 1e-9
# define PI 3.14159265358979323846

typedef struct s_tuple
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_tuple;

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

typedef struct s_intersection
{
	double			t;
	void			*object;
}					t_intersection;

typedef struct s_intersections
{
	int				count;
	t_intersection	*items;
}					t_intersections;

typedef struct s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct s_matrix
{
	double			**data;
	int				row;
	int				col;
}					t_matrix;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_obj_type;

typedef struct s_material
{
	t_color			color;
	float			diffuse;
	float			specular;
	float			shininess;
}					t_material;

typedef struct s_sphere
{
	t_tuple			center;
	double			radius;
	t_material		material;
}					t_sphere;

typedef struct s_plane
{
	t_tuple			point;
	t_tuple			normal;
	t_material		material;
}					t_plane;

typedef struct s_cylinder
{
	t_tuple			center;
	t_tuple			axis;
	double			radius;
	double			height;
	t_material		material;
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

typedef struct s_render_hit
{
	double			t;
	t_object		*object;
}					t_render_hit;

typedef struct s_ambient
{
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_camera
{
	t_tuple			origin;
	t_tuple			dir;
	t_tuple			right;
	t_tuple			up;
	double			fov;
	double			half_width;
	double			half_height;
	double			pixel_size;
}					t_camera;

typedef struct s_light
{
	t_tuple			pos;
	double			brightness;
	t_color			color;
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
void				put_pixel_to_image(t_rt *rt, int x, int y, t_color color);

void				render_scene(t_rt *rt);
t_color				color_at(t_scene *scene, t_ray ray);
int					closest_object_hit(t_object *objects, t_ray ray,
						t_render_hit *result);
int					object_hit_between(t_object *objects, t_ray ray,
						double min_t, double max_t);
t_tuple				object_normal_at(t_object *object, t_tuple point);
t_material			object_material(t_object *object);

void				init_camera(t_camera *camera);
t_ray				ray_for_pixel(t_camera *camera, int x, int y);

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
int					parse_triplet(char *s, t_tuple *out);
int					parse_color(char *s, t_color *out);

int					count_tokens(char **tokens);
int					parse_range(char *s, double *out, double lo, double hi);
int					parse_point(char *s, t_tuple *out);
int					parse_orientation(char *s, t_tuple *out);
int					parse_positive(char *s, double *out);

int					parse_line(char *line, t_scene *scene);
int					parse_ambient(char **tokens, t_scene *scene);
int					parse_camera(char **tokens, t_scene *scene);
int					parse_light(char **tokens, t_scene *scene);
int					parse_sphere(char **tokens, t_scene *scene);
int					parse_plane(char **tokens, t_scene *scene);
int					parse_cylinder(char **tokens, t_scene *scene);

int					rt_error(char *msg);
void				free_objects(t_object **head);
int					append_object(t_object **head, t_object *obj);

t_tuple				new_tuple(double x, double y, double z, double w);
t_tuple				new_point(double x, double y, double z);
t_tuple				new_vector(double x, double y, double z);

// tuple_math1 methods
t_tuple				add_tuples(t_tuple t1, t_tuple t2);
t_tuple				sub_tuples(t_tuple t1, t_tuple t2);
t_tuple				negate_tuple(t_tuple t);
t_tuple				scale_tuple(t_tuple t, double scalar);
t_tuple				divide_tuple(t_tuple t, double num);

// vector math
double				vector_magnitude(t_tuple vector);
t_tuple				normalize_vector(t_tuple vector);
double				dot_product(t_tuple t1, t_tuple t2);
t_tuple				cross_product(t_tuple t1, t_tuple t2);

// ray sphere
t_ray				new_ray(t_tuple position, t_tuple direction);
t_tuple				position(t_ray ray, double distance);
t_sphere			new_sphere(t_tuple center, double radius, t_color color);
t_intersections		*intersect(t_sphere *sphere, t_ray ray);
t_intersection		new_intersection(double distance, void *object);
t_intersections		*new_intersections(void);
void				append_intrsection(t_intersections *intersections,
						t_intersection new);
void				merge_intersections(t_intersections *result,
						t_intersections *temp);
void				free_intersections(t_intersections *intersections);
t_intersection		*hit(t_intersections *intersections);
t_ray				transform_ray(t_ray ray, t_matrix transformation);

// tuple_utils.c
int					is_equal_d(double a, double b);

// print utils
int					print_error_return(char *msg, int err);

// color
t_color				new_color(double red, double green, double blue);
unsigned int		color_to_rgb(t_color color);
t_color				rgb_to_color(unsigned int rgb);
t_color				add_colors(t_color c1, t_color c2);
t_color				sub_colors(t_color c1, t_color c2);
t_color				scale_color(t_color t, double scalar);
t_color				divide_color(t_color t, double num);
t_color				mult_color(t_color c1, t_color c2);
// matrix
t_matrix			*new_matrix(double *values, int col, int row);
void				free_matrix(t_matrix *m);
double				**create_empty_data(int col, int row);
void				print_matrix(t_matrix *m);

t_matrix			*create_empty_matrix(int col, int row);
t_matrix			*create_identity(int num);
t_matrix			*create_transpose(t_matrix *m);

double				calc_det(t_matrix m);
t_matrix			*submatrix(t_matrix m, int row, int col);
double				minor(t_matrix m, int row, int col);
double				cofactor(t_matrix m, int row, int col);
t_matrix			*divide_matrix_by(t_matrix m, double num);
t_matrix			*invert_matrix(t_matrix m);
t_matrix			*create_cofactor_matrix(t_matrix m);
int					is_equal_matrix(t_matrix t1, t_matrix t2);
t_matrix			*multi_matrix(t_matrix m1, t_matrix m2);
t_tuple				multi_matrix_tuple(t_matrix m, t_tuple t);

// transformations
t_matrix			*create_translation(double x, double y, double z);
t_matrix			*create_scaling(double x, double y, double z);
t_matrix			*rotation_x(double radians);
t_matrix			*rotation_y(double radians);
t_matrix			*rotation_z(double radians);
t_matrix			*create_shear(double xy, double xz, double yx, double yz,
						double zx, double zy);

// Lightning and shading
t_tuple				normal_at(t_sphere sphere, t_tuple point);
t_tuple				reflect(t_tuple in, t_tuple normal);
t_light				point_light(t_tuple position, float brightness,
						t_color color);
t_color				lighting(t_material material, t_light light,
						t_ambient ambient, t_tuple point, t_tuple eyev,
						t_tuple normal);
t_material			material(void);

// plane
t_plane				new_plane(t_tuple point, t_tuple normal, t_color color);
t_intersections		*intersect_plane(t_plane *plane, t_ray ray);

// cylinder
t_cylinder			new_cylinder(t_tuple center, t_tuple axis, double radius,
						double height);
t_intersections		*intersect_cylinder(t_cylinder *cyl, t_ray ray);
t_tuple				cyl_normal_at(t_cylinder cyl, t_tuple point);
void				ft_swap(double *val1, double *val2);
t_tuple				find_radial_projection(t_tuple v, t_tuple axis);
double				calc_t_for_upper_cap(t_cylinder *cyl, t_ray ray,
						t_tuple to_ray);
double				calc_t_for_lower_cap(t_cylinder *cyl, t_ray ray,
						t_tuple to_ray);
t_tuple				calc_radial_v(t_cylinder *cyl, t_ray ray, double t);

#endif
