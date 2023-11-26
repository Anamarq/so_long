/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:02:53 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/29 20:02:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*create_img(mlx_t	*mlx, char *route)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(route);
	if (!texture)
		error();
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error();
	mlx_delete_texture(texture);
	return (img);
}

void	create_images(t_info *info)
{
	info->typ.wall = create_img(info->mlx, "./sprites/wall.png");
	info->typ.chr[0] = create_img(info->mlx, "./sprites/piplupSit.png");
	info->typ.chr[1] = create_img(info->mlx, "./sprites/piplupBack.png");
	info->typ.chr[2] = create_img(info->mlx, "./sprites/piplupFront.png");
	info->typ.chr[3] = create_img(info->mlx, "./sprites/piplupLeft.png");
	info->typ.chr[4] = create_img(info->mlx, "./sprites/piplupRight.png");
	info->typ.object = create_img(info->mlx, "./sprites/baya.png");
	info->typ.nothing = create_img(info->mlx, "./sprites/snow4.png");
	info->typ.ext = create_img(info->mlx, "./sprites/pokeball.png");
	info->typ.enemy = create_img(info->mlx, "./sprites/pikachu.png");
	info->typ.ext_open = create_img(info->mlx, "./sprites/open.png");
}
