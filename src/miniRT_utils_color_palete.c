/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_color_palete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:11:59 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/29 03:43:06 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	fill_color(t_vars *vars)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	while (i < 400)
	{
		j = 0;
		while (j < 150)
		{
			color = ((i / 50) + (j / 50) * 8) * (0xffffff / 23);
			mlx_pixel_put(vars->mlx, vars->color_box, i, j, color);
			j++;
		}
		i++;
	}
}

int	push_mouse_key_on_color(int keycode, int x, int y, t_vars *vars)
{
	if (keycode != 1)
		return (1);
	vars->canva.obj_color.color = ((x / 50) + (y / 50) * 8) * (0xffffff / 23);
	printf("color = %06x\n", vars->canva.obj_color.color);
	return (1);
}

int	close_color_box(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->color_box);
	open_color_box(vars);
	return (1);
}

void	open_color_box(t_vars *vars)
{
	vars->color_box = mlx_new_window(vars->mlx, 400, 150, "ColorBox");
	fill_color(vars);
	mlx_hook(vars->color_box, 4, 1L << 0, push_mouse_key_on_color, vars);
	mlx_hook(vars->color_box, 17, 1L << 17, close_color_box, vars);
	mlx_hook(vars->color_box, 2, 1L << 0, edit_functions, vars);
}
