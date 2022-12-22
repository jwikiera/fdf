/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int col(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_color	*t_color_from_int(int color)
{
	t_color	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->color = color;
	/* AARRGGBB */
	res->a = color / 16777216;
	res->r = (color << 8) / 16777216;
	res->g = (color << 16) / 16777216;
	printf("bruh color (%axis_x) << 24: %axis_x\n", color, color << 24);
	res->b = (color << 24) / 16777216;
	return (res);
}

t_color	*t_color_from_argb(int a, int r, int g, int b)
{
	t_color	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->color = (b << 24) + (g << 16) + (r << 8) + a;
	/* AARRGGBB */
	res->a = a;
	res->r = r;
	res->g = g;
	res->b = b;
	return (res);
}
