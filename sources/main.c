#include "stdio.h"
#include <sys/fcntl.h>

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->screen_width || y < 0 || y >= data->screen_height)
	{
		ft_printf("Warning! pixel off screen (%d ; %d)", x, y);
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	fill_screen(t_data *data, int color)
{
	int i;
	int j;

	i = 0;
	while (i < data->screen_width)
	{
		j = 0;
		while (j < data->screen_height)
		{
			my_mlx_pixel_put(data, i, j, color);
			j ++;
		}
		i ++;
	}
}

void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	float	a;
	float	b;
	int		i;
	int printed_y;

	a = ft_abs_float(((float)x1 - (float)x2) / ((float)y1 - (float)y2));
	printf("a: %f\n", a);
	if (a > 1)
	{
		a = ft_abs_float(((float)y1 - (float)y2) / ((float)x1 - (float)x2));
		printf("new a: %f\n", a);

		if (y2 < y1)
			a *= -1;

		int smallest_y;
		if (x1 < x2)
		{
			smallest_y = y1;
		}
		else
		{
			a *= -1;
			smallest_y = y2;
		}

		b = smallest_y - a * ft_min_float(x1, x2);
		i = ft_min_float(x1, x2);
		while (i < ft_max_float(x1, x2))
		{
			printed_y = a * (float)i + b;
			//printf("i: %d, y: %d\n", i, printed_y);
			my_mlx_pixel_put(data, i, printed_y, color);
			i ++;
		}
	}
	else
	{
		int smallest_x;
		//int biggest_y;

		if (x2 < x1)
			a *= -1;

		if (y1 < y2)
		{
			smallest_x = x1;
			//a *= -1;
		}
		else
		{
			smallest_x = x2;

		}

		b = smallest_x - a * ft_min_float(y1, y2);
		printf("b: %f\n", b);
		i = ft_min_float(y1, y2);
		while (i < ft_max_float(y1, y2))
		{
			printed_y = a * (float)i + b;
			//printf("i: %d, y: %d\n", i, printed_y);
			my_mlx_pixel_put(data, printed_y, i, color);
			i ++;
		}
	}


	my_mlx_pixel_put(data, x1, y1, 0x0000FF00);
	my_mlx_pixel_put(data, x2, y2, 0x0000FF00);
}

void draw_rect(t_data *data, int x, int y, int width, int height, int color)
{
	draw_line(data, x, y, x + width, y, color);
	draw_line(data, x + width, y, x + width, y + height, color);
	draw_line(data, x + width, y + height, x, y + height, color);
	draw_line(data, x, y + height, x, y, color);
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

	draw_line(&img, 900, 100, 100, 100, 0x00FF0000);
	//draw_line(&img, 100, 100, 50, 300, 0x00FF0000);

	draw_rect(&img, 1000, 400, 200, 200, 0x00FF0000);

	t_color *test_color = t_color_from_int(0xFF000000);
	t_color *test_color2 = t_color_from_argb(0, 255, 0, 0);
	printf("color: %08x, a: %d, r: %d, g: %d, b: %d\n", test_color->color, test_color->a, test_color->r, test_color->g, test_color->b);
	printf("color: %08x, a: %d, r: %d, g: %d, b: %d\n", test_color2->color, test_color2->a, test_color2->r, test_color2->g, test_color2->b);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);

	return (0);
}