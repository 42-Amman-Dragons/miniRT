/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 00:00:00 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/09 00:00:00 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_tuple position, t_tuple direction)
{
	return ((t_ray){position, direction});
}

t_tuple	position(t_ray ray, double distance)
{
	return (add_tuples(ray.origin,
			scale_tuple(ray.direction, distance)));
}
