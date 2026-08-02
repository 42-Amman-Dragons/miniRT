/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:07 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:07 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

void	free_objects(t_object **head)
{
	t_object	*next;

	while (*head)
	{
		next = (*head)->next;
		free(*head);
		*head = next;
	}
}

int	append_object(t_object **head, t_object *obj)
{
	t_object	*node;
	t_object	*cur;

	node = malloc(sizeof(t_object));
	if (!node)
		return (1);
	*node = *obj;
	node->next = NULL;
	if (!*head)
		return (*head = node, 0);
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	return (0);
}
