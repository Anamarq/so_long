/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:32:17 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/29 19:32:18 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	reserve_memory_chr(t_info *info)
{
	info->typ.chr = malloc(5 * sizeof(mlx_image_t *));
	if (info->typ.chr == NULL)
	{
		free(info->typ.chr);
		return (0);
	}
	info->char_depth = malloc(5 * sizeof(int));
	if (info->char_depth == NULL)
	{
		free(info->char_depth);
		return (0);
	}
	return (1);
}

int	reserve_coordc(t_info *info)
{
	info->cordc = malloc(info->tot_col * sizeof(t_coords));
	if (info->cordc == NULL)
	{
		free(info->cordc);
		return (0);
	}
	return (1);
}

int	reserve_memory_2d(t_info *info)
{
	int	i;

	info->map = (char **)malloc(info->nrows * sizeof(char *));
	if (info->map == NULL)
	{
		free(info->map);
		return (0);
	}
	i = 0;
	while (i < info->nrows)
	{
		info->map[i] = (char *)malloc(info->ncols * sizeof(char));
		if (info->map[i] == NULL)
		{
			free(info->map[i]);
			return (0);
		}
		++i;
	}
	if (reserve_coordc(info) == 0)
		return (0);
	return (1);
}
