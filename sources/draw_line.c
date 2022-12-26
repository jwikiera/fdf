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

void	draw_one(t_data *data, const int coords[4], int color)
{
	double	a;
	double	b;
	int 	i;
	int 	printed_y;

	a = ft_abs_float(((float)coords[1] - (float)coords[3]) / ((float)coords[0] - (float)coords[2]));
	if (coords[3] < coords[1])
		a *= -1;
	int smallest_y;
	if (coords[0] < coords[2])
		smallest_y = coords[1];
	else
	{
		a *= -1;
		smallest_y = coords[3];
	}
	b = smallest_y - a * ft_min_double(coords[0], coords[2]);
	i = ft_min_double(coords[0], coords[2]);
	while (i < ft_max_double(coords[0], coords[2]))
	{
		printed_y = a * (double)i + b;
		my_mlx_pixel_put(data, i, printed_y, color);
		i ++;
	}
}

void	draw_two(t_data *data, const int coords[4], int color, double a)
{
	double	b;
	int 	i;
	int 	printed_y;
	int		smallest_x;

	if (coords[2] < coords[0])
		a *= -1;
	if (coords[1] < coords[3])
		smallest_x = coords[0];
	else
		smallest_x = coords[2];
	b = smallest_x - a * ft_min_double(coords[1], coords[3]);
	//printf("b: %f\n", b);
	i = ft_min_float(coords[1], coords[3]);
	while (i < ft_max_double(coords[1], coords[3]))
	{
		printed_y = a * (double)i + b;
		my_mlx_pixel_put(data, printed_y, i, color);
		i ++;
	}
}

/*
  my_mlx_pixel_put(data, coords[0], coords[1], 0x0000FF00);
	my_mlx_pixel_put(data, coords[2], coords[3], 0x0000FF00);
*/
void	draw_line(t_data *data, const int coords[4], int color)
{
	/*double	a;

	a = ft_abs_double(((float)coords[0] - (float)coords[2]) / ((float)coords[1] - (float)coords[3]));
	if (a > 1)
		draw_one(data, coords, color);
	else
		draw_two(data, coords, color, a);*/

	double	a;
	double	b;
	int 	i;
	int 	printed_y;

	a = ((float)(coords[3] - coords[1])) / (float)(coords[2] - coords[0]);
	b = coords[1] - a * coords[0];

	if (a < 1)
	{
		i = ft_min_int(coords[0], coords[2]);
		while (i < ft_max_int(coords[0], coords[2]))
		{
			printed_y = a * (double)i + b;
			my_mlx_pixel_put(data, i, printed_y, color);
			i ++;
		}
	}
	else
	{
		a = 1 / a; //a = ((float)(coords[2] - coords[0])) / (float)(coords[3] - coords[1]);
		b = coords[0] - a * coords[1];
		i = ft_min_int(coords[1], coords[3]);
		while (i < ft_max_int(coords[1], coords[3]))
		{
			printed_y = a * (double)i + b;
			my_mlx_pixel_put(data, printed_y, i, color);
			i ++;
		}
	}

	//my_mlx_pixel_put(data, coords[0], coords[1], 0x000000FF);
	//my_mlx_pixel_put(data, coords[2], coords[3], 0x000000FF);
	/*int cd1[] = {coords[0], coords[1], 5};
	circle_bres(data, cd1, 0x000000FF);
	int cd2[] = {coords[2], coords[3], 5};
	circle_bres(data, cd2, color);*/
}