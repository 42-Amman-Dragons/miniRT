/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:43 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:44 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	new_color(double red, double green, double blue)
{
	return ((t_color){red, green, blue});
}

static int	color_byte(double channel)
{
	if (isnan(channel) || channel <= 0.0)
		return (0);
	if (channel >= 1.0)
		return (255);
	return ((int)(channel * 255.0 + 0.5));
}

unsigned int	color_to_rgb(t_color color)
{
	return ((unsigned int)(color_byte(color.r) << 16
		| color_byte(color.g) << 8 | color_byte(color.b)));
}

t_color	rgb_to_color(unsigned int rgb)
{
	return (new_color(((rgb >> 16) & 255U) / 255.0,
			((rgb >> 8) & 255U) / 255.0, (rgb & 255U) / 255.0));
}
