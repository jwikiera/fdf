/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3d	*vec_add(t_vec3d *v1, t_vec3d *v2)
{
	t_vec3d	*res;

	if (v1 == NULL || v2 == NULL)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->x = v1->x + v2->x;
	res->y = v1->y + v2->y;
	res->z = v1->z + v2->z;
	return (res);
}

t_vec3d	*vec_sub(t_vec3d *v1, t_vec3d *v2)
{
	t_vec3d	*res;

	if (v1 == NULL || v2 == NULL)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->x = v1->x - v2->x;
	res->y = v1->y - v2->y;
	res->z = v1->z - v2->z;
	return (res);
}
