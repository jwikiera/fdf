/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
void	draw_cube(t_fdf *fdf, t_plane3d *plane, int x,
 int y, int z, int size, int color)
{
	t_vec3d *p1 = new_vect3d(x, y, z);
	t_vec3d *p2 = new_vect3d(x + size, y, z);
	t_vec3d *p3 = new_vect3d(x + size, y, z + size);
	t_vec3d *p4 = new_vect3d(x, y, z + size);

	t_vec3d *p5 = new_vect3d(x, y + size, z);
	t_vec3d *p6 = new_vect3d(x + size, y + size, z);
	t_vec3d *p7 = new_vect3d(x + size, y + size, z + size);
	t_vec3d *p8 = new_vect3d(x, y + size, z + size);

	connect_vects(fdf, project_perspective(p1, plane, fdf->screen_info),
 		roject_perspective(p2, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p2, plane, fdf->screen_info),
 project_perspective(p3, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p3, plane, fdf->screen_info),
 project_perspective(p4, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p4, plane, fdf->screen_info),
 project_perspective(p1, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p5, plane, fdf->screen_info),
 project_perspective(p6, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p6, plane, fdf->screen_info),
 project_perspective(p7, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p7, plane, fdf->screen_info),
 project_perspective(p8, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p8, plane, fdf->screen_info),
 project_perspective(p5, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p1, plane, fdf->screen_info),
 project_perspective(p5, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p4, plane, fdf->screen_info),
 project_perspective(p8, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p3, plane, fdf->screen_info),
 project_perspective(p7, plane, fdf->screen_info), color);
	connect_vects(fdf, project_perspective(p2, plane, fdf->screen_info),
 project_perspective(p6, plane, fdf->screen_info), color);
}

void	draw_cube_orthogonal(t_fdf *fdf, t_plane3d *plane, int x,
 int y, int z, int size, int color)
{
	t_vec3d *p1 = new_vect3d(x, y, z);
	t_vec3d * p2 = new_vect3d(x + size, y, z);
	t_vec3d * p3 = new_vect3d(x + size, y, z + size);
	t_vec3d * p4 = new_vect3d(x, y, z + size);

	t_vec3d * p5 = new_vect3d(x, y + size, z);
	t_vec3d * p6 = new_vect3d(x + size, y + size, z);
	t_vec3d * p7 = new_vect3d(x + size, y + size, z + size);
	t_vec3d * p8 = new_vect3d(x, y + size, z + size);

	connect_vects(fdf, project_orthogonal(p1, plane, fdf->screen_info),
 project_orthogonal(p2, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p2, plane, fdf->screen_info),
 project_orthogonal(p3, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p3, plane, fdf->screen_info),
 project_orthogonal(p4, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p4, plane, fdf->screen_info),
 project_orthogonal(p1, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p5, plane, fdf->screen_info),
 project_orthogonal(p6, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p6, plane, fdf->screen_info),
 project_orthogonal(p7, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p7, plane, fdf->screen_info),
 project_orthogonal(p8, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p8, plane, fdf->screen_info),
 project_orthogonal(p5, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p1, plane, fdf->screen_info),
 project_orthogonal(p5, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p4, plane, fdf->screen_info),
 project_orthogonal(p8, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p3, plane, fdf->screen_info),
 project_orthogonal(p7, plane, fdf->screen_info), color);
	connect_vects(fdf, project_orthogonal(p2, plane, fdf->screen_info),
 project_orthogonal(p6, plane, fdf->screen_info), color);
}
 */
