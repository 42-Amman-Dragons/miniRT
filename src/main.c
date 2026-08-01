/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:22 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:22 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
	{
		write(2, "Error\nusage: ./miniRT <scene.rt>\n", 33);
		return (1);
	}
	rt.scene.objects = NULL;
	rt.scene.has_ambient = 0;
	rt.scene.has_camera = 0;
	rt.scene.has_light = 0;
	if (parse_scene(argv[1], &rt.scene))
		return (1);
	if (init_mlx(&rt))
	{
		cleanup_rt(&rt);
		write(2, "Error\nmlx initialisation failed\n", 32);
		return (1);
	}
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img, 0, 0);
	mlx_loop(rt.mlx);
	return (0);
}
