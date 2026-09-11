/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:13:27 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/09/08 15:55:54 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	new_cylinder(t_tuple center, t_tuple axis, double radius,
		double height)
{
	t_cylinder	cyl;

	cyl.center = center;
	cyl.axis = axis;
	cyl.radius = radius;
	cyl.height = height;
	return (cyl);
}

static t_intersections	*calc_cylinder_intersections(double t0, double t1,
		t_ray ray, t_cylinder *cyl)
{
	t_intersections	*xs;
	t_tuple			point;
	double			axis_distance;

	xs = new_intersections();
	if (!xs)
		return (NULL);
	point = position(ray, t0);
	axis_distance = dot_product(cyl->axis, sub_tuples(point, cyl->center));
	if (axis_distance <= cyl->height / 2.0 + EPSILON
		&& axis_distance >= -cyl->height / 2.0 - EPSILON)
		append_intrsection(xs, new_intersection(t0, cyl));
	point = position(ray, t1);
	axis_distance = dot_product(cyl->axis, sub_tuples(point, cyl->center));
	if (axis_distance <= cyl->height / 2.0 + EPSILON
		&& axis_distance >= -cyl->height / 2.0 - EPSILON)
		append_intrsection(xs, new_intersection(t1, cyl));
	return (xs);
}

void	add_cylinder_intersections(t_intersections *xs, double abc[3],
	t_ray ray, t_cylinder *cyl)
{
	double	discriminant;

	discriminant = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (discriminant >= -EPSILON)
	{
		if (discriminant < 0.0)
			discriminant = 0.0;
		merge_intersections(xs, calc_cylinder_intersections((-abc[1]
					- sqrt(discriminant)) / (2 * abc[0]), (-abc[1]
					+ sqrt(discriminant)) / (2 * abc[0]), ray, cyl));
	}
}

t_intersections	*intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	double			abc[3];
	t_tuple			origin;
	t_tuple			direction;
	t_intersections	*xs;

	if (!cyl || cyl->radius <= 0.0 || cyl->height < 0.0)
		return (NULL);
	origin = sub_tuples(ray.origin, cyl->center);
	origin = find_radial_projection(origin, cyl->axis);
	direction = find_radial_projection(ray.direction, cyl->axis);
	abc[0] = dot_product(direction, direction);
	abc[1] = 2 * dot_product(origin, direction);
	abc[2] = dot_product(origin, origin) - cyl->radius * cyl->radius;
	xs = new_intersections();
	if (!xs)
		return (NULL);
	if (!is_equal_d(cyl->height, 0.0) && !is_equal_d(abc[0], 0))
	{
		add_cylinder_intersections(xs, abc, ray, cyl);
	}
	merge_intersections(xs, intersect_cap(cyl, ray));
	return (xs);
}
