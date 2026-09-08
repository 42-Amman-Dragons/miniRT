/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 15:10:00 by mabuqare          #+#    #+#             */
/*   Updated: 2026/09/08 16:15:17 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

int	parse_range(char *s, double *out, double lo, double hi)
{
	if (parse_double(s, out))
		return (1);
	if (*out < lo || *out > hi)
		return (1);
	return (0);
}

int	parse_positive(char *s, double *out)
{
	if (parse_double(s, out))
		return (1);
	if (*out <= 0.0)
		return (1);
	return (0);
}

int	parse_point(char *s, t_tuple *out)
{
	if (parse_triplet(s, out))
		return (1);
	out->w = 1;
	return (0);
}

int	parse_orientation(char *s, t_tuple *out)
{
	if (parse_triplet(s, out))
		return (1);
	if (out->x < -1.0 || out->x > 1.0 || out->y < -1.0 || out->y > 1.0
		|| out->z < -1.0 || out->z > 1.0)
		return (1);
	if (is_equal_d(out->x, 0) && is_equal_d(out->y, 0) && is_equal_d(out->z, 0))
		return (1);
	if (!is_equal_d(vector_magnitude(*out), 1.0))
		return (1);
	*out = normalize_vector(*out);
	return (0);
}
