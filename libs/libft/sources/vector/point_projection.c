/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	*project_perspective(t_vec3d *point, t_plane3d *plane,
			t_screen_info *screen_info)
{
	t_vec3d		*pt;
	t_vec3d		*line_p1;
	t_line3d	*line;
	t_vec3d		*intersection;

	pt = vec_sub(point, screen_info->rotation_center);
	if (!pt)
		return (NULL);
	pt = matrix_mult_vec(screen_info->rotation_matrix, pt);
	if (!pt)
		return (NULL);
	add_vec_inplace(pt, screen_info->rotation_center);
	line_p1 = new_vect3d(screen_info->width / 2,
			screen_info->height / 2, screen_info->eye_z);
	if (!line_p1)
		return (free_vectors(pt, 0, 0, 0));
	line = line_from_points(line_p1, pt);
	if (!line)
		return (free_vectors(pt, line_p1, 0, 0));
	intersection = line_plane_intersect3d(line, plane);
	free_vectors(pt, line_p1, 0, 0);
	free(line);
	return (intersection);
}

t_vec3d	*project_orthogonal(t_vec3d *point, t_plane3d *plane,
								t_screen_info *screen_info)
{
	t_vec3d		*pt;
	t_vec3d		*cross_res;
	t_line3d	*line;
	t_vec3d		*intersection;

	pt = vec_sub(point, screen_info->rotation_center);
	if (!pt)
		return (NULL);
	pt = matrix_mult_vec(screen_info->rotation_matrix, pt);
	if (!pt)
		return (NULL);
	add_vec_inplace(pt, screen_info->rotation_center);
	cross_res = cross(plane->v1, plane->v2);
	if (!cross_res)
		return (free_vectors(pt, 0, 0, 0));
	line = line_from_point_and_vec(pt, cross_res);
	if (!line)
		return (free_vectors(pt, cross_res, 0, 0));
	intersection = line_plane_intersect3d(line, plane);
	free_vectors(pt, cross_res, 0, 0);
	free(line);
	return (intersection);
}
