/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 13:13:27 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/10 10:37:02 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	new_intersection(double distance, void *object)
{
	return ((t_intersection){distance, object});
}

t_intersections	*new_intersections(void)
{
	t_intersections	*intersections;

	intersections = ft_calloc(1, sizeof(t_intersections));
	return (intersections);
}

static t_intersection	*insert_sorted_list(t_intersections *intersections,
		t_intersection new)
{
	t_intersection	*updated;
	int				i;

	updated = ft_calloc(intersections->count + 1, sizeof(t_intersection));
	if (!updated)
		return (NULL);
	i = 0;
	while (i < intersections->count && intersections->items[i].t <= new.t)
	{
		updated[i] = intersections->items[i];
		i++;
	}
	updated[i] = new;
	while (i < intersections->count)
	{
		updated[i + 1] = intersections->items[i];
		i++;
	}
	return (updated);
}

void	append_intrsection(t_intersections *intersections, t_intersection new)
{
	t_intersection	*updated;

	if (!intersections)
		return ;
	updated = insert_sorted_list(intersections, new);
	if (!updated)
		return ;
	free(intersections->items);
	intersections->items = updated;
	intersections->count++;
}

void	free_intersections(t_intersections *intersections)
{
	if (!intersections)
		return ;
	free(intersections->items);
	free(intersections);
}

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
