/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:56:19 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/09/08 15:57:32 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_upper_intersection(t_intersections **xs, t_cylinder *cyl, t_ray ray,
		t_tuple to_ray)
{
	double	t;
	t_tuple	radial_p;

	t = calc_t_for_upper_cap(cyl, ray, to_ray);
	radial_p = calc_radial_v(cyl, ray, t);
	if (dot_product(radial_p, radial_p) <= pow(cyl->radius, 2) + EPSILON)
	{
		append_intrsection(*xs, new_intersection(t, cyl));
	}
}

void	add_lower_intersection(t_intersections **xs, t_cylinder *cyl, t_ray ray,
		t_tuple to_ray)
{
	double	t;
	t_tuple	radial_p;

	t = calc_t_for_lower_cap(cyl, ray, to_ray);
	radial_p = calc_radial_v(cyl, ray, t);
	if (dot_product(radial_p, radial_p) <= pow(cyl->radius, 2) + EPSILON)
	{
		append_intrsection(*xs, new_intersection(t, cyl));
	}
}

t_intersections	*intersect_cap(t_cylinder *cyl, t_ray ray)
{
	t_intersections	*xs;
	t_tuple			to_ray;
	double			denominator;

	denominator = dot_product(cyl->axis, ray.direction);
	if (fabs(denominator) < EPSILON)
		return (NULL);
	xs = new_intersections();
	if (!xs)
		return (NULL);
	to_ray = sub_tuples(ray.origin, cyl->center);
	add_upper_intersection(&xs, cyl, ray, to_ray);
	if (!is_equal_d(cyl->height, 0.0))
		add_lower_intersection(&xs, cyl, ray, to_ray);
	return (xs);
}
