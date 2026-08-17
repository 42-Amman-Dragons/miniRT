/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:13:27 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/17 10:38:56 by hal-lawa         ###   ########.fr       */
=======
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:13:27 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/15 21:29:45 by mabuqare         ###   ########.fr       */
>>>>>>> 879d19cd38982959428b0758c6af2fa09bcdb858
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// The calculations assumes that the normal is 0,1,0 so a transformation
// should be made to make it match the normal provided by the .rt file
// Notes:
// The normal in the upper cap is not the same as the lower cap they are inverted.

t_cylinder	new_cylinder(t_tuple center, t_tuple axis, double radius,
		double height)
{
	double	lower_end;
	double	upper_end;

	lower_end = center.y - height / 2;
	upper_end = center.y + height / 2;
	return ((t_cylinder){center, axis, radius, height, lower_end, upper_end,
		material()});
}

t_intersections	*intersect_cap(t_cylinder *cyl, t_ray ray)
{
	t_intersections	*xs;
	double			t;

	if (is_equal_d(ray.direction.y, 0))
		return (NULL);
	xs = new_intersections();
	if (!xs)
		return (NULL);
	// check upper bound
	t = (cyl->upper_end - ray.origin.y) / ray.direction.y;
	if (check_cap(*cyl, ray, t) == 1)
		append_intrsection(xs, new_intersection(t, cyl));
	// check lower bound
	t = (cyl->lower_end - ray.origin.y) / ray.direction.y;
	if (check_cap(*cyl, ray, t) == 1)
		append_intrsection(xs, new_intersection(t, cyl));
	if (xs->count == 0)
	{
		free(xs);
		xs = NULL;
	}
	return (xs);
}

static t_intersections	*calc_cylinder_intersections(double t0, double t1,
		t_ray ray, t_cylinder *cyl)
{
	t_intersections	*xs;
	double			y0;
	double			y1;

	xs = new_intersections();
	if (!xs)
		return (NULL);
	if (t0 > t1)
		ft_swap(&t0, &t1);
	y0 = ray.origin.y + t0 * ray.direction.y;
	if (y0 > cyl->lower_end && y0 < cyl->upper_end)
		append_intrsection(xs, new_intersection(t0, cyl));
	y1 = ray.origin.y + t1 * ray.direction.y;
	if (y1 > cyl->lower_end && y1 < cyl->upper_end)
		append_intrsection(xs, new_intersection(t1, cyl));
	return (xs);
}

t_intersections	*intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	double			origin_x;
	double			origin_z;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_intersections	*xs;

	origin_x = ray.origin.x - cyl->center.x;
	origin_z = ray.origin.z - cyl->center.z;
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z
			* ray.direction.z);
	if (is_equal_d(a, 0))
		return (NULL);
	b = 2 * (origin_x * ray.direction.x) + 2 * (origin_z * ray.direction.z);
	c = (origin_x * origin_x) + (origin_z * origin_z) - (cyl->radius
			* cyl->radius);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (NULL);
	xs = new_intersections();
	merge_intersections(xs, calc_cylinder_intersections((-b
				- sqrt(discriminant)) / (2 * a), (-b + sqrt(discriminant)) / (2
				* a), ray, cyl));
	merge_intersections(xs, intersect_cap(cyl, ray));
	return (xs);
}
