/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_keypress_2(int keycode, t_fdf *fdf)
{
	if (keycode == K_NUM_4)
		fdf->screen_info->pos_x += fdf->screen_info->mov_speed;
	else if (keycode == K_NUM_6)
		fdf->screen_info->pos_x -= fdf->screen_info->mov_speed;
	else if (keycode == K_NUM_2)
		fdf->screen_info->pos_y -= fdf->screen_info->mov_speed;
	else if (keycode == K_NUM_8)
	fdf->screen_info->pos_y += fdf->screen_info->mov_speed;
	else if (keycode == K_MINUS || keycode == K_NUM_MINUS)
		fdf->screen_info->pos_z += fdf->screen_info->zoom_speed;
	else if (keycode == K_PLUS || keycode == K_NUM_PLUS)
		fdf->screen_info->pos_z -= fdf->screen_info->zoom_speed;
	else if (keycode == K_P)
		fdf->screen_info->projection = (fdf->screen_info->projection + 1) % 2;
	else if (keycode == K_W)
		fdf->screen_info->eye_z += 5;
	else if (keycode == K_S)
		fdf->screen_info->eye_z -= 5;
}

int	handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == K_ESC)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (keycode == K_RIGHT)
		add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
			- fdf->screen_info->rotation_speed, axis_y, 0);
	else if (keycode == K_LEFT)
		add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
			fdf->screen_info->rotation_speed, axis_y, 0);
	else if (keycode == K_UP)
		add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
			- fdf->screen_info->rotation_speed, axis_x, 0);
	else if (keycode == K_DOWN)
		add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
			fdf->screen_info->rotation_speed, axis_x, 0);
	else if (keycode == K_A)
		add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
			- fdf->screen_info->rotation_speed, axis_z, 0);
	else if (keycode == K_D)
		add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
			fdf->screen_info->rotation_speed, axis_z, 0);
	handle_keypress_2(keycode, fdf);
	draw_map(fdf);
	return (0);
}
