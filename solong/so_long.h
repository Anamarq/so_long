/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:59:32 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/05 11:59:33 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#pragma once
#ifndef SO_LONG_H
# define SO_LONG_H

//# include "libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# define BLOCK 50

typedef struct image
{
	mlx_image_t	*wall;
	mlx_image_t	**chr;
	mlx_image_t	*nothing;
	mlx_image_t	*object;
	mlx_image_t	*ext;
	mlx_image_t	*ext_open;
	mlx_image_t	*enemy;
	mlx_image_t	*mov;
}	t_image;

typedef struct coordinates
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int	x;
	int	y;
}	t_coords;

typedef struct info
{
	char		**map;
	int			ncols;
	int			nrows;
	t_coords	*cordc;
	int			tot_col;
	int			catch_colecs;
	int			total_exts;
	int			init_pos;
	t_image		typ;
	mlx_t		*mlx;
	int			nmov;
	int			nsprite;
	int			*char_depth;

}	t_info;

typedef struct coord_char
{
	int	x;
	int	y;
	int	x2;
	int	y2;
}	t_cord_char;

typedef struct draw_map_data
{
	int		i;
	int		j;
	int		xchar;
	int		ychar;
	char	*car;
}	t_draw_map_data;

void	error(void);
int		reserve_memory(t_info *info);
int		reserve_memory_2d(t_info *info);
int		reserve_memory_chr(t_info *info);
void	create_images(t_info *info);
void	touch_object(t_info *info);
int		check_map(char *route, t_info *info);
void	hook(void *param);
void	draw_map(char *route, t_info *info);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *string);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start,
			size_t len);
int		ft_ind(const char *str, char c);
char	*get_next_line(int fd);

#endif