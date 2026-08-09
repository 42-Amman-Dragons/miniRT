/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexils_to_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 02:48:39 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/09 13:42:20 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel_to_image(t_rt *rt, int x, int y, t_color color)
{
	char			*pixel;
	unsigned int	rgb;
	int				bytes;

	if (!rt || !rt->addr)
		return ;
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	bytes = rt->bpp / 8;
	if (bytes < 3 || bytes > 4)
		return ;
	pixel = rt->addr + y * rt->line_len + x * bytes;
	rgb = color_to_rgb(color);
	ft_memcpy(pixel, &rgb, bytes);
}


