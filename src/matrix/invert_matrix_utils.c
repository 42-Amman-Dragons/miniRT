/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_matrix_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:46 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:47 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_cofactor_matrix(t_matrix m)
{ 
    t_matrix *result;
    int i;
    int j;

    result = create_empty_matrix(m.col, m.row);
    if(!result)
        return (NULL);
    i = 0;
    j = 0;
    while (i < m.row)
    {
        j = 0;
        while (j < m.col)
        {
            result->data[i][j] = cofactor(m,  i , j);
            j++;
        }
        i++;
    }
    return (result);
}

t_matrix *divide_matrix_by(t_matrix m, float num)
{
    t_matrix *result;
    int i;
    int j;

    result = create_empty_matrix(m.col, m.row);
    if(!result)
        return (NULL);
    i = 0;
    j = 0;
    while (i < m.row)
    {
        j = 0;
        while (j < m.col)
        {
            result->data[i][j] = m.data[i][j] / num;
            j++;
        }
        i++;
    }
    return (result);
}