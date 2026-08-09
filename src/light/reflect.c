/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 15:30:50 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/09 15:30:51 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple reflect(t_tuple in, t_tuple normal)
{
    return (sub_tuples(in, scale_tuple(normal, 2* dot_product(in,normal))));
}