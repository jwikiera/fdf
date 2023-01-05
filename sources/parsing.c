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

char	*gnl_trim(int fd)
{
	char	*res;
	char	*gnl_res;

	gnl_res = get_next_line(fd);
	if (!gnl_res)
		return (NULL);
	res = ft_strtrim(gnl_res, "\n");
	free(gnl_res);
	return (res);
}

t_map_struct	*init(const char *filename, int *fd)
{
	t_map_struct	*res;

	ft_printf("Loading %s, please wait...\n", filename);
	*fd = open(filename, O_RDONLY);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->map = malloc(1);
	if (!res->map)
		return (NULL);
	res->size_x = 0;
	res->size_y = 0;
	res->height_mult = 10;
	return (res);
}

int	map_from_fd_2(t_map_struct	*res, char *gnl_str)
{
	char			**split_res;
	int				i;

	res->map = ft_realloc_int2darr(res->map, res->size_y, res->size_x,
			res->size_x + 1);
	if (!res->map)
		return (0);
	split_res = ft_split(gnl_str, ' ');
	if (!split_res)
	{
		free_map_gnlstr(res, gnl_str);
		return (0);
	}
	i = 0;
	while (i < count_words(gnl_str, ' '))
	{
		res->map[res->size_x][i] = ft_atoi(split_res[i]);
		i ++;
	}
	res->size_x ++;
	free_sp(split_res, count_words(gnl_str, ' '));
	free(gnl_str);
	gnl_str = 0;
	return (1);
}

void	print_msg(int type, t_map_struct *map_struct)
{
	if (type == 0)
	{
		ft_printf("Loading done! Map size: %d x %d\n",
			map_struct->size_x, map_struct->size_y);
	}
	else
	{
		ft_printf("Error while loading map, row size is different"
			"from the first one! (row %d)\n", map_struct->size_x + 1);
	}
}

t_map_struct	*map_from_fd(const char *filename)
{
	t_map_struct	*res;
	int				fd;
	char			*gnl_str;

	res = init(filename, &fd);
	if (!res)
		return (NULL);
	while (1)
	{
		gnl_str = gnl_trim(fd);
		if (!gnl_str)
		{
			print_msg(0, res);
			return (res);
		}
		if (res->size_y == 0)
			res->size_y = count_words(gnl_str, ' ');
		if (count_words(gnl_str, ' ') != res->size_y)
		{
			print_msg(1, res);
			return (free_map_gnlstr(res, gnl_str));
		}
		if (!map_from_fd_2(res, gnl_str))
			return (free_map_gnlstr(res, gnl_str));
	}
}
