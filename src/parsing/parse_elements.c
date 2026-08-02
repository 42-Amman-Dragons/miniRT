/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:21:54 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:21:55 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	dispatch(char **tokens, t_scene *scene)
{
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		return (parse_ambient(tokens, scene));
	if (ft_strncmp(tokens[0], "C", 2) == 0)
		return (parse_camera(tokens, scene));
	if (ft_strncmp(tokens[0], "L", 2) == 0)
		return (parse_light(tokens, scene));
	if (ft_strncmp(tokens[0], "sp", 3) == 0)
		return (parse_sphere(tokens, scene));
	if (ft_strncmp(tokens[0], "pl", 3) == 0)
		return (parse_plane(tokens, scene));
	if (ft_strncmp(tokens[0], "cy", 3) == 0)
		return (parse_cylinder(tokens, scene));
	return (rt_error("unknown element identifier in the scene"));
}

int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		status;

	tokens = split_ws(line);
	if (!tokens)
		return (rt_error("out of memory while reading the scene"));
	if (!tokens[0])
		return (free_tokens(tokens), 0);
	status = dispatch(tokens, scene);
	free_tokens(tokens);
	return (status);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	if (count_tokens(tokens) != 3)
		return (rt_error("A takes a ratio and a colour"));
	if (scene->has_ambient)
		return (rt_error("duplicate ambient lighting (A)"));
	if (parse_range(tokens[1], &scene->ambient.ratio, 0.0, 1.0))
		return (rt_error("the ambient ratio must be in [0.0,1.0]"));
	if (parse_color(tokens[2], &scene->ambient.color))
		return (rt_error("the ambient colour must be R,G,B in [0,255]"));
	scene->has_ambient = 1;
	return (0);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	if (count_tokens(tokens) != 4)
		return (rt_error("C takes a position, an orientation and a FOV"));
	if (scene->has_camera)
		return (rt_error("duplicate camera (C)"));
	if (parse_point(tokens[1], &scene->camera.origin))
		return (rt_error("the camera position must be x,y,z"));
	if (parse_orientation(tokens[2], &scene->camera.dir))
		return (rt_error("the camera orientation must be a normalised vector"));
	if (parse_range(tokens[3], &scene->camera.fov, 0.0, 180.0))
		return (rt_error("the camera FOV must be in [0,180]"));
	scene->has_camera = 1;
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	if (count_tokens(tokens) != 4)
		return (rt_error("L takes a position, a brightness and a colour"));
	if (scene->has_light)
		return (rt_error("duplicate light (L)"));
	if (parse_point(tokens[1], &scene->light.pos))
		return (rt_error("the light position must be x,y,z"));
	if (parse_range(tokens[2], &scene->light.brightness, 0.0, 1.0))
		return (rt_error("the light brightness must be in [0.0,1.0]"));
	if (parse_color(tokens[3], &scene->light.color))
		return (rt_error("the light colour must be R,G,B in [0,255]"));
	scene->has_light = 1;
	return (0);
}
