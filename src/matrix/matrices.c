/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:51 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:52 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *create_identity(int num)
{
    int i;
    int j;
    float values[num * num];

    if (num == 0)
        return(NULL);
    i = 0;
    j = 0;
    while(i < num * num)
    {
        if(i == j)
        {
            values[i] = 1;
            j += num + 1;
        }
        else
            values[i] = 0;
        i++;
    }
    return(new_matrix(values, num, num));   
}

t_matrix *create_empty_matrix(int col, int row)
{
    t_matrix *m;

    m = ft_calloc(1 , sizeof(t_matrix));
    if(!m)
        return (NULL);
    m->data = create_empty_data(col, row);
    if(!m->data)
    {
        free(m);
        return (NULL);
    }
    m->col = col;
    m->row = row;
    return (m);
}

t_matrix *create_transpose(t_matrix *m)
{
    int num;
    int i;
    t_matrix *result;

    if(m->col != m->row)
        return (NULL);
    result = create_empty_matrix(m->col, m->row);
    if(!result)
        return (NULL);
    num = 0;
    i = 0;
    while(num < m->row)
    {
        i = 0;
        while (i < m->row)
        {
            result->data[i][num] = m->data[num][i];
            i++;
        }
        num++;
    }
    return(result);
}
