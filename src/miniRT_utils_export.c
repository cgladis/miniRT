/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:12:16 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/29 09:33:48 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*delete_n(char *str)
{
	while (*str != '\n' && *str != '\0')
		str++;
	*str = '\0';
	return (str);
}

char	*delete_str(char *str, char *c)
{
	char	*ptr;
	int		flag;

	while (*str)
	{
		flag = 0;
		ptr = c;
		while (*ptr)
		{
			if (*str == *ptr)
				flag = 1;
			ptr++;
		}
		if (!flag)
			return (str);
		str++;
	}
	return (str);
}

void	export_sub(int fd, t_list *list_obj)
{
	t_obj	*obj;

	obj = list_obj->content;
	if (obj->identifier == 0)
		write_camera(fd, obj);
	if (obj->identifier == 1)
		write_sphere(fd, obj);
	if (obj->identifier == 2)
		write_plane(fd, obj);
	if (obj->identifier == 3)
		write_triangle(fd, obj);
	if (obj->identifier == 4)
		write_squere(fd, obj);
	if (obj->identifier == 5)
		write_cylinder(fd, obj);
	if (obj->identifier == 9)
		write_light(fd, obj);
}

void	export(t_vars *vars, char *file_name)
{
	int		fd;
	t_list	*list_obj;

	list_obj = vars->obj;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd > 1)
	{
		write_resolution(fd, vars->canva.x, vars->canva.y);
		write_ambient(fd, vars->canva.ambient, vars->canva.color);
		while (list_obj)
		{
			export_sub(fd, list_obj);
			list_obj = list_obj->next;
		}
		close(fd);
	}
	else if (fd == 1)
	{
		close(fd);
		printf("file error\n");
	}
	else
		printf("file error\n");
	return ;
}
