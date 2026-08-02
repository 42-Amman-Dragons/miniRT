/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:28 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:29 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple add_tuples(t_tuple t1, t_tuple t2)
{
    if(t1.w == 1 && t2.w == 1)
    {
        print_error_return("Cannot add two points together", 1);
        return (t_tuple){0,0,0,0};
    }
    return ((t_tuple){
        t1.x + t2.x,
        t1.y + t2.y,
        t1.z + t2.z,
        t1.w + t2.w
    });
}

t_tuple sub_tuples(t_tuple t1, t_tuple t2)
{
    if(t1.w - t2.w < 0)
    {
        print_error_return("Negative wight\n", 1);
        return (t_tuple){0,0,0,0};
    }
    return ((t_tuple){
        t1.x - t2.x,
        t1.y - t2.y,
        t1.z - t2.z,
        t1.w - t2.w
    });
}

t_tuple negate_tuple(t_tuple t)
{
    return ((t_tuple){
        0 - t.x,
        0 - t.y,
        0 - t.z,
        0 - t.w
    });
}

t_tuple scale_tuple(t_tuple t, double scalar)
{
    return ((t_tuple){
        t.x * scalar,
        t.y * scalar,
        t.z * scalar,
        t.w * scalar
    });
}

t_tuple divide_tuple(t_tuple t, double num)
{
    return ((t_tuple){
        t.x / num,
        t.y / num,
        t.z / num,
        t.w / num
    });
}
