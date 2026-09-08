/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init-camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by mabuqare          #+#    #+#             */
/*   Updated: 2026/09/08 15:24:39 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tuple	world_up_for(t_tuple direction)
{
	if (fabs(direction.y) > 1.0 - EPSILON)
		return (new_vector(0.0, 0.0, 1.0));
	return (new_vector(0.0, 1.0, 0.0));
}

void	init_camera(t_camera *camera)
{
	double	aspect_ratio;
	double	half_view;
	t_tuple	world_up;

	aspect_ratio = (double)WIN_W / (double)WIN_H;
	half_view = tan(camera->fov * PI / 360.0);
	if (aspect_ratio >= 1.0)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect_ratio;
	}
	else
	{
		camera->half_width = half_view * aspect_ratio;
		camera->half_height = half_view;
	}
	camera->pixel_size = camera->half_width * 2.0 / (double)WIN_W;
	world_up = world_up_for(camera->dir);
	camera->right = normalize_vector(cross_product(world_up, camera->dir));
	camera->up = normalize_vector(cross_product(camera->dir, camera->right));
}

t_ray	ray_for_pixel(t_camera *camera, int x, int y)
{
	t_tuple	direction;
	double	camera_x;
	double	camera_y;

	camera_x = -camera->half_width + (x + 0.5) * camera->pixel_size;
	camera_y = camera->half_height - (y + 0.5) * camera->pixel_size;
	direction = add_tuples(camera->dir, scale_tuple(camera->right, camera_x));
	direction = add_tuples(direction, scale_tuple(camera->up, camera_y));
	return (new_ray(camera->origin, normalize_vector(direction)));
}
