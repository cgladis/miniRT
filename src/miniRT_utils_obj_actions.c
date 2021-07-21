/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:31:59 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/28 21:22:37 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_obj(t_vars *vars)
{
	char	str[50];
	t_obj	*obj;
	t_list	*list;

	list = vars->obj;
	printf("номер	объект	координаты			направление\n");
	while (list)
	{
		obj = list->content;
		if (obj->identifier == 1 || obj->identifier == 9)
			printf("%d	%s	%8.2f,%8.2f,%8.2f\n", obj->number, get_name_obj(
					obj->identifier, str), obj->xyz.x, obj->xyz.y, obj->xyz.z);
		else
			printf("%d %s	%8.2f,%8.2f,%8.2f		%8.2f,%8.2f,%8.2f\n", obj
				->number, get_name_obj(obj->identifier, str),
				obj->xyz.x, obj->xyz.y, obj->xyz.z,
				obj->vector_3d.x, obj->vector_3d.y, obj->vector_3d.z);
		list = list->next;
	}
}

void	remove_content(void *obj)
{
	free(obj);
}

t_list	*get_last_obj(int number, t_vars *vars, t_list *list_obj,
					 t_list *last_obj)
{
	if (number == 0)
	{
		vars->obj = list_obj->next;
		last_obj = vars->obj;
	}
	else
		last_obj->next = list_obj->next;
	last_obj = last_obj->next;
	return (last_obj);
}

t_list	*get_last_obj2(int number, t_list *last_obj, t_obj	*obj)
{
	int		i;

	i = number;
	while (last_obj)
	{
		obj = last_obj->content;
		obj->number = i;
		last_obj = last_obj->next;
		i++;
	}
	return (last_obj);
}

void	remove_obj(int number, t_vars *vars)
{
	t_obj	*obj;
	t_list	*last_obj;
	t_list	*list_obj;

	list_obj = vars->obj;
	last_obj = list_obj;
	while (list_obj)
	{
		obj = list_obj->content;
		if (obj->number == number)
		{
			last_obj = get_last_obj(number, vars, list_obj, last_obj);
			last_obj = get_last_obj2(number, last_obj, obj);
			ft_lstdelone(list_obj, remove_content);
			return ;
		}
		last_obj = list_obj;
		list_obj = list_obj->next;
	}
}
