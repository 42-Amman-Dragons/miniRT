/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 00:00:00 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/09 00:00:00 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*hit(t_intersections *intersections)
{
	int	i;

	if (!intersections || !intersections->items)
		return (NULL);
	i = 0;
	while (i < intersections->count)
	{
		if (intersections->items[i].t >= 0.0)
			return (&intersections->items[i]);
		i++;
	}
	return (NULL);
}
