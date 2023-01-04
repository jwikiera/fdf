/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_printf("Please pass exactly one file as parameter!\n");
		return (2);
	}
	if (!ft_str_endswith(argv[1], ".fdf"))
	{
		ft_printf("File extension is not fdf!\n");
		return (3);
	}
	ft_printf("File: %s\n", argv[1]);
	return (0);
}
