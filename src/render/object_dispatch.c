/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 00:00:00 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/13 00:00:00 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersections	*intersect_object(t_object *object, t_ray ray)
{
	if (object->type == OBJ_SPHERE)
		return (intersect(&object->shape.sphere, ray));
	if (object->type == OBJ_PLANE)
		return (intersect_plane(object->shape.plane, ray));
	return (NULL);
}

int	closest_object_hit(t_object *objects, t_ray ray, t_render_hit *result)
{
	t_intersections	*xs;
	t_intersection	*current;

	result->t = HUGE_VAL;
	result->object = NULL;
	while (objects)
	{
		xs = intersect_object(objects, ray);
		current = hit(xs);
		if (current && current->t < result->t)
		{
			result->t = current->t;
			result->object = objects;
		}
		free_intersections(xs);
		objects = objects->next;
	}
	return (result->object != NULL);
}

t_tuple	object_normal_at(t_object *object, t_tuple point)
{
	if (object->type == OBJ_SPHERE)
		return (normal_at(object->shape.sphere, point));
	if (object->type == OBJ_PLANE)
		return (object->shape.plane.normal);
	return (new_vector(0.0, 0.0, 0.0));
}

t_material	object_material(t_object *object)
{
	t_material	result;

	result = material();
	result.color = object->color;
	return (result);
}
