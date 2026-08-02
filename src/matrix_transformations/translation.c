/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:11 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:12 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_translation(float x, float y, float z)
{
    t_matrix *result;

    result = create_identity(4);
    if(!result)
        return (NULL);
    result->data[0][3] = x;
    result->data[1][3] = y;
    result->data[2][3] = z;

    return (result);
}