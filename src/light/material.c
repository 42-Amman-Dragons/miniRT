/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 15:31:15 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/09 15:31:19 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material material()
{
    t_material m;
    m.color = new_color(1,1,1);
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;
    return (m);
}