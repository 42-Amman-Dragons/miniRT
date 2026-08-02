/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:55 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:56 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int is_equal_matrix(t_matrix t1, t_matrix t2)
{
    int c;
    int r;
    if(t1.col != t2.col || t1.row != t2.row)
        return (0);
    c = 0;
    r = 0;
    while(r < t1.row)
    {
        while(c < t1.col)
        {
            if(!is_equal_f(t1.data[r][c] ,t2.data[r][c]))
                return (0);
            c++;
        }
        r++;
    }
    return (1);
}


float **mult_data(t_matrix m1, t_matrix m2)
{
    float **data;
    int row;
    int col;
    int i;
    float sum;

    data = create_empty_data(m2.col, m1.row);
    if(!data)
        return(NULL);
    row = 0;
    col = 0;
    while(row < m1.row)
    {
        // printf("row is :%i\n", row);
        col = 0;
        while(col < m2.col)
        {
            // printf("col is :%i\n", col);
            sum = 0;
            i = 0;
            while(i < m1.col)
            {
                // printf("addint the value : %f*%f\n", m1.data[row][i] , m2.data[i][col]);
                sum += m1.data[row][i] * m2.data[i][col];
                i++;
            }
            // printf("sum is : %i\n", sum);
            data[row][col] = sum;
            col++;
        }
        row++;
    }
    return (data);
}

t_matrix *multi_matrix(t_matrix m1, t_matrix m2)
{
    t_matrix *result;

    if(m1.col != m2.row)
    {
        ft_putstr_fd("invalid matrix!", 2);
        return (NULL);
    }
    result = ft_calloc(1, sizeof(t_matrix));
    if(!result)
        return (NULL);
    result->data = mult_data(m1, m2);
    result->row = m1.row;
    result->col = m2.col;
    if(!result->data)
        return (NULL);
    return (result);
}

t_tuple multi_matrix_tuple(t_matrix m, t_tuple t)
{
    t_matrix *n;
    t_matrix *result;
    t_tuple returned_tup;

    if(m.col != 4)
        return ((t_tuple){0,0,0,0});
    n = new_matrix((float[]){t.x, t.y,t.z,t.w}, 1, 4);
    if(!n)
        return ((t_tuple){0,0,0,0});
    result = multi_matrix(m, *n);
    free_matrix(n);
    if(!result)
        return ((t_tuple){0,0,0,0});
    returned_tup = new_tuple(result->data[0][0], result->data[1][0], result->data[2][0], result->data[3][0]);
    free_matrix(result);
    return (returned_tup);
}

