/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:29:01 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/29 11:39:57 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	error_and_exit(const char *str, t_vars *vars)
{
	free_vars(vars);
	printf("Error\n%s\n", str);
	exit (0);
}

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_coordinates	norm_vector_obj(int x, int y, t_vars *vars)
{
	t_coordinates	result;
	t_coordinates	point_vector;

	point_vector = coordinates(x - vars->canva.x / 2, y - vars->canva.y / 2,
			calc_length_to_canva(vars->current_camera->size1, vars->canva.x));
	result = rotate_vector_v1(point_vector, vars);
	return (result);
}

void	view_scene(t_vars *vars)
{
	vars->need_free_win = 1;
	vars->img = mlx_new_image(vars->mlx, vars->canva.x, vars->canva.y);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	if (vars->bmp)
		save_bmp(vars);
	vars->win = mlx_new_window(vars->mlx, vars->canva.x, vars->canva.y,
			"miniRT");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_hook(vars->win, 17, 1L << 17, close_w, vars);
	mlx_hook(vars->win, 2, 1L << 0, edit_functions, vars);
	mlx_hook(vars->win, 5, 1L << 0, release_mouse_key, vars);
	mlx_hook(vars->win, 4, 1L << 0, push_mouse_key, vars);
	mlx_loop_hook(vars->mlx, loop_hook, vars);
	printf("view_scene OK\n");
	mlx_loop(vars->mlx);
}

void	edit_scene(t_vars *vars)
{
	vars->canva.x = DEFAULT_X;
	vars->canva.y = DEFAULT_Y;
	vars->canva.ambient = 0.1;
	vars->canva.color.color = DEFAULT_COLOR;
	vars->obj = new_camera(NULL, (t_param_obj){
			coordinates(0, 0, 0), coordinates(0,
				0, 0), coordinates(0, 0, 0),
			coordinates(0, 0, 1),
			DEFAULT_FOV, 0, new_color(0, 0, 0)}, vars);
	vars->current_camera = vars->obj->content;
	vars->mode = 2;
	view_scene(vars);
}
