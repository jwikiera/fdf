/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*free_map_gnlstr(t_map_struct *map_struct, char *gnl_str)
{
	int	i;

	if (gnl_str)
		free(gnl_str);
	i = 0;
	while (i < map_struct->size_x)
	{
		free(map_struct->map[i]);
		i ++;
	}
	free(map_struct->map);
	free(map_struct);
	return (NULL);
}

void	free_map_members(t_map_struct *map_struct)
{
	int	i;

	i = 0;
	while (i < map_struct->size_x)
	{
		free(map_struct->map[i]);
		i ++;
	}
}

void	free_sp(char **split, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(split[i]);
		i ++;
	}
	free(split);
}

void	set_extremes(t_map_struct *map_struct)
{
	int	max;
	int	min;
	int	i;
	int	j;

	if (!map_struct)
		return ;
	max = 0;
	min = 0;
	i = 0;
	while (i < map_struct->size_y)
	{
		j = 0;
		while (j < map_struct->size_x)
		{
			if (map_struct->map[j][i] > max)
				max = map_struct->map[j][i];
			else if (map_struct->map[j][i] < min)
				min = map_struct->map[j][i];
			j ++;
		}
		i ++;
	}
	map_struct->min_height = min;
	map_struct->max_height = max;
}
