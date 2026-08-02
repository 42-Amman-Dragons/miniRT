/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 12:51:40 by haya              #+#    #+#             */
/*   Updated: 2026/08/02 12:53:30 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_canvas(t_canvas *canvas)
{
    if(!canvas)
        return;
    if(!canvas->pixels)
    {
        free(canvas);
        return;
    }
    free(canvas->pixels);
    free(canvas);
    return;    
}

t_canvas *new_canvas(int width, int height)
{
    t_canvas *canvas;
    int i;

    canvas = ft_calloc(1, sizeof(t_canvas));
    if(!canvas)
        return (NULL);
    i = 0;
    canvas->width = width;
    canvas->height = height;
    canvas->pixels = (t_color *)ft_calloc(width * height , sizeof(t_color));
    if(!canvas->pixels)
        return (NULL);
    while(i < width * height)
    {
        canvas->pixels[i] = new_color(0,0,0);
        i++;
    }
    return (canvas);
}


void write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
    if (!canvas)
        return;
    if ((x < 0 || x >= canvas->width) || (y < 0 || y >= canvas->height))
        return;
    if(!canvas->pixels)
        return;
    canvas->pixels[canvas->width*y + x] = color;
}

t_color get_pixel(t_canvas *canvas, int x, int y)
{
    if (!canvas)
        return (t_color){0, 0, 0};
    if ((x < 0 || x >= canvas->width) || (y < 0 || y >= canvas->height))
        return (t_color){0, 0, 0};
    if(!canvas->pixels)
        return (t_color){0, 0, 0};
    return (canvas->pixels[canvas->width*y + x]);
}