/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 11:35:44 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/09/08 15:30:44 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_amb_diff_black(t_color *amb_diff_spect)
{
	amb_diff_spect[1] = new_color(0, 0, 0);
	amb_diff_spect[2] = new_color(0, 0, 0);
}

/*
	ambient is the porthin of the light the affects the opject in a way
	that is colored the same over the entire surface of the object.
	ambient light is not affected by the angle of the light or the position
	of the object. It is a constant light that is present in the scene.
*/
void	handle_ambient(t_color *amb_diff_spect, t_material material,
		t_ambient ambient)
{
	amb_diff_spect[0] = scale_color(mult_color(material.color, ambient.color),
			ambient.ratio);
}

/*
	Diffuse lighting is the light reflection that depends on the 
	angle ebetween the light source and the surface normal.
	it is appears brighter when the light source is directly facing
	 the surface and darker when the light source is at an angle.
	cos theta > 90 degrees, the light is not visible on the surface.
*/
void	handle_diffuse(t_color *amb_diff_spect, t_material material,
		t_color effective_color, t_calculations calc)
{
	amb_diff_spect[1] = scale_color(scale_color(effective_color,
				material.diffuse), dot_product(calc.lightv, calc.normal));
}

/*
	Spectular reflection: it is the spot of light appearing on the 
	surface of an object when the light source is reflected directly 
	into the viewer's eye.
	it depend on the angle between the light source and the viewer's eye.
	cos theta > 90 degrees between the reflected light and the viewer's eye,
		the specular light is not visible on the surface.
*/
void	handle_specular(t_color *amb_diff_spect, t_material material,
		t_color light_intensity, t_calculations calc)
{
	calc.reflectv = reflect(negate_tuple(calc.lightv), calc.normal);
	if (dot_product(calc.reflectv, calc.eyev) <= 0)
		amb_diff_spect[2] = new_color(0, 0, 0);
	else
	{
		amb_diff_spect[2] = scale_color(scale_color(light_intensity,
					material.specular), pow(dot_product(calc.reflectv,
						calc.eyev), material.shininess));
	}
}
