/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:05 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:06 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_scaling(double x, double y, double z)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][0] = x;
    result->data[1][1] = y;
    result->data[2][2] = z;

    return (result);
}