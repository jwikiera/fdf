/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_proj_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*free_proj_map(t_vec3d ***res, int sizey, int sizex, int sizelast)
{
	int	i;
	int	j;
	int	maxx;

	i = 0;
	while (i < sizey)
	{
		if (i == sizey - 1)
			maxx = sizelast;
		else
			maxx = sizex;
		j = 0;
		while (j < maxx)
		{
			free(res[i][j]);
			j ++;
		}
		free(res[i]);
		i ++;
	}
	free(res);
	return (NULL);
}

int	free_map_int(t_vec3d ***res, int sizey, int sizex, int sizelast)
{
	free_proj_map(res, sizey, sizex, sizelast);
	return (0);
}

t_vec3d	*get_pt(t_fdf *fdf, int i, int j)
{
	return (new_vect3d(fdf->map_struct->pos_x + i
			* fdf->map_struct->rect_size, fdf->map_struct->pos_y
			+ j * fdf->map_struct->rect_size, fdf->map_struct->pos_z
			- fdf->map_struct->map[j][i] * fdf->map_struct->height_mult
		+ fdf->screen_info->pos_z));
}

/* The res[i][*j] malloc is not protected directly here, because some vects
 * can be empty. The not null check happens in the main draw function */
int	second_while(int i, int *j, t_vec3d ***res, t_fdf *fdf)
{
	t_vec3d	*pt;
	t_vec3d	*rotated_pt;

	while (*j < fdf->map_struct->size_y)
	{
		pt = get_pt(fdf, *j, i);
		if (!pt)
			return (free_map_int(res, i, fdf->map_struct->size_y, *j));
		if (fdf->screen_info->projection == orthogonal)
			res[i][*j] = project_orthogonal(pt, fdf->screen_info->screen_plane,
					fdf->screen_info);
		else
		{
			rotated_pt = apply_rotation_matrix_to_point(pt, fdf->screen_info);
			if (rotated_pt->z > fdf->screen_info->screen_depth)
				res[i][*j] = project_perspective(pt,
						fdf->screen_info->screen_plane, fdf->screen_info);
			else
				res[i][*j] = NULL;
			free(rotated_pt);
		}
		free(pt);
		(*j)++;
	}
	return (1);
}

t_vec3d	***get_proj_map(t_fdf *fdf)
{
	t_vec3d	***res;
	int		i;
	int		j;

	res = malloc(sizeof(*res) * fdf->map_struct->size_x);
	if (!res)
		return (NULL);
	i = 0;
	while (i < fdf->map_struct->size_x)
	{
		j = 0;
		res[i] = malloc(sizeof(**res) * fdf->map_struct->size_y);
		if (!res[i])
			return (free_proj_map(res, i, fdf->map_struct->size_y, j));
		second_while(i, &j, res, fdf);
		i ++;
	}
	return (res);
}
