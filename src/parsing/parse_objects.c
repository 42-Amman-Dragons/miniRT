/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:22:05 by mabuqare          #+#    #+#             */
/*   Updated: 2026/08/17 10:30:42 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	obj;
	double		diameter;

	if (count_tokens(tokens) != 4)
		return (rt_error("sp takes a centre, a diameter and a colour"));
	if (parse_point(tokens[1], &obj.shape.sphere.center))
		return (rt_error("the sphere centre must be x,y,z"));
	if (parse_positive(tokens[2], &diameter))
		return (rt_error("the sphere diameter must be a positive number"));
	if (parse_color(tokens[3], &obj.color))
		return (rt_error("the sphere colour must be R,G,B in [0,255]"));
	obj.shape.sphere.radius = diameter / 2.0;
	obj.type = OBJ_SPHERE;
	if (append_object(&scene->objects, &obj))
		return (rt_error("out of memory while reading the scene"));
	return (0);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	obj;

	if (count_tokens(tokens) != 4)
		return (rt_error("pl takes a point, a normal and a colour"));
	if (parse_point(tokens[1], &obj.shape.plane.point))
		return (rt_error("the plane point must be x,y,z"));
	if (parse_orientation(tokens[2], &obj.shape.plane.normal))
		return (rt_error("the plane normal must be a normalised vector"));
	if (parse_color(tokens[3], &obj.color))
		return (rt_error("the plane colour must be R,G,B in [0,255]"));
	obj.type = OBJ_PLANE;
	if (append_object(&scene->objects, &obj))
		return (rt_error("out of memory while reading the scene"));
	return (0);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	obj;
	double		diameter;

	if (count_tokens(tokens) != 6)
		return (rt_error("cy takes centre, axis, diameter, height and colour"));
	if (parse_point(tokens[1], &obj.shape.cylinder.center))
		return (rt_error("the cylinder centre must be x,y,z"));
	if (parse_orientation(tokens[2], &obj.shape.cylinder.axis))
		return (rt_error("the cylinder axis must be a normalised vector"));
	if (parse_positive(tokens[3], &diameter))
		return (rt_error("the cylinder diameter must be a positive number"));
	if (parse_positive(tokens[4], &obj.shape.cylinder.height))
		return (rt_error("the cylinder height must be a positive number"));
	if (parse_color(tokens[5], &obj.color))
		return (rt_error("the cylinder colour must be R,G,B in [0,255]"));
	obj.shape.cylinder = new_cylinder(obj.shape.cylinder.center, obj.shape.cylinder.axis, diameter/2, obj.shape.cylinder.height);
	obj.type = OBJ_CYLINDER;
	if (append_object(&scene->objects, &obj))
		return (rt_error("out of memory while reading the scene"));
	return (0);
}
