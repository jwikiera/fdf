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

typedef struct s_intarr
{
	int	size;
	int	*arr;
}	t_intarr;

/* frees the passed string */
t_intarr	*str_to_intarr(char *s)
{
	char		*num;
	t_intarr	*res;
	int			i;
	int			num_index;

	if (!s)
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
	{
		free(s);
		return (NULL);
	}
	num_index = 0;
	i = 0;
	while (*s)
	{
		if (*s != ' ')
		{

			s ++;
			i ++;
		}
		else
		{

		}
	}
	res->size = i;
	return (res);
}

t_map	*map_from_fd(const char *filename)
{
	t_map		*res;
	int			**map;
	int			fd;
	t_intarr	*int_line;
	int 		i;

	fd = open(filename, O_RDONLY);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->size_x = 0;
	res->size_y = 0;
	i = 0;
	while (1)
	{
		int_line = str_to_intarr(get_next_line(fd));
		if (!int_line)
			return (res);
		map = ft_realloc(&map, sizeof(*map) + sizeof(**map));
		if (!map)
			return (NULL);
		map[i] = int_line->arr;
		i ++;
	}
}
