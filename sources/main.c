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
//#include "X11/"

typedef struct	s_vars {
	void			*mlx;
	void			*win;
	void			*img;
	t_data			*data;
	t_map_struct	*map_struct;
}				t_vars;

void	draw_map(t_data *data, t_map_struct *map_struct, void *mlx, void *mlx_win)
{
	(void) mlx;
	(void) mlx_win;
	fill_screen(data, data->screen_info->background_color);

	int size = ft_max_int(ft_min_int((data->screen_info->height - 600) / map_struct->size_x, (data->screen_info->width - 600) / map_struct->size_y), 1);
	//ft_printf("size: %d\n", size);
	int base_x = data->screen_info->width / 2 - map_struct->size_y * size / 2 + data->screen_info->pos_x;
	int base_y = data->screen_info->height / 2 - map_struct->size_x * size / 2 + data->screen_info->pos_y;
	//draw_vect(data, new_vect3d(base_x, base_y, 200), 0);
	//draw_vect(data, new_vect3d(data->screen_info->width / 2, data->screen_info->height / 2, 200), 0x00FF0000);
	int depth = data->screen_info->screen_depth + 100;

	t_vec3d *rotation_center_prev = new_vect3d(data->screen_info->rotation_center->x, data->screen_info->rotation_center->y, data->screen_info->rotation_center->z);
	data->screen_info->rotation_center = new_vect3d(base_x + map_struct->size_y * size / 2.0 - size / 2.0, (float)base_y + (float)map_struct->size_x * (float)size / 2.0 - size / 2.0, depth + data->screen_info->pos_z);

	//printf("map_struct sizes: x: %d, y: %d\n", map_struct->size_x, map_struct->size_y);
	t_vec3d *previous_point_y = 0;
	for (int i = 0; i < map_struct->size_y; i ++) {
		for (int j = 0; j < map_struct->size_x; j ++) {
			//ft_printf("%3d, ", map_struct->map_struct[i][j]);
			t_vec3d *pt = new_vect3d(base_x + i * size, base_y + j * size, depth - map_struct->map[j][i] * map_struct->height_mult + data->screen_info->pos_z);
			if (previous_point_y && data->screen_info->projection == orthogonal)
			{
				//connect_vects(data, project_orthogonal(previous_point_y, data->screen_info->screen_plane, data->screen_info), project_orthogonal(pt, data->screen_info->screen_plane, data->screen_info), 0x00000000);
				break;
			}
			else if (previous_point_y && data->screen_info->projection == perspective)
				connect_vects(data, project_perspective(previous_point_y, data->screen_info->screen_plane, data->screen_info), project_perspective(pt, data->screen_info->screen_plane, data->screen_info), 0x00000000);
			previous_point_y = new_vect3d(pt->x, pt->y, pt->z);
			free(pt);
		}
		//ft_printf("\n");
		previous_point_y = 0;
	}

	/*t_vec3d *previous_point_x = 0;
	for (int i = 0; i < map_struct->size_x; ++i) {
		for (int j = 0; j < map_struct->size_y; ++j) {
			//ft_printf("%3d, ", map_struct->map_struct[i][j]);
			t_vec3d *pt = new_vect3d(base_x + j * size, base_y + i * size, depth - map_struct->map[i][j] * map_struct->height_mult + data->screen_info->pos_z);
			if (previous_point_x && data->screen_info->projection == orthogonal)
				connect_vects(data, project_orthogonal(previous_point_x, data->screen_info->screen_plane, data->screen_info), project_orthogonal(pt, data->screen_info->screen_plane, data->screen_info), 0x00000000);
			else if (previous_point_x && data->screen_info->projection == perspective)
				connect_vects(data, project_perspective(previous_point_x, data->screen_info->screen_plane, data->screen_info), project_perspective(pt, data->screen_info->screen_plane, data->screen_info), 0x00000000);
			previous_point_x = new_vect3d(pt->x, pt->y, pt->z);
		}
		//ft_printf("\n");
		previous_point_x = 0;
	}

	draw_vect(data, data->screen_info->rotation_center, 0);
	mlx_put_image_to_window(mlx, mlx_win, data->img, 0, 0);*/

	data->screen_info->rotation_center = rotation_center_prev;
}

int	handle_keypress(int keycode, t_vars *vars)
{
	//ft_printf("keycode: %d\n", keycode);
	if (keycode == K_ESC)
	{
		ft_printf("freeing map\n");
		free_map_members(vars->map_struct);
		ft_printf("done freeing map\n");
		//free_map_members(vars->map_struct);
		//free_map_members(vars->map_struct);
		free_matrix3d(vars->data->screen_info->rotation_matrix);
		free_plane3d(vars->data->screen_info->screen_plane);
		free(vars->data->screen_info->rotation_center);
		free(vars->data->screen_title);
		free(vars->data->screen_info);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if  (keycode == K_RIGHT)
		add_angle_to_rotation_matrix(vars->data->screen_info->rotation_matrix, -vars->data->screen_info->rotation_speed, axis_y, 0);
	else if (keycode == K_LEFT)
		add_angle_to_rotation_matrix(vars->data->screen_info->rotation_matrix, vars->data->screen_info->rotation_speed, axis_y, 0);
	else if (keycode == K_UP)
		add_angle_to_rotation_matrix(vars->data->screen_info->rotation_matrix, -vars->data->screen_info->rotation_speed, axis_x, 0);
	else if (keycode == K_DOWN)
		add_angle_to_rotation_matrix(vars->data->screen_info->rotation_matrix, vars->data->screen_info->rotation_speed, axis_x, 0);
	else if (keycode == K_A)
		add_angle_to_rotation_matrix(vars->data->screen_info->rotation_matrix, -vars->data->screen_info->rotation_speed, axis_z, 0);
	else if (keycode == K_D)
		add_angle_to_rotation_matrix(vars->data->screen_info->rotation_matrix, vars->data->screen_info->rotation_speed, axis_z, 0);
	else if (keycode == K_NUM_4)
		vars->data->screen_info->pos_x += vars->data->screen_info->mov_speed;
	else if (keycode == K_NUM_6)
		vars->data->screen_info->pos_x -= vars->data->screen_info->mov_speed;
	else if (keycode == K_NUM_2)
		vars->data->screen_info->pos_y -= vars->data->screen_info->mov_speed;
	else if (keycode == K_NUM_8)
		vars->data->screen_info->pos_y += vars->data->screen_info->mov_speed;
	else if (keycode == K_MINUS || keycode == K_NUM_MINUS)
		vars->data->screen_info->pos_z += vars->data->screen_info->zoom_speed;
	else if (keycode == K_PLUS || keycode == K_NUM_PLUS)
		vars->data->screen_info->pos_z -= vars->data->screen_info->zoom_speed;
	else if (keycode == K_P)
		vars->data->screen_info->projection = (vars->data->screen_info->projection + 1) % 2;
	else if (keycode == K_W)
		vars->data->screen_info->eye_z += 5;
	else if (keycode == K_S)
		vars->data->screen_info->eye_z -= 5;
	draw_map(vars->data, vars->map_struct, vars->mlx, vars->win);
	return (0);
}

int destroy(int keycode, t_vars *vars)
{
	(void) keycode;
	(void) vars;
	//free_map_gnlstr(vars->map_struct, 0);
	//mlx_destroy_image(vars->mlx, vars->img);
	//free(vars);
	exit(0);
}

int handle_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_printf("Please pass exactly one file as parameter!\n");
		return (1);
	}
	if (!ft_str_endswith(argv[1], ".fdf"))
	{
		ft_printf("File extension is not fdf!\n");
		return (2);
	}
	ft_printf("File: %s\n", argv[1]);
	return (0);
}

int main(int argc, char *argv[])
{
	void	*mlx;
	t_data	*data;
	void	*mlx_win;

	t_vars *vars;
	vars = malloc(sizeof(*vars));

	ft_printf("dupa0\n");
	print_title();

	if (handle_args(argc, argv) != 0)
		return (handle_args(argc, argv));
	ft_printf("dupa1\n");
	vars->map_struct = map_from_fd(argv[1]);

	ft_printf("dupa2\n");
	if (!vars->map_struct)
	{
		ft_printf("Please pass a valid map_struct file!\n");
		return (3);
	}
	data = malloc(sizeof(*data));
	if (!data)
	{
		free_map_gnlstr(vars->map_struct, 0);
		return (0);
	}
	//print_map(map_struct);

	data->screen_info = screen_info_init();
	if (!data->screen_info)
	{
		free_map_gnlstr(vars->map_struct, 0);
		return (0);
	}

	ft_printf("Opening window...\n");
	ft_printf("initializing mlx\n");
	mlx = mlx_init();
	ft_printf("done initializing mlx\n");
	if (!mlx)
	{
		free_map_gnlstr(vars->map_struct, 0);
		return (0);
	}
	data->screen_title = ft_strjoin("fdf: ", argv[1]);

	data->img = mlx_new_image(mlx, data->screen_info->width, data->screen_info->height);
	if (!data->img)
	{
		free_map_gnlstr(vars->map_struct, 0);
		return (0);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (!data->addr)
	{
		free_map_gnlstr(vars->map_struct, 0);
		return (0);
	}
	mlx_win = mlx_new_window(mlx, data->screen_info->width, data->screen_info->height, data->screen_title);
	if (!mlx_win)
	{
		free_map_gnlstr(vars->map_struct, 0);
		return (0);
	}


	//add_angle_to_rotation_matrix(data->screen_info->rotation_matrix, -35, axis_x, 0);
	//add_angle_to_rotation_matrix(data->screen_info->rotation_matrix, 45, axis_z, 0);

	//draw_map(data, map_struct, mlx, mlx_win);


	vars->mlx = mlx;
	vars->win = mlx_win;
	vars->data = data;
	//vars->map_struct = map_struct;
	vars->img = data->img;

	mlx_hook(vars->win, ON_KEYDOWN, 1L << 0, handle_keypress, vars);
	mlx_hook(vars->win, ON_DESTROY, 0, destroy, vars);
	mlx_put_image_to_window(mlx, mlx_win, data->img, 0, 0);
	mlx_loop(mlx);
	return (0);
}