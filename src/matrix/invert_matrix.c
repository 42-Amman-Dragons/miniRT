/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:53:49 by hal-lawa          #+#    #+#             */
/*   Updated: 2026/08/02 12:53:50 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float calc_det(t_matrix m)
{
    float det;
    int i;
    
    det = 0;
    i = 0;
    if(m.row != m.col)
        return (0);
    if (m.col == 2)
        return( (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]));
    else
    {
        while(i < m.col)
        {
            // printf("value at 0,%i: %f\n", i,  m.data[0][i]);
            // printf("cofactor at 0,%i: %f\n", i,  cofactor(m, 0, i));
            det = det + (m.data[0][i] * cofactor(m, 0, i));
            // printf("det is %f\n", det);
            i++;
        }
    }
    return (det);
}

t_matrix *submatrix(t_matrix m, int row, int col)
{
    int i;
    int c;
    int r;
    float data[(m.row - 1)*(m.col -1)];

    if(row >= m.row || col >= m.col)
        return (NULL);
    i = 0;
    c = 0;
    r = 0;
    while(r < m.row)
    {
        c = 0;
        while(c < m.col)
        {
            if(r != row && c != col)
            {
                data[i] = m.data[r][c];
                i++;
            }
            c++;
        }
        r++;
    }
    return (new_matrix(data, m.col - 1, m.row - 1));
}


float minor(t_matrix m, int row, int col)
{
    t_matrix *sub;
    float det;

    sub = submatrix(m, row, col);
    if(!sub)
        return (0);
    det = calc_det(*sub);
    free_matrix(sub);
    return(det);
}

float cofactor(t_matrix m, int row, int col)
{
    float min;

    min = minor(m, row, col);
    if((row + col) % 2 != 0 && !is_equal_f(min, 0))
        min = -1 * min;
    return (min);
}

t_matrix *invert_matrix(t_matrix m)
{
    t_matrix *mat1;
    t_matrix *mat2;

    mat1 = create_cofactor_matrix(m);
    if(!mat1)
        return (NULL);
    mat2 = create_transpose(mat1);
    free_matrix(mat1);
    mat1 = NULL;
    if(!mat2)
        return(NULL);
    mat1 = divide_matrix_by(*mat2, calc_det(m));
    free_matrix(mat2);
    mat2 = NULL;
    if(!mat1)
        return (NULL);
    return (mat1);
}


