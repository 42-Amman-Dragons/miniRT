/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:08 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:09 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_shear(double xy, double xz, double yx, double yz, double zx, double zy)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][1] = xy;
    result->data[0][2] = xz;
    result->data[1][0] = yx;
    result->data[1][2] = yz;
    result->data[2][0] = zx;
    result->data[2][1] = zy;

    return (result);
}