/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 00:00:00 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/09/08 15:36:02 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_tuple position, t_tuple direction)
{
	return ((t_ray){position, direction});
}

t_tuple	position(t_ray ray, double distance)
{
	t_tuple	pos;

	pos = add_tuples(ray.origin, scale_tuple(ray.direction, distance));
	pos.w = 1.0;
	return (pos);
}
