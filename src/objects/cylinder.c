/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:13:27 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/17 14:51:22 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// The calculations assumes that the normal is 0,1,0 so a transformation
// should be made to make it match the normal provided by the .rt file
// Notes:
// The normal in the upper cap is not the same as the lower cap they are inverted.
void mult_matrix_self(t_matrix **m1, t_matrix *m2)
{
    t_matrix *temp;
    
    temp = multi_matrix(**m1,*m2);
    if(!temp)
        return;
    free_matrix(*m1);
    free_matrix(m2);
    *m1 = temp;
}

void inv_matrix_self(t_matrix **m)
{
    t_matrix *temp;
    temp = invert_matrix(**m);
    if(!temp)
        return;
    free_matrix(*m);
    *m = temp;
}

t_matrix *create_cyl_transformation(t_cylinder *cyl)
{
    t_tuple         base_v;
    double          theta;
    t_tuple         r_dir;
    t_matrix        *result;

    base_v = new_vector(0, 1, 0);
    theta = acos(dot_product(cyl->axis, base_v));
    r_dir = cross_product(cyl->axis, base_v);
    result = create_identity(4);
    mult_matrix_self(&result, create_translation(-cyl->center.x, -cyl->center.y, -cyl->center.z));
    mult_matrix_self(&result, rotation_x(theta * r_dir.x));
    mult_matrix_self(&result, rotation_y(theta * r_dir.y));
    mult_matrix_self(&result, rotation_z(theta * r_dir.z));
    return(result);
}

t_cylinder	new_cylinder(t_tuple center, t_tuple axis, double radius,
		double height)
{
    t_cylinder  cyl;
    
	cyl.lower_end = center.y - height / 2;
	cyl.upper_end = center.y + height / 2;
    cyl.center = center;
    cyl.axis = axis;
    cyl.radius = radius;
    cyl.height = height;
    cyl.trans = create_cyl_transformation(&cyl);
	return (cyl);
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
	double			a;
	double			b;
	double			c;
	double			discriminant;
    t_matrix        *transform;
	t_intersections	*xs;

    transform = invert_matrix(*(cyl->trans));
    ray = transform_ray(ray, *transform);
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z
			* ray.direction.z);
	if (is_equal_d(a, 0))
		return (NULL);
	b = 2 * (ray.origin.x * ray.direction.x) + 2 * (ray.origin.z * ray.direction.z);
	c = (ray.origin.x * ray.origin.x) + (ray.origin.z * ray.origin.z) - (cyl->radius
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
