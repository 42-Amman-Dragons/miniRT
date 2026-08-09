/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 00:00:00 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/09 00:00:00 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	new_sphere(t_tuple center, double radius)
{
	return ((t_sphere){center, radius});
}

static t_intersections	*calc_intersections(double a, double b,
		double discriminant, t_sphere *sphere)
{
	t_intersections	*xs;

	xs = new_intersections();
	if (!xs)
		return (NULL);
	xs->items = ft_calloc(2, sizeof(t_intersection));
	if (!xs->items)
		return (free_intersections(xs), NULL);
	xs->items[0] = new_intersection((-b - sqrt(discriminant)) / (2 * a),
			sphere);
	xs->items[1] = new_intersection((-b + sqrt(discriminant)) / (2 * a),
			sphere);
	xs->count = 2;
	return (xs);
}

t_intersections	*intersect(t_sphere *sphere, t_ray ray)
{
	t_tuple	offset;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	if (!sphere || sphere->radius <= 0.0)
		return (NULL);
	offset = sub_tuples(ray.origin, sphere->center);
	a = dot_product(ray.direction, ray.direction);
	if (fabs(a) < EPSILON)
		return (NULL);
	b = 2.0 * dot_product(ray.direction, offset);
	c = dot_product(offset, offset) - sphere->radius * sphere->radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (NULL);
	return (calc_intersections(a, b, discriminant, sphere));
}
