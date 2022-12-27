/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/* Source: https://www.geeksforgeeks.org/dda-line
 * -generation-algorithm-computer-graphics/ */
void draw_line_dda(t_data *data, const int coords[4], int color)
{
	int		steps;
	float	pos[2];
	float 	incs[2];
	int 	i;
		
	if (ft_abs_int(coords[2] - coords[0]) > ft_abs_int(coords[3] - coords[1]))
		steps = ft_abs_int(coords[2] - coords[0]);
	else
		steps = ft_abs_int(coords[3] - coords[1]);
	incs[0] = (coords[2] - coords[0]) / (float)steps;
	incs[1] = (coords[3] - coords[1]) / (float)steps;
	pos[0] = coords[0];
	pos[1] = coords[1];
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(data, pos[0], pos[1], color);
		pos[0] += incs[0];
		pos[1] += incs[1];
		i ++;
	}
}
