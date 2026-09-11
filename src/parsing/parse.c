/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuqare <mabuqare@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:10 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/01 15:22:10 by mabuqare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <errno.h>

int	has_rt_extension(char *path)
{
	char	*dot;

	dot = ft_strrchr(path, '.');
	if (!dot || dot == path)
		return (0);
	return (ft_strncmp(dot, ".rt", 4) == 0);
}

int	read_scene(int fd, t_scene *scene)
{
	char	*line;
	int		status;

	status = 0;
	errno = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!status && count_words(line) > 0)
			status = parse_line(line, scene);
		free(line);
		errno = 0;
		line = get_next_line(fd);
	}
	if (!status && errno)
		return (rt_error("failed while reading the scene file"));
	return (status);
}

int	check_scene(t_scene *scene)
{
	if (!scene->has_ambient)
		return (rt_error("the scene has no ambient lighting (A)"));
	if (!scene->has_camera)
		return (rt_error("the scene has no camera (C)"));
	if (!scene->has_light)
		return (rt_error("the scene has no light (L)"));
	return (0);
}

int	parse_scene(char *path, t_scene *scene)
{
	int	fd;
	int	status;

	if (!has_rt_extension(path))
		return (rt_error("the scene file must have a .rt extension"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (rt_error("cannot open the scene file"));
	status = read_scene(fd, scene);
	close(fd);
	if (status || check_scene(scene))
	{
		free_objects(&scene->objects);
		return (1);
	}
	return (0);
}
