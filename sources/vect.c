/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vect(t_fdf *fdf, t_vec3d *vect, int color)
{
	const int	circle_data[3] = {vect->x, vect->y, 5};

	circle_bres(fdf, circle_data, color);
}

void	connect_vects(t_fdf *fdf, t_vec3d *v1, t_vec3d *v2, int color)
{
	const int	line_coords[4] = {v1->x, v1->y, v2->x, v2->y};

	draw_line_dda(fdf, line_coords, color);
}

void	connect_vects_color(t_fdf *fdf, t_vec3d *v1, t_vec3d *v2, int colors[2])
{
	const int	line_coords[4] = {v1->x, v1->y, v2->x, v2->y};

	draw_line_dda_colors(fdf, line_coords, colors);
}
