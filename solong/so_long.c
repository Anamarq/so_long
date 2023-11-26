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

#include "MLX42/include/MLX42/MLX42.h"
#include "so_long.h"
// #include "ft_itoa.c"
// #include "reserve_memory.c"
// #include "check_map.c"
// #include "touch_object.c"
// #include "hook.c"
// #include "draw_map.c"
// #include "create_images.c"
// #include "get_next_line/get_next_line.c"
// #include "get_next_line/get_next_line_utils.c"

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	finish(t_info *i)
{
	int	c;

	mlx_delete_image(i->mlx, i->typ.wall);
	mlx_delete_image(i->mlx, i->typ.ext);
	mlx_delete_image(i->mlx, i->typ.chr[0]);
	mlx_delete_image(i->mlx, i->typ.chr[1]);
	mlx_delete_image(i->mlx, i->typ.chr[2]);
	mlx_delete_image(i->mlx, i->typ.chr[3]);
	mlx_delete_image(i->mlx, i->typ.chr[4]);
	mlx_delete_image(i->mlx, i->typ.object);
	mlx_delete_image(i->mlx, i->typ.nothing);
	mlx_delete_image(i->mlx, i->typ.ext_open);
	free(i->cordc);
	free(i->typ.chr);
	free(i->char_depth);
	mlx_terminate(i->mlx);
	c = 0;
	while (c < i->nrows)
	{
		free(i->map[c]);
		++c;
	}
	return (EXIT_SUCCESS);
}
// void	write_map(t_i *i)
// {
// 	for (int i = 0; i < i->nrows; ++i) {
// 		for (int j = 0; j < i->ncols; ++j) {
// 			write(1, &i->map[i][j], 1);
// 		}
// 		write(1, "\n", 1);
// 	}
// }

//x, y punto imagen arriba izquierda.
//x2, y2 punto imagen abajo derecha
//i
void	update_colec(t_info *i)
{
	int	c;

	c = 0;
	while (c < i->tot_col)
	{
		i->cordc[c].x_start = (i->typ.object->inst[c].x + 10) / BLOCK;
		i->cordc[c].y_start = (i->typ.object->inst[c].y + 10) / BLOCK;
		i->cordc[c].x_end = (i->typ.object->inst[c].x + BLOCK - 10) / BLOCK;
		i->cordc[c].y_end = (i->typ.object->inst[c].y + BLOCK - 10) / BLOCK;
		i->cordc[c].x = (i->cordc[c].x_start + i->cordc[c].x_end) / 2;
		i->cordc[c].y = (i->cordc[c].y_start + i->cordc[c].y_end) / 2;
		++c;
	}
}

void	initialize(t_info *i)
{
	i->tot_col = 0;
	i->catch_colecs = 0;
	i->total_exts = 0;
	i->init_pos = 0;
	i->nmov = 0;
	i->nsprite = 0;
	i->nrows = 1;
}
void leaks(void)
{
	system("leaks -q so_long");
}
//i es info pero he tenido q poner i por la tontería de norminette
int	main(int argc, char *argv[])
{
	t_info	i;

	if(argc < 2)
		return (0);
//	atexit(leaks);
	(void)argc;
	initialize(&i);
	if (check_map(argv[1], &i) == 1)
	{
		if (reserve_memory_chr(&i) != 1)
			return (0);
		i.mlx = mlx_init(i.ncols * BLOCK, i.nrows * BLOCK, "MLX42", true);
		if (!i.mlx)
			exit(EXIT_FAILURE);
		create_images(&i);
		if (reserve_memory_2d(&i) != 1)
			return (0);
		draw_map(argv[1], &i);
		update_colec(&i);
		mlx_loop_hook(i.mlx, &hook, &i);
		mlx_loop(i.mlx);
		return (finish(&i));
	}
	return (EXIT_SUCCESS);
}
