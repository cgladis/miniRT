/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_import.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:12:26 by cgladis           #+#    #+#             */
/*   Updated: 2021/05/03 16:59:07 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_obj(char *str, t_vars *vars)
{
	int	identifier;
	int	err;

	identifier = define_obj(str);
	if (identifier < 0)
		return (0);
	if (identifier == 255)
		err = read_ambient(str, vars);
	if (identifier == 254)
		err = read_resolution(str, vars);
	if (identifier == 0)
		err = read_camera(str, vars);
	if (identifier == 1)
		err = read_sphere(str, vars);
	if (identifier == 2)
		err = read_plane(str, vars);
	if (identifier == 3)
		err = read_triangle(str, vars);
	if (identifier == 4)
		err = read_square(str, vars);
	if (identifier == 5)
		err = read_cylinder(str, vars);
	if (identifier == 9)
		err = read_light(str, vars);
	return (err);
}

int	import_sub_sub(char *str, t_vars *vars, int *i)
{
	if (ft_strlen(str) > 0)
	{
		if (!create_obj(str, vars))
		{
			printf("Error in line %d\n", *i + 1);
			free (str);
			return (0);
		}
	}
	free (str);
	return (1);
}

int	import_sub(int fd, t_vars *vars)
{
	int		i;
	char	*str;

	i = 0;
	if (read(fd, NULL, 0) < 0)
		error_and_exit("Не могу открыть папку", vars);
	while (get_next_line(fd, &str) > 0)
	{
		if (!import_sub_sub(str, vars, &i))
			return (0);
		i++;
	}
	if (!import_sub_sub(str, vars, &i))
		return (0);
	close(fd);
	return (1);
}

int	import(t_vars *vars, char *file_name)
{
	int		fd;

	free_vars(vars);
	clear_vars(vars);
	fd = open(file_name, O_RDONLY);
	if (fd > 1)
	{
		if (!import_sub(fd, vars))
			return (0);
	}
	else
		error_and_exit("Не могу открыть файл", vars);
	if (vars->obj == NULL)
		error_and_exit("Нет объектов для вывода", vars);
	if (vars->no_camera)
		error_and_exit("Нет камеры", vars);
	vars->mode = 2;
	print_obj(vars);
	vars->current_obj = last_obj(vars->obj);
	view_scene(vars);
	return (1);
}
