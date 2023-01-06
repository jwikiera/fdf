/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	destroy(t_fdf *fdf)
{
	if (!fdf)
		exit(0);
	if (fdf->map_struct)
	{
		free_map_members(fdf->map_struct);
		free(fdf->map_struct->map);
		free(fdf->map_struct);
	}
	if (fdf->screen_info->rotation_matrix)
		free_matrix3d(fdf->screen_info->rotation_matrix);
	if (fdf->screen_info->screen_plane)
		free_plane3d(fdf->screen_info->screen_plane);
	if (fdf->screen_info->rotation_center)
		free(fdf->screen_info->rotation_center);
	if (fdf->screen_title)
		free(fdf->screen_title);
	if (fdf->screen_info)
		free(fdf->screen_info);
	ft_printf("Exiting...\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;
	int		arg_handle_res;

	print_title();
	arg_handle_res = handle_args(argc, argv);
	if (arg_handle_res != 0)
		return (arg_handle_res);
	fdf = init_fdf(argv);
	if (!fdf)
		return (1);
	if (!post_init(fdf, argv))
		destroy(fdf);
	add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
		-35, axis_x, 0);
	add_angle_to_rotation_matrix(fdf->screen_info->rotation_matrix,
		45, axis_z, 0);
	draw_map(fdf);
	mlx_hook(fdf->win, ON_KEYDOWN, 1L << 0, handle_keypress, fdf);
	mlx_hook(fdf->win, ON_DESTROY, 0, destroy, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->mlx_data->img, 0, 0);
	mlx_loop(fdf->mlx);
	return (0);
}
