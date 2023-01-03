/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_bresenham.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Algorithm and implementation source:
 * https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
 */
void	draw_circle(t_fdf *fdf, const int coords[4], int color)
{
	my_mlx_pixel_put(fdf, coords[0] + coords[2], coords[1] + coords[3], color);
	my_mlx_pixel_put(fdf, coords[0] - coords[2], coords[1] + coords[3], color);
	my_mlx_pixel_put(fdf, coords[0] + coords[2], coords[1] - coords[3], color);
	my_mlx_pixel_put(fdf, coords[0] - coords[2], coords[1] - coords[3], color);
	my_mlx_pixel_put(fdf, coords[0] + coords[3], coords[1] + coords[2], color);
	my_mlx_pixel_put(fdf, coords[0] - coords[3], coords[1] + coords[2], color);
	my_mlx_pixel_put(fdf, coords[0] + coords[3], coords[1] - coords[2], color);
	my_mlx_pixel_put(fdf, coords[0] - coords[3], coords[1] - coords[2], color);
}

void	set_y_d(int *y, int *d, int valy, int vald)
{
	*y = valy;
	*d = vald;
}

/* details: x, y, radius */
void	circle_bres(t_fdf *fdf, const int circle_details[3], int color)
{
	int	x;
	int	y;
	int	d;
	int	coords[4];

	x = 0;
	set_y_d(&y, &d, circle_details[2], 3 - 2 * circle_details[2]);
	coords[0] = circle_details[0];
	coords[1] = circle_details[1];
	coords[2] = x;
	coords[3] = y;
	draw_circle(fdf, coords, color);
	while (y >= x)
	{
		x ++;
		if (d > 0)
			set_y_d(&y, &d, y - 1, d + 4 * (x - y) + 10);
		else
			d = d + 4 * x + 6;
		coords[2] = x;
		coords[3] = y;
		draw_circle(fdf, coords, color);
	}
}
