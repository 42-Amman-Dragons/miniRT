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
	(void)tokens;
	(void)scene;
	return (0);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	return (0);
}
