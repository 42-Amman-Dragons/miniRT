/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_basic_calc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 11:24:19 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/23 11:25:17 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_calculations prepare_basic_calc(t_tuple point ,t_tuple eyev, t_tuple normal)
{
    t_calculations calc;

    calc.point = point;
    calc.eyev = eyev;
    calc.normal = normal;
    return (calc);
}