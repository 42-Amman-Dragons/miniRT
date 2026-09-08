/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normsl_at.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:17:34 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/23 12:24:45 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	cyl_normal_at(t_cylinder cyl, t_tuple point)
{
	t_tuple	v;
	t_tuple	radial_projection;
	double	axial_dist;
	double	radial_squared;

	v = sub_tuples(point, cyl.center);
	axial_dist = dot_product(v, cyl.axis);
	radial_projection = sub_tuples(v, scale_tuple(cyl.axis, axial_dist));
	radial_squared = dot_product(radial_projection, radial_projection);
	if (fabs(axial_dist - cyl.height / 2.0) <= EPSILON
		&& radial_squared <= cyl.radius * cyl.radius + EPSILON)
	{
		return (cyl.axis);
	}
	if (fabs(axial_dist + cyl.height / 2.0) <= EPSILON
		&& radial_squared <= cyl.radius * cyl.radius + EPSILON)
	{
		return (negate_tuple(cyl.axis));
	}
	return (normalize_vector(radial_projection));
}
