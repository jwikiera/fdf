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
		free(map_struct->map[i]);
		i ++;
	}
	//free(map_struct);
	return (NULL);
}

void	free_map_members(t_map_struct *map_struct)
{
	int i;

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
	while(i < len)
	{
		free(split[i]);
		i ++;
	}
	free(split);
}

t_map_struct	*map_from_fd(const char *filename)
{
	t_map_struct	*res;
	int				fd_i[2];
	char			*gnl_str;
	char 			*old_gnl;
	char			**split_res;

	ft_printf("Loading %s, please wait...\n", filename);
	fd_i[0] = open(filename, O_RDONLY);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->map = malloc(1);
	if (!res->map)
		return (NULL);
	res->size_x = 0;
	res->size_y = 0;
	res->height_mult = 10;
	while (1)
	{
		gnl_str = get_next_line(fd_i[0]);
		if (!gnl_str)
		{
			ft_printf("Loading done!\n");
			return (res);
		}
		old_gnl = gnl_str;
		gnl_str = ft_strtrim(gnl_str, "\n");
		free(old_gnl);
		if (!gnl_str)
			return (res);
		res->size_y = count_words(gnl_str, ' ');
		res->map = ft_realloc_int2darr(res->map, res->size_y, res->size_x, res->size_x + 1);
		if (!res->map)
			return (NULL);
		//res->map[res->size_x] = malloc(sizeof(*(res->map)) * count_words(gnl_str, ' '));
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
		free_sp(split_res, count_words(gnl_str, ' '));
		free(gnl_str);
		gnl_str = 0;
	}
}
