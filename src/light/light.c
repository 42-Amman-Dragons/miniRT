/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 15:31:53 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/23 11:49:48 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	point_light(t_tuple position, float brightness, t_color color)
{
	return ((t_light){position, brightness, color});
}


/*  Phong model --> 3 components of light: ambient, diffuse, and specular.
  -------------------------------------------------------
- The (light intensity) represents the light amount and the light color that is emitted from the light source.
- The (effective light) represent how the light color and the oject color interact with each other.
- The (ambient light) exist for every pixel in the sceene.
- The (diffuse and spectular) light is only calculated if the angle 
  between the normal and the light is less than 90 degrees. If the angle is greater than 90 degrees.
*/

t_color	lighting(t_material material, t_light light, t_ambient ambient, t_calculations calc)
{
	t_color	effective_color;
	t_color	amb_diff_spect[3];
	t_color	light_intensity;

	light_intensity = scale_color(light.color, light.brightness);
	effective_color = mult_color(material.color, light_intensity);
	calc.lightv = normalize_vector(sub_tuples(light.pos, calc.point));
	handle_ambient(amb_diff_spect, material, ambient);
	if (dot_product(calc.lightv, calc.normal) < 0)
		set_amb_diff_black(amb_diff_spect);
	else
	{
		handle_diffuse(amb_diff_spect, material, effective_color, calc);
		handle_specular(amb_diff_spect, material, light_intensity, calc);
	}	
	return (add_colors(add_colors(amb_diff_spect[0], amb_diff_spect[1]),
			amb_diff_spect[2]));
}
