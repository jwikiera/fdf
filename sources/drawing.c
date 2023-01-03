/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_screen(t_fdf *fdf, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->screen_info->width)
	{
		j = 0;
		while (j < fdf->screen_info->height)
		{
			my_mlx_pixel_put(fdf, i, j, color);
			j ++;
		}
		i ++;
	}
}

/* square_details: x, y, width, height */
void	draw_square(t_fdf *fdf, const int square_details[4], int color)
{
	const int	line_coords1[4] = {square_details[0], square_details[1],
		square_details[0] + square_details[2], square_details[1]};
	const int	line_coords2[4] = {square_details[0] + square_details[2],
		square_details[1], square_details[0] + square_details[2],
		square_details[1] + square_details[3]};
	const int	line_coords3[4] = {square_details[0] + square_details[2],
		square_details[1] + square_details[3], square_details[0],
		square_details[1] + square_details[3]};
	const int	line_coords4[4] = {square_details[0],
		square_details[1] + square_details[3],
		square_details[0], square_details[1]};

	draw_line_dda(fdf, line_coords1, color);
	draw_line_dda(fdf, line_coords2, color);
	draw_line_dda(fdf, line_coords3, color);
	draw_line_dda(fdf, line_coords4, color);
}
