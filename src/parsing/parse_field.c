/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:00 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:00 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	count_commas(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
		if (s[i++] == ',')
			n++;
	return (n);
}

static char	**split_triplet(char *s)
{
	char	**parts;
	int		n;

	if (count_commas(s) != 2)
		return (NULL);
	parts = ft_split(s, ',');
	if (!parts)
		return (NULL);
	n = 0;
	while (parts[n])
		n++;
	if (n != 3)
		return (free_tokens(parts), NULL);
	return (parts);
}

int	parse_vec3(char *s, t_vec3 *out)
{
	char	**parts;

	parts = split_triplet(s);
	if (!parts)
		return (1);
	if (parse_double(parts[0], &out->x) || parse_double(parts[1], &out->y)
		|| parse_double(parts[2], &out->z))
		return (free_tokens(parts), 1);
	free_tokens(parts);
	return (0);
}

int	parse_color(char *s, t_color *out)
{
	char	**parts;

	parts = split_triplet(s);
	if (!parts)
		return (1);
	if (parse_int(parts[0], &out->r) || parse_int(parts[1], &out->g)
		|| parse_int(parts[2], &out->b))
		return (free_tokens(parts), 1);
	free_tokens(parts);
	if (out->r < 0 || out->r > 255 || out->g < 0 || out->g > 255 || out->b < 0
		|| out->b > 255)
		return (1);
	return (0);
}
