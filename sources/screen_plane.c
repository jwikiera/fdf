/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_plane3d	*get_screen_plane(int width, int height, int spectator_distance)
{
	t_vec3d		*p1;
	t_vec3d		*p2;
	t_vec3d		*p3;

	p1 = new_vect3d(0, 0, spectator_distance);
	p2 = new_vect3d(0, -height / 2, spectator_distance);
	p3 = new_vect3d(-width / 2, -height / 2, spectator_distance);
	if (!p1 || !p2 || !p3)
		return (free_vectors(p1, p2, p3, 0));
	return (plane_from_points(p1, p2, p3));
}
