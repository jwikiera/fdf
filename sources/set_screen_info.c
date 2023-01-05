/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_screen_info	*screen_info_init(void)
{
	t_screen_info	*screen_info;

	screen_info = malloc(sizeof(*screen_info));
	if (!screen_info)
		return (NULL);
	screen_info->pos_x = 0;
	screen_info->pos_y = 0;
	screen_info->pos_z = 0;
	screen_info->mov_speed = 5;
	screen_info->zoom_speed = 5;
	screen_info->width = 1920;
	screen_info->height = 1080;
	screen_info->rotation_matrix = new_matrix(new_vect3d(1, 0, 0),
			new_vect3d(0, 1, 0), new_vect3d(0, 0, 1));
	screen_info->rotation_center = new_vect3d(0, 0, 0);
	screen_info->rotation_speed = 5;
	screen_info->eye_z = 0;
	screen_info->screen_depth = 200;
	screen_info->screen_plane = get_screen_plane(screen_info->width,
			screen_info->height, screen_info->screen_depth);
	screen_info->background_color = 0x00FFFFFF;
	screen_info->projection = orthogonal;
	return (screen_info);
}
