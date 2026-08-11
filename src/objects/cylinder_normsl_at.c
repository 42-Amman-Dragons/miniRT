/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normsl_at.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:17:34 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/11 16:22:03 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple cyl_normal_at(t_cylinder cyl, t_tuple point)
{
    double distance;

    distance = point.x * point.x + point.z * point.z;
    if(distance <= cyl.radius)
    {
        if(point.y <= cyl.upper_end - EPSILON)
            return(cyl.axis);
        else if(point.y >= cyl.lower_end + EPSILON)
            return(new_vector(cyl.axis.x, -cyl.axis.y, cyl.axis.z));
    }
    // @TODO: use a different equation that takes the object transformation instead of this static cyl.
    // this assumes that the y axis is 0.
    return(new_vector(point.x, 0, point.z));
}