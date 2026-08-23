/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/23 11:25:34 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*This will be redone later*/
t_color	color_at(t_scene *scene, t_ray ray)
{
	t_render_hit	closest;
	t_tuple			point;
	t_tuple			eye;
	t_tuple			normal;

	/**/
	if (!closest_object_hit(scene->objects, ray, &closest))
		return (new_color(0.0, 0.0, 0.0));
	point = position(ray, closest.t);
	eye = negate_tuple(ray.direction);
	normal = object_normal_at(closest.object, point);
	if (dot_product(normal, eye) < 0.0)
		normal = negate_tuple(normal);
	return (lighting(object_material(closest.object), scene->light,
			scene->ambient, prepare_basic_calc(
				point,
				eye,
				normal
			)));
}
/*This will be redone later*/

void	render_scene(t_rt *rt)
{
	t_ray	ray;
	int		x;
	int		y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = ray_for_pixel(&rt->scene.camera, x, y);
			put_pixel_to_image(rt, x, y, color_at(&rt->scene, ray));
			x++;
		}
		y++;
	}
}
