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
void	draw_line_dda(t_fdf *fdf, const int coords[4], int color)
{
	int		steps;
	float	pos[2];
	float	incs[2];
	int		i;

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
		my_mlx_pixel_put(fdf, pos[0], pos[1], color);
		pos[0] += incs[0];
		pos[1] += incs[1];
		i ++;
	}
}

int	get_color_for_step(int step, int steps, int color1, int color2)
{
	float	color_steps[4];

	color_steps[0] = (float)ft_abs_int(get_a(color1)
			- get_a(color2)) / (float)steps;
	color_steps[1] = (float)ft_abs_int(get_r(color1)
			- get_r(color2)) / (float)steps;
	color_steps[2] = (float)ft_abs_int(get_g(color1)
			- get_g(color2)) / (float)steps;
	color_steps[3] = (float)ft_abs_int(get_b(color1)
			- get_b(color2)) / (float)steps;
	return (argb_to_int(color_steps[0] * step,
			color_steps[0] * step,
			color_steps[0] * step,
			color_steps[0] * step));
}

void	draw_line_dda_colors(t_fdf *fdf, const int coords[4], int colors[2])
{
	int		steps;
	float	pos[2];
	float	incs[2];
	int		i;

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
		my_mlx_pixel_put(fdf, pos[0], pos[1],
			get_color_for_step(i, steps, colors[0], colors[1]));
		pos[0] += incs[0];
		pos[1] += incs[1];
		i ++;
	}
}
