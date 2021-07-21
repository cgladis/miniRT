/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:32:22 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/28 22:37:19 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_list	*new_square(t_list *list_obj, t_param_obj square, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 4;
	obj->xyz = square.coordinates;
	obj->vector_3d = norm_vector(square.vector_3d);
	obj->size1 = square.size1;
	obj->rgb = square.color;
	return (ft_lstnew(obj));
}

t_list	*new_cylinder(t_list *list_obj, t_param_obj cylinder, t_vars *vars)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->number = get_number_obj(list_obj, vars);
	obj->identifier = 5;
	obj->xyz = cylinder.coordinates;
	obj->vector_3d = norm_vector(cylinder.vector_3d);
	obj->size1 = cylinder.size1;
	obj->size2 = cylinder.size2;
	obj->rgb = cylinder.color;
	return (ft_lstnew(obj));
}
