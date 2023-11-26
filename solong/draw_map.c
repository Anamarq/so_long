/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:26:34 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/29 19:26:35 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//dibujar el personaje al final
void	draw_chr(t_info *i, int xchar, int ychar)
{
	if (mlx_image_to_window(i->mlx, i->typ.chr[0], xchar * 50, ychar * 50) < 0)
		error();
	i->char_depth[0] = i->typ.chr[0]->inst[0].z;
	if (mlx_image_to_window(i->mlx, i->typ.chr[1], xchar * 50, ychar * 50) < 0)
		error();
	i->char_depth[1] = i->typ.chr[1]->inst[0].z;
	mlx_set_instance_depth(&i->typ.chr[1]->inst[0], -100);
	if (mlx_image_to_window(i->mlx, i->typ.chr[2], xchar * 50, ychar * 50) < 0)
		error();
	i->char_depth[2] = i->typ.chr[2]->inst[0].z;
	mlx_set_instance_depth(&i->typ.chr[2]->inst[0], -100);
	if (mlx_image_to_window(i->mlx, i->typ.chr[3], xchar * 50, ychar * 50) < 0)
		error();
	i->char_depth[3] = i->typ.chr[3]->inst[0].z;
	mlx_set_instance_depth(&i->typ.chr[3]->inst[0], -100);
	if (mlx_image_to_window(i->mlx, i->typ.chr[4], xchar * 50, ychar * 50) < 0)
		error();
	i->char_depth[4] = i->typ.chr[4]->inst[0].z;
	mlx_set_instance_depth(&i->typ.chr[4]->inst[0], -100);
}

void	show_images(t_info *in, int i, int j, char *car)
{
	if (mlx_image_to_window(in->mlx, in->typ.nothing, i * 50, j * 50) < 0)
		error();
	if (car[i] == '1')
	{
		if (mlx_image_to_window(in->mlx, in->typ.wall, i * 50, j * 50) < 0)
			error();
	}
	else if (car[i] == 'C')
	{
		if (mlx_image_to_window(in->mlx, in->typ.object, i * 50, j * 50) < 0)
			error();
	}
	else if (car[i] == 'E')
	{
		if (mlx_image_to_window(in->mlx, in->typ.ext, i * 50, j * 50) < 0)
			error();
	}
	else if (car[i] == 'X')
	{
		if (mlx_image_to_window(in->mlx, in->typ.enemy, i * 50, j * 50) < 0)
			error();
	}
	in->map[j][i] = car[i];
}

void	draw_map2(t_info *info, t_draw_map_data *d)
{
	d->i = 0;
	while (d->car[d->i] != '\0')
	{
		show_images(info, d->i, d->j, d->car);
		if (d->car[d->i] == 'P')
		{
			d->xchar = d->i;
			d->ychar = d->j;
		}
		++d->i;
	}
	++d->j;
	free(d->car);
}

//Posición del personaje: xchay ychar
void	draw_map(char *route, t_info *info)
{
	int				fd;
	t_draw_map_data	d;

	fd = open(route, O_RDONLY);
	d.j = 0;
	d.xchar = 0;
	d.ychar = 0;
	if (fd > 0)
	{
		d.car = get_next_line(fd);
		while (d.car != NULL)
		{
			draw_map2(info, &d);
			d.car = get_next_line(fd);
		}
		free(d.car);
		draw_chr(info, d.xchar, d.ychar);
	}
	mlx_put_string(info->mlx, "movement: ", 20, 10);
	info->typ.mov = mlx_put_string(info->mlx, "0", 120, 10);
}
