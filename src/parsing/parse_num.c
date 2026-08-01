/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:02 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:03 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_int(char *s, int *out)
{
	long	value;
	long	sign;
	int		i;

	value = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (1);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		value = value * 10 + (s[i++] - '0');
		if (value > 2147483647)
			return (1);
	}
	*out = (int)(value * sign);
	return (0);
}

static int	parse_fraction(char *s, int *i, double *value)
{
	double	div;

	div = 1.0;
	if (s[*i] != '.')
		return (0);
	(*i)++;
	if (!ft_isdigit(s[*i]))
		return (1);
	while (ft_isdigit(s[*i]))
	{
		*value = *value * 10.0 + (s[(*i)++] - '0');
		div *= 10.0;
	}
	*value /= div;
	return (0);
}

int	parse_double(char *s, double *out)
{
	double	value;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	value = 0.0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(s[i]))
		return (1);
	while (ft_isdigit(s[i]))
		value = value * 10.0 + (s[i++] - '0');
	if (parse_fraction(s, &i, &value))
		return (1);
	if (s[i])
		return (1);
	*out = value * sign;
	return (0);
}
