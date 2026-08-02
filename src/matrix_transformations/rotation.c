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

t_matrix *rotation_x(float radians)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[1][1] = cosf(radians);
    result->data[2][2] = cosf(radians);
    result->data[2][1] = sinf(radians);
    result->data[1][2] = -sinf(radians);

    return (result);
}

t_matrix *rotation_y(float radians)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][0] = cosf(radians);
    result->data[0][2] = sinf(radians);
    result->data[2][0] = -sinf(radians);
    result->data[2][2] = cosf(radians);

    return (result);
}

t_matrix *rotation_z(float radians)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][0] = cosf(radians);
    result->data[0][1] = -sinf(radians);
    result->data[1][0] = sinf(radians);
    result->data[1][1] = cosf(radians);

    return (result);
}
