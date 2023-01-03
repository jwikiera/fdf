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

# define ON_KEYDOWN 2
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17

# ifdef LINUX
#  define K_ESC 65307
#  define K_UP 65362
#  define K_DOWN 65364
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_P 112
#  define K_MINUS 61
#  define K_PLUS 10
#  define K_R 114
#  define K_U 117
#  define K_J 106
#  define K_I 105
#  define K_K 107
#  define K_O 111
#  define K_L 108

#  define K_NUM_4 65430
#  define K_NUM_6 65432
#  define K_NUM_8 65431
#  define K_NUM_2 65433
#  define K_NUM_MINUS 65453
#  define K_NUM_PLUS 65451
# else
#  define K_ESC 53
#  define K_UP 126
#  define K_DOWN 125
#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_P 35
#  define K_MINUS 27
#  define K_PLUS 24
#  define K_R 15
#  define K_U 32
#  define K_J 38
#  define K_I 34
#  define K_K 40
#  define K_O 31
#  define K_L 37

#  define K_NUM_4 86
#  define K_NUM_6 88
#  define K_NUM_8 91
#  define K_NUM_2 84
#  define K_NUM_MINUS 78
#  define K_NUM_PLUS 69
# endif

# include "stdlib.h"
# include "stdio.h"
# include "math.h"

# include <mlx.h>

# include <libft.h>
# include <get_next_line.h>
# include <ft_printf.h>

typedef struct s_color {
	int	color;
	int	a;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map_struct {
	int	**map;
	int	size_x;
	int	size_y;
	int rect_size_x;
	int rect_size_y;
	int height_mult;
	int pos_x;
	int pos_y;
	int	min_height;
	int	max_height;
}	t_map_struct;

typedef struct s_mlx_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_data;

/* This holds everything */
typedef struct s_fdf {
	t_mlx_data		*mlx_data;
	void			*mlx;
	void			*win;
	t_screen_info	*screen_info;
	char			*screen_title;
	t_map_struct	*map_struct;
}	t_fdf;

/* color */
t_color			*t_color_from_int(int color);
t_color			*t_color_from_argb(int a, int r, int g, int b);

/* parsing */
t_map_struct	*map_from_fd(const char *filename);
void			set_extremes(t_map_struct *map_struct);

/* mlx helpers */
void			my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);

/* drawing */
void			draw_line_dda(t_fdf *fdf, const int coords[4], int color);
void			draw_line_dda_colors(t_fdf *fdf, const int coords[4], int colors[2]);
void			fill_screen(t_fdf *fdf, int color);
void			draw_square(t_fdf *fdf, const int square_details[4], int color);
void			circle_bres(t_fdf *fdf, const int circle_details[3], int color);
void			draw_vect(t_fdf *fdf, t_vec3d *vect, int color);
void			connect_vects(t_fdf *fdf, t_vec3d *v1, t_vec3d *v2, int color);

void			draw_cube(t_fdf *fdf, t_plane3d *plane, int x, int y, int z, int size, int color);
void			draw_cube_orthogonal(t_fdf *fdf, t_plane3d *plane, int x, int y, int z, int size, int color);
void			draw_map(t_fdf *fdf);

/* other util */
void			print_title();
void			print_map(t_map_struct *map);
t_plane3d		*get_screen_plane(int width, int height, int spectator_distance);
t_screen_info	*screen_info_init();
void			*free_map_gnlstr(t_map_struct *map_struct, char *gnl_str);
void			free_map_members(t_map_struct *map_struct);
int				handle_keypress(int keycode, t_fdf *fdf);
t_fdf			*init_fdf(char *argv[]);
int				post_init(t_fdf *fdf, char *argv[]);
int				handle_args(int argc, char *argv[]);
int				destroy(t_fdf *fdf);

#endif
