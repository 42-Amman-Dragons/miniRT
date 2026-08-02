/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:02 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:03 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *rotation_x(double radians)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[1][1] = cos(radians);
    result->data[2][2] = cos(radians);
    result->data[2][1] = sin(radians);
    result->data[1][2] = -sin(radians);

    return (result);
}

t_matrix *rotation_y(double radians)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][0] = cos(radians);
    result->data[0][2] = sin(radians);
    result->data[2][0] = -sin(radians);
    result->data[2][2] = cos(radians);

    return (result);
}

t_matrix *rotation_z(double radians)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][0] = cos(radians);
    result->data[0][1] = -sin(radians);
    result->data[1][0] = sin(radians);
    result->data[1][1] = cos(radians);

    return (result);
}
