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

t_color	*t_color_from_int(int color);
t_color	*t_color_from_argb(int a, int r, int g, int b);

t_map	*map_from_fd(const char *filename);

#endif
