/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:19:14 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/11 16:19:26 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	axial dist for v = v.axis<<normalized>>
	radial projection --> remove the axial part
	v - axis * axial dist
	
	note : 
		the axial projection can be calculated using 
		axis * axial_dist 
*/
t_tuple find_radial_projection(t_tuple v, t_tuple axis)
{
	double axial_dist;

	axial_dist = dot_product(v, axis);
	return (sub_tuples(v, scale_tuple(axis, axial_dist)));
}


/*
y(t) = axis.(p0 + vt1) <-- axial distance :D
located in the upeer cap means y(t) = h/2
so:
	axis.(p0 + vt1) = h/2
	axis.p0 + t(axis.v) = h/2
	...
	...
	t = (h/2 - axis.p0) / axis.v

	when calculating along the axis 
	(h/2 - dot(p0 - center, axis))/ dot(axis, v)
*/
double calc_t_for_upper_cap(t_cylinder *cyl, t_ray ray, t_tuple to_ray)
{
	return(
		(cyl->height / 2.0 - 
		dot_product(cyl->axis, to_ray)) 
		/ dot_product(cyl->axis,ray.direction)
	);
}

double calc_t_for_lower_cap(t_cylinder *cyl, t_ray ray, t_tuple to_ray)
{
	return(
		(-cyl->height / 2.0 - 
		dot_product(cyl->axis, to_ray)) 
		/ dot_product(cyl->axis,ray.direction)
	);
}

t_tuple calc_radial_v(t_cylinder *cyl, t_ray ray, double t)
{
	t_tuple			point;
	t_tuple			v;
	t_tuple			radial_projection;

	point = add_tuples(ray.origin, scale_tuple(ray.direction, t)); 
	v = sub_tuples(point, cyl->center);
	radial_projection = find_radial_projection(v, cyl->axis);
	return (radial_projection);
}