/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:17:42 by anamarqu          #+#    #+#             */
/*   Updated: 2022/12/29 18:17:48 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	read_medium_lines(char *car, t_info *info, int *i)
{
	while (car[*i] != '\0')
	{
		if (car[*i] == 'E')
			++info->total_exts;
		else if (car[*i] == 'P')
			++info->init_pos;
		else if (car[*i] == 'C')
			++info->tot_col;
		else if (car[*i] != '0' && car[*i] != '1'
			&& car[*i] != 'X' && car[*i] != '\n')
		{
			write(1, "Error\nDATOS ERRONEOS DEL MAPA \n", 32);
			return (-1);
		}
		++*i;
	}
	--*i;
	return (1);
}

int	read_next_lines(char *car, t_info *info, char *next, int *i)
{
	if (next == NULL)
	{
		while (car[*i] != '\0')
		{
			if (car[*i] != '1')
			{
				write(1, "Error\nDATOS ERRONEOS DEL MAPA \n", 32);
				return (-1);
			}
			++*i;
		}
		return (1);
	}
	else
	{
		if (read_medium_lines(car, info, i) < 0)
			return (-1);
	}
	return (1);
}

int	read_lines(int fd, char *car, t_info *info)
{
	char	*next;
	int		i;

	i = 0;
	while (car != NULL)
	{
		next = get_next_line(fd);
		if (read_next_lines(car, info, next, &i) < 0)
			return (-1);
		if (info->ncols != i || car[0] != '1' || car[i - 1] != '1')
		{
			write(1, "Error\nDATOS ERRONEOS DEL MAPA \n", 32);
			return (-1);
		}
		i = 0;
		++info->nrows;
		free(car);
		car = next;
	}
	free(car);
	return (1);
}

//First line of 1s, and call readLines
//Get next line for first row and for second
int	read_lines1(t_info *in, char *route)
{
	int		fd;
	char	*car;
	int		i;

	fd = open(route, O_RDONLY);
	i = 0;
	if (fd > 0)
	{
		car = get_next_line(fd);
		while (car[i + 1] != '\0')
		{
			if (car[i] != '1')
			{
				write(1, "Error\nDATOS ERRONEOS DEL MAPA \n", 32);
				return (-1);
			}
			++i;
		}
		in->ncols = i;
		free(car);
		car = get_next_line(fd);
		if (read_lines(fd, car, in) < 0)
			return (-1);
	}
	return (1);
}

int	check_map(char *route, t_info *in)
{
	int		i;
	char	*str2;

	i = ft_ind(route, '.');
	str2 = ".ber";
	if (! (route[i] == str2[0] && route[i + 1] == str2[1]
			&& route[i + 2] == str2[2] && route[i + 3] == str2[3]
			&& route[i + 4] == '\0'))
	{
		write(1, "Error\nLa extensión ha de ser .ber \n", 34);
		return (-1);
	}
	if (read_lines1(in, route) < 0)
		return (-1);
	if ((in->init_pos == 0) || (in->total_exts == 0) || (in->tot_col == 0))
	{
		write(1, "Error\nDATOS ERRONEOS DEL MAPA \n", 32);
		return (-1);
	}
	return (1);
}
