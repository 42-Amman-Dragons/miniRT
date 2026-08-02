/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:58 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:59 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_matrix(t_matrix *m)
{
    int i;

    i = 0;
    if(!m)
        return;
    if(!m->data)
    {
        free(m);
        return;
    }
    while(i < m->row)
    {
        if(m->data[i])
        {
            free(m->data[i]);
            m->data[i] = NULL;
        }
        i++;
    }
    free(m->data);
    free(m);
}

double **create_empty_data(int col, int row)
{
    int i; 
    double **data;

    i = 0;
    if(!col || !row)
        return(NULL);
    data = ft_calloc(row , sizeof(double *));
    if(!data)
        return (NULL);
    while(i < row)
    {
        data[i] = ft_calloc(col, sizeof(double));
        if(!data[i])
        {
            while(i > 0)
            {
                i--;
                free(data[i]);
                data[i] = NULL;
            }
            free(data);
            return (NULL);
        }
        i++;
    }
    return (data);
}

double **create_data(double *values, int col, int row)
{
    int i; 
    int y;
    int x;
    double **data;

    data = create_empty_data(col, row);
    if (!data)
        return (NULL);
    i = 0;
    y = 0;
    x = 0;
    while (i < row * col)
    {
        if(i % col == 0 && i != 0)
        {
            y++;
            x = 0;
        }
        data[y][x] = values[i];
        x++;
        i++;
    }
    return (data);
}

t_matrix *new_matrix(double *values, int col, int row)
{
    t_matrix *m;

    m = ft_calloc(1, sizeof(t_matrix));
    m->col = col;
    m->row = row;
    if(!m)
        return (NULL);
    m->data = create_data(values, col, row);
    if(!m->data)
    {
        free(m);
        return (NULL);
    }
    return (m);
}

void print_matrix(t_matrix *m)
{
    int i;
    int j;
    if(!m)
        return;
    i =0;
    j =0;
    while(i< m->row)
    {
        j = 0;
        while(j < m->col)
        {
            printf("%f,", m->data[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}