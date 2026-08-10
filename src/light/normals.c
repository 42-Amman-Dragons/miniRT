/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 15:17:56 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/10 11:08:39 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	world_normal(t_sphere s, t_tuple point, t_matrix inverse)
{
	t_tuple		obj_p;
	t_tuple		obj_normal;
	t_tuple		world_normal;
	t_matrix	*n;

	obj_p = multi_matrix_tuple(inverse, point);
	obj_normal = sub_tuples(obj_p, s.center);
	n = create_transpose(&inverse);
	world_normal = multi_matrix_tuple(*n, obj_normal);
	free_matrix(n);
	world_normal.w = 0;
	return (world_normal);
}

t_tuple	normal_at(t_sphere s, t_tuple point)
{
	return (normalize_vector(sub_tuples(point, s.center)));
}
