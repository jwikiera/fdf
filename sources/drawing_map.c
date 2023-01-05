/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_y(t_fdf *fdf, t_vec3d	***proj_map)
{
	t_vec3d	*previous_pt;
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map_struct->size_x)
	{
		previous_pt = NULL;
		j = 0;
		while (j < fdf->map_struct->size_y)
		{
			if (proj_map[i][j] && previous_pt)
				connect_vects(fdf, previous_pt, proj_map[i][j], 0x00000000);
			previous_pt = proj_map[i][j];
			j ++;
		}
		i ++;
	}
}

void	draw_x(t_fdf *fdf, t_vec3d	***proj_map)
{
	t_vec3d	*previous_pt;
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map_struct->size_y)
	{
		previous_pt = NULL;
		j = 0;
		while (j < fdf->map_struct->size_x)
		{
			if (proj_map[j][i] && previous_pt)
				connect_vects(fdf, previous_pt, proj_map[j][i], 0x00000000);
			previous_pt = proj_map[j][i];
			j ++;
		}
		i ++;
	}
}

void	adapt_size_ortho(t_fdf *fdf)
{
	fdf->map_struct->rect_size = ft_max_int(
			ft_min_int((fdf->screen_info->height - 600)
				/ fdf->map_struct->size_x, (fdf->screen_info->width - 600)
				/ fdf->map_struct->size_y), 1);
	if (fdf->screen_info->projection == orthogonal)
		fdf->map_struct->rect_size = ft_max_int(
				1, fdf->map_struct->rect_size
				- fdf->screen_info->pos_z);
	fdf->map_struct->pos_x = fdf->screen_info->width / 2
		- fdf->map_struct->size_y * fdf->map_struct->rect_size
		/ 2 + fdf->screen_info->pos_x;
	fdf->map_struct->pos_y = fdf->screen_info->height / 2
		- fdf->map_struct->size_x * fdf->map_struct->rect_size
		/ 2 + fdf->screen_info->pos_y;
	fdf->map_struct->pos_z = fdf->screen_info->screen_depth + 150;
}

void	draw_map(t_fdf *fdf)
{
	t_vec3d	*rotation_center_prev;
	t_vec3d	***proj_map;

	adapt_size_ortho(fdf);
	fill_screen(fdf, fdf->screen_info->background_color);
	rotation_center_prev = new_vect3d(fdf->screen_info->rotation_center->x,
			fdf->screen_info->rotation_center->y,
			fdf->screen_info->rotation_center->z);
	free(fdf->screen_info->rotation_center);
	fdf->screen_info->rotation_center = new_vect3d(fdf->map_struct->pos_x
			+ fdf->map_struct->size_y * fdf->map_struct->rect_size / 2.0
			- fdf->map_struct->rect_size / 2.0, (float)fdf->map_struct->pos_y
			+ (float)fdf->map_struct->size_x * (float)fdf->map_struct->rect_size
			/ 2.0 - fdf->map_struct->rect_size / 2.0, fdf->map_struct->pos_z
			+ fdf->screen_info->pos_z);
	proj_map = get_proj_map(fdf);
	if (!proj_map)
		return ;
	draw_x(fdf, proj_map);
	draw_y(fdf, proj_map);
	free_proj_map(proj_map, fdf->map_struct->size_x, fdf->map_struct->size_y,
		fdf->map_struct->size_y);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->mlx_data->img, 0, 0);
	free(fdf->screen_info->rotation_center);
	fdf->screen_info->rotation_center = rotation_center_prev;
}
