/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:36 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:37 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double vector_magnitude(t_tuple vector)
{
    if(is_equal_d(vector.w, 1))
    {
        print_error_return("Cannot calculate a magnitude for a point.\n",0);
        return(0);
    }
    return (sqrt(
        pow(vector.x, 2)
        + pow(vector.y, 2)
        + pow(vector.z, 2)
        + pow(vector.w, 2)
    ));
}

t_tuple normalize_vector(t_tuple vector)
{
    double magnituade;

    if(is_equal_d(vector.w, 1))
    {
        print_error_return("Cannot normalize a point.\n",0);
        return((t_tuple){0,0,0,0});
    }     
    magnituade = vector_magnitude(vector);
    return (
        new_tuple(
            vector.x / magnituade,
            vector.y / magnituade,
            vector.z / magnituade,
            vector.w /magnituade
        )
    );
}

double dot_product(t_tuple t1, t_tuple t2)
{
    if(is_equal_d(t1.w, 1) || is_equal_d(t2.w, 1))
    {
        print_error_return("Cannot dot product points.\n",0);
        return (0);
    }    
    return (  
            t1.x * t2.x +
            t1.y * t2.y +
            t1.z * t2.z +
            t1.w * t2.w
    );
}

t_tuple cross_product(t_tuple t1, t_tuple t2)
{
    if(is_equal_d(t1.w, 1) || is_equal_d(t2.w, 1))
    {
        print_error_return("Cannot cross product points.\n",0);
        return((t_tuple){0,0,0,0});
    }    
    return (
        new_vector(
            t1.y * t2.z- t1.z * t2.y,
            t1.z * t2.x- t1.x * t2.z,
            t1.x * t2.y- t1.y * t2.x
        )
    );
}