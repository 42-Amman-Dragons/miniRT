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

/*
** The file gives three bare numbers; only the element parser knows whether
** they are a position or a direction, so w is left at 0 for it to set.
*/
int	parse_triplet(char *s, t_tuple *out)
{
	char	**parts;

	parts = split_triplet(s);
	if (!parts)
		return (1);
	if (parse_double(parts[0], &out->x) || parse_double(parts[1], &out->y)
		|| parse_double(parts[2], &out->z))
		return (free_tokens(parts), 1);
	free_tokens(parts);
	out->w = 0;
	return (0);
}

/*
** The scene file states each channel as an integer in [0,255]; the renderer
** works with ratios, so validate the file's form then store it as [0.0,1.0].
*/
static int	parse_channel(char *s, double *out)
{
	int	value;

	if (parse_int(s, &value))
		return (1);
	if (value < 0 || value > 255)
		return (1);
	*out = value / 255.0;
	return (0);
}

int	parse_color(char *s, t_color *out)
{
	char	**parts;

	parts = split_triplet(s);
	if (!parts)
		return (1);
	if (parse_channel(parts[0], &out->r) || parse_channel(parts[1], &out->g)
		|| parse_channel(parts[2], &out->b))
		return (free_tokens(parts), 1);
	free_tokens(parts);
	return (0);
}
