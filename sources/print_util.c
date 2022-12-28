/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_map_struct *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size_x)
	{
		j = 0;
		while (j < map->size_y)
		{
			ft_printf("%3d, ", map->map[i][j]);
			j ++;
		}
		ft_printf("\n");
		i ++;
	}
	ft_printf("\n");
}

void	print_title()
{
	ft_printf("________/\\\\\\\\\\_________/\\\\\\_________/\\\\\\\\\\_        \n"
			  " ______/\\\\\\///_________\\/\\\\\\_______/\\\\\\///__       \n"
			  "  _____/\\\\\\_____________\\/\\\\\\______/\\\\\\______      \n"
			  "   __/\\\\\\\\\\\\\\\\\\__________\\/\\\\\\___/\\\\\\\\\\\\\\\\\\___     \n"
			  "    _\\////\\\\\\//______/\\\\\\\\\\\\\\\\\\__\\////\\\\\\//____    \n"
			  "     ____\\/\\\\\\_______/\\\\\\////\\\\\\_____\\/\\\\\\______   \n"
			  "      ____\\/\\\\\\______\\/\\\\\\__\\/\\\\\\_____\\/\\\\\\______  \n"
			  "       ____\\/\\\\\\______\\//\\\\\\\\\\\\\\/\\\\____\\/\\\\\\______ \n"
			  "        ____\\///________\\///////\\//_____\\///_______\n");
	ft_printf("Welcome to jwikiera's fdf!\n\n");
}