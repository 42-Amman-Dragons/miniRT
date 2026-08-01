/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:16 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:17 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	on_key(int keycode, t_rt *rt)
{
	if (keycode == KEY_ESC)
		close_rt(rt);
	return (0);
}

int	on_destroy(t_rt *rt)
{
	close_rt(rt);
	return (0);
}

int	on_expose(t_rt *rt)
{
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	return (0);
}
