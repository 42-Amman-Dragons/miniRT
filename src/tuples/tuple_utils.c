/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:54:30 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:54:31 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int is_equal_d(double a, double b)
{
    if(fabs(a - b) < EPSILON)
        return(1);
    else 
        return(0);    
}