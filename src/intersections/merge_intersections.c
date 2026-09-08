/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:25:49 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/09/08 15:27:35 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	merge_intersections(t_intersections *result, t_intersections *temp)
{
	t_intersection	intersection;
	int				i;

	if (!temp)
		return ;
	i = 0;
	while (i < temp->count)
	{
		intersection = new_intersection(temp->items[i].t,
				temp->items[i].object);
		append_intrsection(result, intersection);
		i++;
	}
	free_intersections(temp);
}
