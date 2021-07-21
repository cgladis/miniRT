/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:29:01 by cgladis           #+#    #+#             */
/*   Updated: 2021/05/02 17:40:09 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clear_vars(t_vars *vars)
{
	vars->read_a = 0;
	vars->read_r = 0;
	vars->no_camera = 1;
	vars->obj = NULL;
}

void	init_vars(t_vars *vars, char **arg)
{
	vars->mlx = mlx_init();
	vars->canva.background_color.color = BACKGROUND_COLOR;
	vars->canva.color.color = DEFAULT_COLOR;
	vars->canva.obj_color.color = DEFAULT_COLOR;
	vars->debug_win = NULL;
	vars->bmp = 0;
	vars->need_free = 0;
	vars->need_free_win = 0;
	vars->arg = arg;
	vars->potok = 0;
}

int	check_file_name(char *file_mame)
{
	int	len;

	len = ft_strlen(file_mame);
	if (len < 4)
		return (0);
	if (ft_strncmp(file_mame + len - 3, ".rt", 4) == 0)
		return (1);
	return (0);
}

void	main_sub(t_vars *vars, char *arg, int count)
{
	if (count > 3)
		error_and_exit("Неверное количество аргументов", vars);
	if (!check_file_name(arg))
		error_and_exit("Неверное имя файла (.rt)", vars);
	if (!import(vars, arg))
		error_and_exit("Ошибка при чтении файла", vars);
}

int	main(int count, char **arg)
{
	t_vars	vars;

	init_vars(&vars, arg);
	open_color_box(&vars);
	if (count < 2)
		error_and_exit("Нужно указать имя файла .rt или параметр --edit",
			&vars);
	if (*arg[1] == '-')
	{
		if (read_param(arg[1], "--edit"))
			edit_scene(&vars);
		else
			error_and_exit("Неверный параметр n1", &vars);
	}
	if (count == 3)
	{
		if (*arg[2] == '-')
		{
			if (read_param(arg[2], "--save"))
				vars.bmp = 1;
			else
				error_and_exit("Неверный параметр n2", &vars);
		}
	}
	main_sub(&vars, arg[1], count);
}
