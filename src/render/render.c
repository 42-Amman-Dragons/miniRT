/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by mabuqare          #+#    #+#             */
/*   Updated: 2026/09/05 02:18:05 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define SHADOW_BIAS 1e-5

static int	is_shadowed(t_scene *scene, t_tuple point, t_tuple normal)
{
	t_tuple	over_point;
	t_tuple	to_light;
	double	distance;
	t_ray	shadow_ray;

	over_point = add_tuples(point, scale_tuple(normal, SHADOW_BIAS));
	to_light = sub_tuples(scene->light.pos, over_point);
	distance = vector_magnitude(to_light);
	if (distance <= SHADOW_BIAS)
		return (0);
	shadow_ray = new_ray(over_point, normalize_vector(to_light));
	return (object_hit_between(scene->objects, shadow_ray, SHADOW_BIAS, distance
			- SHADOW_BIAS));
}

static t_color	ambient_at(t_material material, t_ambient ambient)
{
	return (scale_color(mult_color(material.color, ambient.color),
			ambient.ratio));
}

t_color	color_at(t_scene *scene, t_ray ray)
{
	t_render_hit	closest;
	t_material		material;
	t_tuple			point;
	t_tuple			eye;
	t_tuple			normal;

	if (!closest_object_hit(scene->objects, ray, &closest))
		return (new_color(0.0, 0.0, 0.0));
	point = position(ray, closest.t);
	eye = negate_tuple(ray.direction);
	normal = object_normal_at(closest.object, point);
	if (dot_product(normal, eye) < 0.0)
		normal = negate_tuple(normal);
	material = object_material(closest.object);
	if (is_shadowed(scene, point, normal))
		return (ambient_at(material, scene->ambient));
	return (lighting(material, scene->light, scene->ambient,
			prepare_basic_calc(point, eye, normal)));
}

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
