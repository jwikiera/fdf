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

void	draw_map(t_fdf *fdf)
{
	fill_screen(fdf, fdf->screen_info->background_color);

	int size = ft_max_int(ft_min_int((fdf->screen_info->height - 600) / fdf->map_struct->size_x, (fdf->screen_info->width - 600) / fdf->map_struct->size_y), 1);
	if (fdf->screen_info->projection == orthogonal)
		size = ft_max_int(1, size - fdf->screen_info->pos_z);
	int base_x = fdf->screen_info->width / 2 - fdf->map_struct->size_y * size / 2 + fdf->screen_info->pos_x;
	int base_y = fdf->screen_info->height / 2 - fdf->map_struct->size_x * size / 2 + fdf->screen_info->pos_y;
	int depth = fdf->screen_info->screen_depth + 100;

	t_vec3d *rotation_center_prev = new_vect3d(fdf->screen_info->rotation_center->x, fdf->screen_info->rotation_center->y, fdf->screen_info->rotation_center->z);
	free(fdf->screen_info->rotation_center);
	fdf->screen_info->rotation_center = new_vect3d(base_x + fdf->map_struct->size_y * size / 2.0 - size / 2.0, (float)base_y + (float)fdf->map_struct->size_x * (float)size / 2.0 - size / 2.0, depth + fdf->screen_info->pos_z);

	t_vec3d *previous_point_y = 0;
	for (int i = 0; i < fdf->map_struct->size_y; i ++) {
		for (int j = 0; j < fdf->map_struct->size_x; j ++) {
			t_vec3d *pt = new_vect3d(base_x + i * size, base_y + j * size, depth - fdf->map_struct->map[j][i] * fdf->map_struct->height_mult + fdf->screen_info->pos_z);
			t_vec3d *pt_rotated = apply_rotation_matrix_to_point(pt, fdf->screen_info);
			if (previous_point_y && fdf->screen_info->projection == orthogonal)
			{
				t_vec3d	*proj1 = project_orthogonal(previous_point_y, fdf->screen_info->screen_plane, fdf->screen_info);
				t_vec3d *proj2 = project_orthogonal(pt, fdf->screen_info->screen_plane, fdf->screen_info);
				if (proj1 && proj2)
					connect_vects(fdf, proj1, proj2, 0x00000000);
				free_vectors(proj1, proj2, 0, 0);
			}
			else if (previous_point_y && fdf->screen_info->projection == perspective)
			{
				t_vec3d	*proj1 = project_perspective(previous_point_y, fdf->screen_info->screen_plane, fdf->screen_info);
				t_vec3d *proj2 = project_perspective(pt, fdf->screen_info->screen_plane, fdf->screen_info);
				if (proj1 && proj2)
					connect_vects(fdf, proj1, proj2, 0x00000000);
				free_vectors(proj1, proj2, 0, 0);
			}
			free(previous_point_y);
			previous_point_y = new_vect3d(pt->x, pt->y, pt->z);
			free(pt);
			free(pt_rotated);
		}
		if (previous_point_y)
			free(previous_point_y);
		previous_point_y = 0;
	}

	t_vec3d *previous_point_x = 0;
	for (int i = 0; i < fdf->map_struct->size_x; ++i) {
		for (int j = 0; j < fdf->map_struct->size_y; ++j) {
			t_vec3d *pt = new_vect3d(base_x + j * size, base_y + i * size, depth - fdf->map_struct->map[i][j] * fdf->map_struct->height_mult + fdf->screen_info->pos_z);
			if (previous_point_x && fdf->screen_info->projection == orthogonal)
			{
				t_vec3d	*proj1 = project_orthogonal(previous_point_x, fdf->screen_info->screen_plane, fdf->screen_info);
				t_vec3d *proj2 = project_orthogonal(pt, fdf->screen_info->screen_plane, fdf->screen_info);
				if (proj1 && proj2)
					connect_vects(fdf, proj1, proj2, 0x00000000);
				free_vectors(proj1, proj2, 0, 0);
			}
			else if (previous_point_x && fdf->screen_info->projection == perspective && previous_point_x->z > fdf->screen_info->screen_depth + 10 && pt->z > fdf->screen_info->screen_depth + 10)
			{
				t_vec3d	*proj1 = project_perspective(previous_point_x, fdf->screen_info->screen_plane, fdf->screen_info);
				t_vec3d *proj2 = project_perspective(pt, fdf->screen_info->screen_plane, fdf->screen_info);
				if (proj1 && proj2)
					connect_vects(fdf, proj1, proj2, 0x00000000);
				free_vectors(proj1, proj2, 0, 0);
			}
			free(previous_point_x);
			previous_point_x = new_vect3d(pt->x, pt->y, pt->z);
			free(pt);
		}
		if (previous_point_x)
			free(previous_point_x);
		previous_point_x = 0;
	}

	draw_vect(fdf, fdf->screen_info->rotation_center, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->mlx_data->img, 0, 0);

	free(fdf->screen_info->rotation_center);
	fdf->screen_info->rotation_center = rotation_center_prev;
}
