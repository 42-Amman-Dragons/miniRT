/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:22 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/10 13:12:42 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void	render_test_sphere(t_rt *rt)
// {
// 	t_sphere		sphere;
// 	t_intersections	*xs;
// 	t_color			color;
// 	int				x;
// 	int				y;

// 	sphere = new_sphere(new_point(0.5, 0.0, 0.0), 2.0);
// 	color = new_color(1.0, 0.0, 0.0);
// 	y = 0;
// 	while (y < WIN_H)
// 	{
// 		x = 0;
// 		while (x < WIN_W)
// 		{
// 			xs = intersect(&sphere, ray_for_pixel(&rt->scene.camera, x, y));
// 			if (hit(xs))
// 				put_pixel_to_image(rt, x, y, color);
// 			free_intersections(xs);
// 			x++;
// 		}
// 		y++;
// 	}
// }
/*--------------------------------------*/
// test shading and lightning
t_light add_light_source(t_rt *rt)
{
   return(
	point_light(
		rt->scene.light.pos,
		rt->scene.light.brightness,
		rt->scene.light.color
	)
   );
}

// static void	render_test_sphere2(t_rt *rt)
// {
// 	t_sphere		sphere;
// 	t_intersections	*xs;
// 	t_color			color;
// 	t_light			light;
// 	t_intersection  *h;
// 	t_tuple			point;
// 	t_tuple			normal;
// 	t_tuple			eyev;
// 	t_ray			ray;
// 	int				x;
// 	int				y;

// 	sphere = new_sphere(new_point(0.5, 0.0, 0.0), 2.0);
// 	sphere.material.color = new_color(1,0,0);
// 	light = add_light_source(rt);
// 	y = 0;
// 	while (y < WIN_H)
// 	{
// 		x = 0;
// 		while (x < WIN_W)
// 		{
// 			ray = ray_for_pixel(&rt->scene.camera, x, y);
// 			xs = intersect(&sphere, ray);
// 			h = hit(xs);
// 			if (h)
// 			{
// 				point = position(ray, h->t);
// 				eyev = sub_tuples(point, ray.origin);
// 				normal = normal_at(sphere, point);
// 				color = lighting(sphere.material, light, point, eyev, normal);
// 				put_pixel_to_image(rt, x, y, color);
// 			}
// 			free_intersections(xs);
// 			x++;
// 		}
// 		y++;
// 	}
// }

static void	render_test_plane(t_rt *rt)
{
	t_plane		plane;
	t_intersections	*xs;
	t_color			color;
	t_light			light;
	t_intersection  *h;
	t_tuple			point;
	t_tuple			eyev;
	t_ray			ray;
	int				x;
	int				y;

	plane = new_plane(new_point(0.0, -1.0, 0.0),
			new_vector(0.0, 1.0, 0.0), new_color(1.0, 0.0, 0.0));
	light = point_light(new_point(-5.0, 10.0, -5.0), 1.0,
			new_color(1.0, 1.0, 1.0));
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = ray_for_pixel(&rt->scene.camera, x, y);
			xs = intersect_plane(plane, ray);
			h = hit(xs);
			if (h)
			{
				point = position(ray, h->t);
				eyev = negate_tuple(ray.direction);
				color = lighting(plane.material, light, rt->scene.ambient,
						point, eyev, plane.normal);
				put_pixel_to_image(rt, x, y, color);
			}
			free_intersections(xs);
			x++;
		}
		y++;
	}
}
/*--------------------------------------*/

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
	{
		write(2, "Error\nusage: ./miniRT <scene.rt>\n", 33);
		return (1);
	}
	ft_bzero(&rt.scene, sizeof(t_scene));
	if (parse_scene(argv[1], &rt.scene))
		return (1);
	init_camera(&rt.scene.camera);
	if (init_mlx(&rt))
	{
		cleanup_rt(&rt);
		write(2, "Error\nmlx initialisation failed\n", 32);
		return (1);
	}
	// render_test_sphere(&rt);
	// render_test_sphere2(&rt);
	render_test_plane(&rt);
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img, 0, 0);
	mlx_loop(rt.mlx);
	return (0);
}
