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

void	*free_s_res(char *s, t_intarr *res, int shouldfreeres)
{
	free(s);
	if (shouldfreeres)
	{
		free(res->arr);
		free(res);
	}
	return (NULL);
}

/* frees the passed string */
t_intarr	*str_to_intarr(char *s)
{
	char		*num;
	t_intarr	*res_;
	int			new_num;
	char		*trimmed;

	if (!s)
		return (NULL);
	trimmed = ft_strtrim(s, " \n");
	free(s);
	res_ = malloc(sizeof(*res_));
	if (!res_)
		return (free_s_res(trimmed, 0, 0));
	res_->size = 0;
	res_->arr = malloc(sizeof(*(res_->arr)));
	num = malloc(1);
	if (!num)
		return (free_s_res(trimmed, res_, 1));
	new_num = 0;
	while (*trimmed)
	{
		if (!new_num && *trimmed != ' ')
		{
			num = ft_realloc_chararr(num, ft_strlen(num), ft_strlen(num) + 1);
			if (!num)
				return (free_s_res(trimmed, res_, 1));
			num[ft_strlen(num)] = *trimmed;
		}
		else
		{
			//ft_printf("sizeof(int): %u, sizeof(*(res_->arr)): %u\n", sizeof(int), sizeof(*(res_->arr)));
			res_->arr = ft_realloc_intarr(res_->arr, res_->size, res_->size + 1);
			res_->arr[res_->size] = ft_atoi(num);

			free(num);
			num = ft_calloc(1, 1);
			if (!num)
				return (free_s_res(trimmed, res_, 1));
			res_->size ++;
			new_num = 0;
			while (*trimmed && *(trimmed + 1) == ' ') {
				trimmed++;
			}
		}
		trimmed ++;
		if (*trimmed == ' ')
			new_num = 1;
		if (!*trimmed)
		{
			res_->arr = ft_realloc_intarr(res_->arr, res_->size, res_->size + 1);
			res_->arr[res_->size] = ft_atoi(num);
			free(num);
			res_->size ++;
		}
	}
	/*ft_printf("array: ");
	for (int i = 0; i < res_->size; ++i) {
		ft_printf("%3d, ", res_->arr[i]);
	}
	ft_printf("\n");*/
	return (res_);
}

t_map	*map_from_fd(const char *filename)
{
	t_map		*res;
	//int			**map;
	int			fd;
	t_intarr	*int_line;

	fd = open(filename, O_RDONLY);
	res = malloc(sizeof(*res));
	res->map = malloc(sizeof(*(res->map)));
	if (!res)
		return (NULL);
	res->size_x = 0;
	res->size_y = 0;
	while (1)
	{
		int_line = str_to_intarr(get_next_line(fd));
		if (!int_line)
			return (res);

		res->map = ft_realloc_int2darr(res->map, res->size_x, res->size_x + 1);
		if (!res->map)
			return (NULL);
		res->map[res->size_x] = int_line->arr;

		ft_printf("array: ");
		ft_printf("\n");

		res->size_x ++;
		res->size_y = int_line->size;
	}
}
