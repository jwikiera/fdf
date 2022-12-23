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

#ifndef FDF_H
# define FDF_H

# include "stdlib.h"
# include "stdio.h"
# include "math.h"

# include <mlx.h>

# include <libft.h>
# include <get_next_line.h>
# include <ft_printf.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		screen_width;
	int		screen_height;
}	t_data;

typedef struct s_color {
	int	color;
	int	a;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map {
	int	**map;
	int	size_x;
	int	size_y;
}	t_map;

/* color */
t_color	*t_color_from_int(int color);
t_color	*t_color_from_argb(int a, int r, int g, int b);

/* parsing */
t_map	*map_from_fd(const char *filename);

/* mlx helpers */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* draw helpers */
void	draw_line(t_data *data, const int coords[4], int color);
void	fill_screen(t_data *data, int color);
void	draw_square(t_data *data, const int square_details[4], int color);
void	circle_bres(t_data *data, const int circle_details[3], int color);
void	draw_vect(t_data *data, t_vec3d *vect, int color);
void	connect_vects(t_data *data, t_vec3d *v1, t_vec3d *v2, int color);

void	draw_cube(t_data *data, t_plane3d *plane, int x, int y, int z, int size, int color, t_screen_info *screen_info);
void	draw_cube_orthogonal(t_data *data, t_plane3d *plane, int x, int y, int z, int size, int color, t_screen_info *screen_info);

#endif
