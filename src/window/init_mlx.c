/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:19 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:20 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_rt *rt)
{
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img = NULL;
	rt->addr = NULL;
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (1);
	rt->win = mlx_new_window(rt->mlx, WIN_W, WIN_H, "miniRT");
	if (!rt->win)
		return (1);
	rt->img = mlx_new_image(rt->mlx, WIN_W, WIN_H);
	if (!rt->img)
		return (1);
	rt->addr = mlx_get_data_addr(rt->img, &rt->bpp, &rt->line_len,
			&rt->endian);
	if (!rt->addr)
		return (1);
	mlx_hook(rt->win, EV_KEYPRESS, MASK_KEYPRESS, on_key, rt);
	mlx_hook(rt->win, EV_DESTROY, 0, on_destroy, rt);
	mlx_hook(rt->win, EV_EXPOSE, MASK_EXPOSE, on_expose, rt);
	return (0);
}

void	cleanup_rt(t_rt *rt)
{
	free_objects(&rt->scene.objects);
	if (rt->img)
		mlx_destroy_image(rt->mlx, rt->img);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	rt->img = NULL;
	rt->win = NULL;
	rt->mlx = NULL;
}

int	close_rt(t_rt *rt)
{
	cleanup_rt(rt);
	exit(0);
}
