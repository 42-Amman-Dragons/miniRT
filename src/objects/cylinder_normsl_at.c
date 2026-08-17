/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normsl_at.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:17:34 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/17 10:58:28 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple cyl_normal_at(t_cylinder cyl, t_tuple point)
{
    double distance;

    distance = (point.x- cyl.center.x) * (point.x- cyl.center.x) + (point.z - cyl.center.z) * (point.z - cyl.center.z);
    if(distance <= cyl.radius * cyl.radius)
    {
        if(point.y >= cyl.upper_end - EPSILON)
            return(cyl.axis);
        else if(point.y <= cyl.lower_end + EPSILON)
            return(new_vector(cyl.axis.x, -cyl.axis.y, cyl.axis.z));
    }
    return(normalize_vector(new_vector(point.x - cyl.center.x, 0, point.z - cyl.center.z)));
}