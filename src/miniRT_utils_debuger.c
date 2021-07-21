/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_debuger.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:12:08 by cgladis           #+#    #+#             */
/*   Updated: 2021/05/03 17:21:53 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	debug(t_vars *vars)
{
	vars->debug_win = mlx_new_window(vars->mlx, 900, 300, "Debuger");
	mlx_hook(vars->debug_win, 2, 1L << 0, edit_functions, vars);
}

void	wtite_block_1(t_ray_tracing *data, t_vars *vars)
{
	char	*str;

	str = ft_cont_str(ft_strdup("x = "), rt_get_int(data->x));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(" y = ")), rt_get_int(data
				->y));
	mlx_string_put(vars->mlx, vars->debug_win, 10, 20, 0xffffff, str);
	free(str);
	str = ft_cont_str(ft_strdup("camera - "), rt_get_int(vars->current_camera
				->number));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(": ")), rt_get_coordinates(vars
				->current_camera->xyz));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(" vector: ")),
			rt_get_coordinates(vars->current_camera->vector_3d));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(" FOV: ")), ft_get_float(vars
				->current_camera->size1, 2));
	mlx_string_put(vars->mlx, vars->debug_win, 10, 40, 0xffffff, str);
	free(str);
	str = ft_cont_str(ft_strdup("ray: "), rt_get_coordinates(data->ray));
	mlx_string_put(vars->mlx, vars->debug_win, 10, 60, 0xffffff, str);
	free(str);
}

void	wtite_block_2(t_ray_tracing *data, t_vars *vars)
{
	char	*str;
	char	name_obj[50];

	if (data->closest_obj.obj == NULL)
		return ;
	name_obj[0] = '\0';
	get_name_obj(data->closest_obj.obj->identifier, name_obj);
	str = ft_cont_str(ft_strdup("obj: "), ft_strdup(name_obj));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(" ")), rt_get_int(data
				->closest_obj.obj->number));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(" cross_point: ")),
			rt_get_coordinates(data->p));
	str = ft_cont_str(ft_cont_str(str, ft_strdup(" normal: ")),
			rt_get_coordinates(data->normal));
	mlx_string_put(vars->mlx, vars->debug_win, 10, 80, 0xffffff, str);
	free(str);
}

void	wtite_block_3(t_ray_tracing *data, t_vars *vars, int i)
{
	t_list		*ptr;
	t_trace_obj	*obj;
	char		*str;
	char		str1[50];

	ptr = data->lights;
	while (ptr)
	{
		obj = ptr->content;
		str = ft_cont_str(ft_cont_str(ft_cont_str(ft_strdup("light: "),
						rt_get_int(obj->obj->number)), ft_strdup(" | l: ")),
				rt_get_coordinates(obj->l));
		if (obj->shaddow_obj.obj)
		{
			get_name_obj(obj->shaddow_obj.obj->identifier, str1);
			str = ft_cont_str(ft_cont_str(ft_cont_str(str, ft_strdup(
								" shad obj: ")), ft_strdup(str1)), rt_get_int(
						obj->shaddow_obj.obj->number));
		}
		mlx_string_put(vars->mlx, vars->debug_win, 10, i, 0xffffff, str);
		free(str);
		ptr = ptr->next;
		i += 20;
	}
}

void	refresh_debug_win(t_vars *vars)
{
	t_ray_tracing	data;

	mlx_clear_window(vars->mlx, vars->debug_win);
	mlx_mouse_get_pos(vars->win, &data.x, &data.y);
	if (data.x < 0 || data.y < 0 || data.x >= vars->canva.x || data.y
		>= vars->canva.y)
		return ;
	data.vars = vars;
	trace_ray(data.x, data.y, &data);
	wtite_block_1(&data, vars);
	wtite_block_2(&data, vars);
	wtite_block_3(&data, vars, 110);
	clear_ray_tracing_data(&data);
}
