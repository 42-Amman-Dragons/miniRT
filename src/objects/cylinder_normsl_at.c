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

// t_tuple cyl_normal_at(t_cylinder cyl, t_tuple point)
// {
//     t_tuple local_point;
//     t_tuple local_normal;
//     t_matrix *inverse_rotation;

//     inverse_rotation = invert_matrix(*cyl.rotation);
//     local_point = multi_matrix_tuple(*cyl.translation, point);
//     local_point = multi_matrix_tuple(*inverse_rotation, local_point);
//     free_matrix(inverse_rotation);
//     if (local_point.y >= cyl.height / 2.0 - EPSILON
//         && local_point.x * local_point.x + local_point.z * local_point.z
//         <= cyl.radius * cyl.radius)
//         local_normal = new_vector(0, 1, 0);
//     else if (local_point.y <= -cyl.height / 2.0 + EPSILON
//         && local_point.x * local_point.x + local_point.z * local_point.z
//         <= cyl.radius * cyl.radius)
//         local_normal = new_vector(0, -1, 0);
//     else
//         local_normal = normalize_vector(new_vector(local_point.x, 0,
//                     local_point.z));
//     local_normal = multi_matrix_tuple(*cyl.rotation, local_normal);
//     return (normalize_vector(local_normal));
// }

t_tuple cyl_normal_at(t_cylinder cyl, t_tuple point)
{
    t_tuple v;
    t_tuple radial_projection;
    float axial_dist;

    v = sub_tuples(point, cyl.center);
    axial_dist = dot_product(v, cyl.axis);
    radial_projection = sub_tuples(v,
        scale_tuple(cyl.axis, axial_dist));
    if(axial_dist >= cyl.height / 2.0 - EPSILON)
    {
        return (cyl.axis);
    }
    if(axial_dist <= -cyl.height / 2.0 + EPSILON)
    {
        return (negate_tuple(cyl.axis));
    }
    return (normalize_vector(radial_projection));
}