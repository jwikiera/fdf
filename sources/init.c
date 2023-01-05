/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:56 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/11 13:36:27 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*return_print(char *message)
{
	ft_putstr_fd(message, 1);
	return (NULL);
}

int	init_part_two(t_fdf *res)
{
	res->screen_info = screen_info_init();
	if (!res->screen_info)
	{
		free_map_gnlstr(res->map_struct, 0);
		ft_putstr_fd("Failed to initialize screen info!\n", 1);
		return (0);
	}
	return (1);
}

t_fdf	*init_fdf(char *argv[])
{
	t_fdf	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (return_print("Failed to allocate the fdf struct!\n"));
	res->map_struct = map_from_fd(argv[1]);
	if (!res->map_struct)
	{
		free(res);
		return (return_print("Please pass a valid map file!\n"));
	}
	if (res->map_struct->size_x == 0 || res->map_struct->size_y == 0)
	{
		free_map_gnlstr(res->map_struct, 0);
		free(res);
		return (return_print("Please pass a non-empty map file!\n"));
	}
	if (!init_part_two(res))
		return (NULL);
	return (res);
}

int	post_init_two(t_fdf *fdf)
{
	fdf->mlx_data->img = mlx_new_image(fdf->mlx, fdf->screen_info->width,
			fdf->screen_info->height);
	if (!fdf->mlx_data->img)
	{
		free_map_gnlstr(fdf->map_struct, 0);
		return (0);
	}
	fdf->mlx_data->addr = mlx_get_data_addr(fdf->mlx_data->img,
			&fdf->mlx_data->bits_per_pixel, &fdf->mlx_data->line_length,
			&fdf->mlx_data->endian);
	if (!fdf->mlx_data->addr)
	{
		free_map_gnlstr(fdf->map_struct, 0);
		return (0);
	}
	return (1);
}

int	post_init(t_fdf *fdf, char *argv[])
{
	fdf->screen_title = ft_strjoin("fdf: ", argv[1]);
	if (!fdf->screen_title)
		destroy(fdf);
	ft_printf("Opening window...\n");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		free_map_gnlstr(fdf->map_struct, 0);
		return (0);
	}
	fdf->win = mlx_new_window(fdf->mlx, fdf->screen_info->width,
			fdf->screen_info->height, fdf->screen_title);
	if (!fdf->win)
	{
		free_map_gnlstr(fdf->map_struct, 0);
		return (0);
	}
	fdf->mlx_data = malloc(sizeof(*fdf->mlx_data));
	if (!fdf->mlx_data)
	{
		free_map_gnlstr(fdf->map_struct, 0);
		return (0);
	}
	return (post_init_two(fdf));
}
