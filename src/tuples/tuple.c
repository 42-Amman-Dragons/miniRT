/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:33 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:34 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple new_tuple(float x, float y, float z, float w)
{
    return ((t_tuple){x,y,z,w});
}

t_tuple new_point(float x, float y, float z)
{
        return ((t_tuple){x,y,z,1});
}

t_tuple new_vector(float x, float y, float z)
{
        return ((t_tuple){x,y,z,0});
}

