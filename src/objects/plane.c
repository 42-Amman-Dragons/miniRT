/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 10:17:35 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/10 10:48:36 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane new_plane(t_tuple point, t_tuple normal, t_color color)
{
    t_material m;
    
    m = material();
    m.color = color;
    return ((t_plane){point, normal, m});
}

/*
    derived from equations:
    1) (p - a) . n = 0  since p and a are points in the plane so the resulting vector will be prependicular on the normal
    2) p(t) = p0 + tv   The ray equation

    (p0 + tv - a).n = 0
    ...
    ...
    t = -((p0 - a).n) / v.n
*/
t_intersections *intersect_plane(t_plane plane, t_ray ray)
{
    double t;
    t_intersection intersection;
    t_intersections * xs;
    // If the ray was paralel to the plane no intersections.
    if(dot_product(ray.direction, plane.normal) == 0)
        return (NULL);
    t = (-1 * dot_product(sub_tuples(ray.origin, plane.point), plane.normal))
        / dot_product(ray.direction, plane.normal);
    intersection = new_intersection(t, &plane);   
    xs = new_intersections();
    if(!xs)
        return (NULL);
    append_intrsection(xs, intersection);
    return(xs);
}