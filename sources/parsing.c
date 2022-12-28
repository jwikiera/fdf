/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>

#include "fdf.h"
#include "get_next_line.h"

void	*free_map_gnlstr(t_map_struct *map_struct, char *gnl_str)
{
	int i;

	if (gnl_str)
		free(gnl_str);
	i = 0;
	while (i < map_struct->size_x)
	{
		free(map_struct->map[map_struct->size_x]);
		i ++;
	}
	free(map_struct);
	return (NULL);
}

t_map_struct	*map_from_fd(const char *filename)
{
	t_map_struct	*res;
	int				fd_i[2];
	char			*gnl_str;
	char			**split_res;

	ft_printf("Loading %s, please wait...\n", filename);
	fd_i[0] = open(filename, O_RDONLY);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->map = malloc(sizeof(*(res->map)));
	if (!res->map)
		return (NULL);
	res->size_x = 0;
	res->size_y = 0;
	res->height_mult = 2;
	while (1)
	{
		gnl_str = get_next_line(fd_i[0]);
		if (!gnl_str)
		{
			ft_printf("Loading done!\n");
			return (res);
		}
		gnl_str = ft_strtrim(gnl_str, "\n");
		if (!gnl_str)
			return (res);
		res->map = ft_realloc_int2darr(res->map, res->size_x, res->size_x + 1);
		if (!res->map)
			return (NULL);
		res->map[res->size_x] = malloc(sizeof(*(res->map)) * count_words(gnl_str, ' '));
		split_res = ft_split(gnl_str, ' ');
		if (!split_res)
			return (free_map_gnlstr(res, gnl_str));
		fd_i[1] = 0;
		while (fd_i[1] < count_words(gnl_str, ' '))
		{
			res->map[res->size_x][fd_i[1]] = ft_atoi(split_res[fd_i[1]]);
			fd_i[1] ++;
		}
		res->size_x ++;
		res->size_y = count_words(gnl_str, ' ');
	}
}
