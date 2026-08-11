/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:19:14 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/11 16:19:26 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_cap(t_cylinder cyl, t_ray ray, double t)
{
    double x;
    double z;

    x = ray.origin.x + t * ray.direction.x;
    z = ray.origin.z + t * ray.direction.z;
    return(x * x + z * z <= cyl.radius);
}