#include "stdio.h"
#include <sys/fcntl.h>

#include "fdf.h"

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

	int line_coords[4] = {900, 100, 100, 100};
	draw_line(&img, line_coords, 0x00FF0000);
	//draw_line(&img, 100, 100, 50, 300, 0x00FF0000);

	int square_coords[4] = {1000, 400, 200, 200};
	draw_square(&img, square_coords, 0x00FF0000);

	int circle_details[3] = {400, 400, 200};
	circle_bres(&img, circle_details, 0x00FF0000);

	t_vec3d *vec = new_vect3d(100, 300, 400);
	draw_vect(&img, vec, 0x00FF0000);

	t_color *test_color = t_color_from_int(0xFF000000);
	t_color *test_color2 = t_color_from_argb(0, 255, 0, 0);
	printf("color: %08x, a: %d, r: %d, g: %d, b: %d\n", test_color->color, test_color->a, test_color->r, test_color->g, test_color->b);
	printf("color: %08x, a: %d, r: %d, g: %d, b: %d\n", test_color2->color, test_color2->a, test_color2->r, test_color2->g, test_color2->b);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);

	return (0);
}