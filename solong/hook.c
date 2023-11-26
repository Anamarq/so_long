/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:23:34 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/29 19:23:35 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//0 frente
//1: arriba
//2: abajo
//3: izq
//4 der
//if (info->nsprite != n) activar nuevo sprite y poner la pos
//mostrar MOVS (2 ultimas lineas)

void	update_mov(t_info *info, int n)
{
	char	*str;

	if (info->nsprite != n)
	{
		mlx_set_instance_depth(&info->typ.chr[info->nsprite]->inst[0], -100);
		mlx_set_instance_depth(&info->typ.chr[n]->inst[0], info->char_depth[n]);
		info->typ.chr[n]->inst[0].y = info->typ.chr[info->nsprite]->inst[0].y;
		info->typ.chr[n]->inst[0].x = info->typ.chr[info->nsprite]->inst[0].x;
	}
	info->nsprite = n;
	++info->nmov;
	mlx_delete_image(info->mlx, info->typ.mov);
	str = ft_itoa(info->nmov);
	info->typ.mov = mlx_put_string(info->mlx, str, 120, 10);
	free(str);
}

void	key_pressed2(t_info *info, t_cord_char c)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT)
		&& info->map[c.y2][c.x2 - 1] != '1' && info->map[c.y][c.x] != '1')
	{
		update_mov(info, 3);
		info->typ.chr[info->nsprite]->inst[0].x -= BLOCK / 10;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT)
		&& info->map[c.y][c.x + 1] != '1' && info->map[c.y2][c.x2] != '1')
	{
		update_mov(info, 4);
		info->typ.chr[info->nsprite]->inst[0].x += BLOCK / 10;
	}	
}

void	key_pressed(t_info *info, t_cord_char c)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_UP)
		&& info->map[c.y2 - 1][c.x2] != '1' && info->map[c.y][c.x] != '1')
	{
		update_mov(info, 1);
		info->typ.chr[info->nsprite]->inst[0].y -= BLOCK / 10;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_DOWN)
		&& info->map[c.y + 1][c.x] != '1' && info->map[c.y2][c.x2] != '1')
	{
		update_mov(info, 2);
		info->typ.chr[info->nsprite]->inst[0].y += BLOCK / 10;
	}
	key_pressed2(info, c);
}
//x, y punto imagen arriba izquierda.
//x2, y2 punto imagen abajo derecha 

void	hook(void *param)
{
	t_info		*i;
	t_cord_char	c;

	i = param;
	c.x = (i->typ.chr[i->nsprite]->inst[0].x) / BLOCK;
	c.y = (i->typ.chr[i->nsprite]->inst[0].y) / BLOCK;
	c.x2 = (i->typ.chr[i->nsprite]->inst[0].x + BLOCK - 1) / BLOCK;
	c.y2 = (i->typ.chr[i->nsprite]->inst[0].y + BLOCK - 1) / BLOCK;
	key_pressed(i, c);
	touch_object(i);
}
//printf(" x = %i, y= %i , obs = %c\n", x,y, info->map[y][x]);