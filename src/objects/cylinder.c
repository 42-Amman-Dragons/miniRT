/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:13:27 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/23 12:41:24 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_cylinder	new_cylinder(t_tuple center, t_tuple axis, double radius,
		double height)
{
    t_cylinder  cyl;
    
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
	t_tuple		    point;
	float			axis_distance;

	xs = new_intersections();
	if (!xs)
		return (NULL);
	point = position(ray, t0);
	axis_distance = dot_product(cyl->axis,
			sub_tuples(point, cyl->center));
	if (axis_distance <= cyl->height / 2 && axis_distance >= -cyl->height / 2)
		append_intrsection(xs, new_intersection(t0, cyl));
	point = position(ray, t1);
	axis_distance = dot_product(cyl->axis,
			sub_tuples(point, cyl->center));
	if (axis_distance <= cyl->height / 2 && axis_distance > -cyl->height / 2)
		append_intrsection(xs, new_intersection(t1, cyl));
	return (xs);
}

void add_upper_intersection(t_intersections	**xs,t_cylinder *cyl, t_ray ray, t_tuple to_ray)
{
	double t;
	t_tuple radial_p;

	t = calc_t_for_upper_cap(cyl,ray, to_ray);
	radial_p = calc_radial_v(cyl, ray, t);
	if(dot_product(radial_p, radial_p) <= pow(cyl->radius,2))
	{
		append_intrsection(*xs, new_intersection(
			t,
			cyl
		));
	}
}

void add_lower_intersection(t_intersections	**xs,t_cylinder *cyl, t_ray ray, t_tuple to_ray)
{
	double t;
	t_tuple radial_p;

	t = calc_t_for_lower_cap(cyl,ray, to_ray);
	radial_p = calc_radial_v(cyl, ray, t);
	if(dot_product(radial_p, radial_p) <= pow(cyl->radius,2))
	{
		append_intrsection(*xs, new_intersection(
			t,
			cyl
		));
	}
}

t_intersections *intersect_cap(t_cylinder *cyl, t_ray ray)
{
	t_intersections	*xs;
	t_tuple	to_ray;
	double			denominator;

	denominator = dot_product(cyl->axis, ray.direction);
	if (is_equal_d(denominator, 0))
		return (NULL);
	xs = new_intersections();
	if (!xs)
		return (NULL);
	to_ray = sub_tuples(ray.origin, cyl->center);
	add_upper_intersection(&xs, cyl, ray, to_ray);
	add_lower_intersection(&xs, cyl, ray, to_ray);
	return (xs);
}

t_intersections	*intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_tuple			origin;
	t_tuple			direction;
	t_intersections	*xs;

	origin = sub_tuples(ray.origin, cyl->center);
	origin = find_radial_projection(origin, cyl->axis);
	direction = find_radial_projection(ray.direction, cyl->axis);
	a = dot_product(direction, direction);
	b = 2 * dot_product(origin, direction);
	c = dot_product(origin, origin) - cyl->radius * cyl->radius;
	xs = new_intersections();
	if (!is_equal_d(a, 0))
	{
		discriminant = b * b - 4.0 * a * c;
		if (discriminant >= 0)
			merge_intersections(xs, calc_cylinder_intersections((-b
					- sqrt(discriminant)) / (2 * a), (-b + sqrt(discriminant))
					/ (2 * a), ray, cyl));
	}
	merge_intersections(xs, intersect_cap(cyl, ray));
	return (xs);
}
