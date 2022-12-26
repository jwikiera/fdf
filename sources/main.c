#include "stdio.h"
#include <sys/fcntl.h>

#include "fdf.h"
//#include "X11/"

t_plane3d *get_screen_plane(int width, int height, int spectator_distance) {
	return (plane_from_points(new_vect3d(0, 0, spectator_distance), new_vect3d(0, -height/2, spectator_distance), new_vect3d(-width/2, -height/2, spectator_distance)));
}

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close_win(int keycode, t_vars *vars)
{
	(void) keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int main(int argc, char *argv[])
{
	ft_printf("hello\n");

	void	*mlx;
	t_data	img;
	void	*mlx_win;


	ft_printf("argc: %d\n", argc);
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

	ft_printf("arg 0: %s\n", argv[1]);

	t_map *map = map_from_fd(argv[1]);
	if (!map)
	{
		ft_printf("Please pass a valid map file!\n");
		return (3);
	}

	ft_printf("map:\n");
	for (int i = 0; i < map->size_x; ++i) {
		for (int j = 0; j < map->size_y; ++j) {
			ft_printf("%3d, ", map->map[i][j]);
		}
		ft_printf("\n");
	}
	ft_printf("\n");

	mlx = mlx_init();
	img.screen_width = 1920;
	img.screen_height = 1080;
	img.img = mlx_new_image(mlx, img.screen_width, img.screen_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, img.screen_width, img.screen_height, "Hello world!");

	fill_screen(&img, 0x00FFFFFF);

	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	//int line_coords[4] = {900, 100, 100, 100};
	//draw_line(&img, line_coords, 0x00FF0000);

	//draw_line(&img, 100, 100, 50, 300, 0x00FF0000);

	//int square_coords[4] = {1000, 400, 200, 200};
	//draw_square(&img, square_coords, 0x00FF0000);

	int circle_details[3] = {1400, 400, 200};
	circle_bres(&img, circle_details, 0x00FF0000);

	//t_vec3d *vec = new_vect3d(100, 300, 400);
	//draw_vect(&img, vec, 0x00FF0000);

	//t_vec3d *vec2 = new_vect3d(200, 350, 400);
	//draw_vect(&img, vec2, 0x00FF0000);

	//connect_vects(&img, vec, vec2, 0x00000000);

	int line_coords2[4] = {1600, 300, 1800, 350};
	draw_line(&img, line_coords2, 0x00FF0000);

	int eye_z = 0;
	int plane_depth = 200;
	t_plane3d *screen_plane = get_screen_plane(img.screen_width, img.screen_height, plane_depth);
	t_screen_info screen_info;
	screen_info.rotation_matrix = new_matrix(new_vect3d(1, 0, 0), new_vect3d(0, 1, 0), new_vect3d(0, 0, 1));
	screen_info.rotation_center = new_vect3d(0, 0, 0);
	screen_info.eye_z = eye_z;
	screen_info.height = img.screen_height;
	screen_info.width = img.screen_width;

	int cube_width = img.screen_height / 4;
	int cube_x = img.screen_width / 3 * 2 - cube_width / 2;
	int cube_y = img.screen_height / 2 - cube_width / 2;
	int cube_z = plane_depth + 100;

	printf("x: %d, y: %d, z: %d\n", cube_x, cube_y, cube_z);

	t_vec3d *rotation_center_prev = new_vect3d(screen_info.rotation_center->x, screen_info.rotation_center->y, screen_info.rotation_center->z);
	screen_info.rotation_center = new_vect3d(cube_x + cube_width / 2, cube_y + cube_width /2, cube_z + cube_width / 2);


	//add_angle_to_rotation_matrix(screen_info.rotation_matrix, 90, axis_z, 0);
	//add_angle_to_rotation_matrix(screen_info.rotation_matrix, 90, axis_x, 0);
	//add_angle_to_rotation_matrix(screen_info.rotation_matrix, 35, axis_x, 0);
	//add_angle_to_rotation_matrix(screen_info.rotation_matrix, 45, axis_y, 0);

	//draw_cube(&img, screen_plane, cube_x, cube_y, cube_z, cube_width, 0x00000000, &screen_info);
	//draw_cube_orthogonal(&img, screen_plane, cube_x, cube_y, cube_z, cube_width, 0x00000000, &screen_info);
	draw_cube(&img, screen_plane, cube_x, cube_y, cube_z, cube_width, 0x00000000, &screen_info);
	screen_info.rotation_center = rotation_center_prev;

	/*t_color *test_color = t_color_from_int(0xFF000000);
	t_color *test_color2 = t_color_from_argb(0, 255, 0, 0);
	printf("color: %08x, a: %d, r: %d, g: %d, b: %d\n", test_color->color, test_color->a, test_color->r, test_color->g, test_color->b);
	printf("color: %08x, a: %d, r: %d, g: %d, b: %d\n", test_color2->color, test_color2->a, test_color2->r, test_color2->g, test_color2->b);
	 */


	int size = 5;
	int base_x = 400 + map->size_x * size / 2;
	int base_y = 200 + map->size_y * size / 2;
	int height_mult = 1;//5;
	int depth = 200;

	rotation_center_prev = new_vect3d(screen_info.rotation_center->x, screen_info.rotation_center->y, screen_info.rotation_center->z);
	screen_info.rotation_center = new_vect3d(base_x + map->size_x * size / 2, base_y + map->size_y * size / 2, depth);
	//add_angle_to_rotation_matrix(screen_info.rotation_matrix, 35, axis_y, 0);

	t_vec3d *previous_point_y = 0;
	for (int i = 0; i < map->size_x; ++i) {
		for (int j = 0; j < map->size_y; ++j) {
			//ft_printf("%3d, ", map->map[i][j]);
			t_vec3d *pt = new_vect3d(base_x + i * size, base_y + j * size, depth - map->map[i][j] * height_mult);
			if (previous_point_y)
				connect_vects(&img, project_perspective(previous_point_y, screen_plane, &screen_info), project_perspective(pt, screen_plane, &screen_info), 0x00000000);
			previous_point_y = new_vect3d(pt->x, pt->y, pt->z);
		}
		//ft_printf("\n");
		previous_point_y = 0;
	}

	t_vec3d *previous_point_x = 0;
	for (int i = 0; i < map->size_y; ++i) {
		for (int j = 0; j < map->size_x; ++j) {
			//ft_printf("%3d, ", map->map[i][j]);
			t_vec3d *pt = new_vect3d(base_x + j * size, base_y + i * size, depth - map->map[j][i] * height_mult);
			if (previous_point_x)
				connect_vects(&img, project_perspective(previous_point_x, screen_plane, &screen_info), project_perspective(pt, screen_plane, &screen_info), 0x00000000);
			previous_point_x = new_vect3d(pt->x, pt->y, pt->z);
		}
		//ft_printf("\n");
		previous_point_x = 0;
	}

	screen_info.rotation_center = rotation_center_prev;


	t_vars vars;
	vars.mlx = mlx;
	vars.win = mlx_win;
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(mlx);

	return (0);
}