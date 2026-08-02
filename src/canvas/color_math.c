/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:38 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:39 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color add_colors(t_color c1, t_color c2)
{
    return ((t_color){
        c1.r + c2.r,
        c1.g + c2.g,
        c1.b + c2.b
    });
}

t_color sub_colors(t_color c1, t_color c2)
{
    return ((t_color){
        c1.r - c2.r,
        c1.g - c2.g,
        c1.b - c2.b
    });
}

t_color scale_color(t_color c, double scalar)
{
    return ((t_color){
        c.r * scalar,
        c.g * scalar,
        c.b * scalar
    });
}

t_color divide_color(t_color c, double num)
{
    return ((t_color){
        c.r / num,
        c.g / num,
        c.b / num
    });
}

t_color mult_color(t_color c1, t_color c2)
{
    return ((t_color){
        c1.r * c2.r,
        c1.g * c2.g,
        c1.b * c2.b
    });
}