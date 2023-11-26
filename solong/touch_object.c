/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:08:52 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/29 19:08:54 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Open door if(d->tot_col == d->catch_colecs)
void	open_dor(t_info *info)
{
	if (info->tot_col == info->catch_colecs)
	{
		write(1, "PUERTA ABIERTA :)\n", 19);
		mlx_set_instance_depth(&info->typ.ext->inst[0], -99);
		if (mlx_image_to_window(info->mlx, info->typ.ext_open,
				info->typ.ext->inst[0].x, info->typ.ext->inst[0].y) < 0)
			error();
	}
}

//Touch obstacle
// (catch colects) bayas
void	touch_obstacle(t_info *d, t_cord_char c, int i)
{
	if (d->map[c.y][c.x] == 'C' || d->map[c.y2][c.x2] == 'C')
	{
		i = 0;
		while (i < d->tot_col
			&& (d->map[c.y][c.x] == 'C' || d->map[c.y2][c.x2] == 'C'
				|| d->map[c.y][c.x2] == 'C' || d->map[c.y2][c.x] == 'C'))
		{
			if (d->cordc[i].x_start >= c.x && d->cordc[i].y_start >= c.y
				&& d->cordc[i].x_end <= c.x2 && d->cordc[i].y_end <= c.y2)
			{
				write(1, "Que baya más rica ! :)'\n", 26);
				mlx_set_instance_depth(&d->typ.object->inst[i], -99);
				++d->catch_colecs;
				d->map[d->cordc[i].y][d->cordc[i].x] = '0';
				open_dor(d);
			}
			++i;
		}	
	}
}

//si toca un enemigo
void	touch_enemy(t_info *d, t_cord_char *c)
{
	if (d->map[c->y][c->x] == 'X' || d->map[c->y2][c->x2] == 'X')
	{
		write(1, "NOOOOO!! pikachu te ha debilitado con un rayo. :(\n", 50);
		mlx_close_window(d->mlx);
	}
}

//If you touch the door and have all collecs
//Also shows number of movements in terminal
void	finish_game(t_info *d, t_cord_char *c)
{
	char		*chr;

	if (d->map[c->y][c->x] == 'E' || d->map[c->y2][c->x2] == 'E')
	{
		if (d->tot_col == d->catch_colecs)
		{
			write(1, "OLE! Conseguiste salir!!Bien hecho :O.Has tardado ", 51);
			chr = ft_itoa(d->nmov);
			write(1, chr, ft_strlen(chr));
			free(chr);
			write(1, " movimientos!Eso está regular. Puedes mejorarlo?\n", 51);
			mlx_close_window(d->mlx);
		}
	}
}

//For obstacle
//c.x, c.y image top left. 
//c.x2, c.y2 image bottom right
void	touch_object(t_info	*d)
{
	t_cord_char	c;
	int			i;

	i = 0;
	c.x = (d->typ.chr[d->nsprite]->inst[0].x + 30) / BLOCK;
	c.y = (d->typ.chr[d->nsprite]->inst[0].y + 30) / BLOCK;
	c.x2 = (d->typ.chr[d->nsprite]->inst[0].x + BLOCK - 30) / BLOCK;
	c.y2 = (d->typ.chr[d->nsprite]->inst[0].y + BLOCK - 30) / BLOCK;
	touch_obstacle(d, c, i);
	touch_enemy(d, &c);
	finish_game(d, &c);
}
