/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 15:31:53 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/09 16:36:49 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	point_light(t_tuple position, float brightness, t_color color)
{
	return ((t_light){position, brightness, color});
}

void	set_amb_diff_black(t_color *amb_diff_spect)
{
	amb_diff_spect[1] = new_color(0, 0, 0);
	amb_diff_spect[2] = new_color(0, 0, 0);
}

//  Phong model
t_color	lighting(t_material material, t_light light, t_tuple point,
		t_tuple eyev, t_tuple normal)
{
	t_color	effective_color;
	t_tuple	lightv;
	t_color	amb_diff_spect[3];
	t_tuple	reflectv;
	t_color	light_intensity;

	light_intensity = scale_color(light.color, light.brightness);
	effective_color = mult_color(material.color, light_intensity);
	lightv = normalize_vector(sub_tuples(light.pos, point));
	amb_diff_spect[0] = scale_color(effective_color, material.ambient);
	if (dot_product(lightv, normal) < 0)
		set_amb_diff_black(amb_diff_spect);
	else
	{
		amb_diff_spect[1] = scale_color(scale_color(effective_color,
					material.diffuse), dot_product(lightv, normal));
		reflectv = reflect(negate_tuple(lightv), normal);
		if (dot_product(reflectv, eyev) <= 0)
			amb_diff_spect[2] = new_color(0, 0, 0);
		else
		{
			amb_diff_spect[2] = scale_color(scale_color(light_intensity,
						material.specular), pow(dot_product(reflectv, eyev),
						material.shininess));
		}
	}
	return (add_colors(add_colors(amb_diff_spect[0], amb_diff_spect[1]),
			amb_diff_spect[2]));
}
