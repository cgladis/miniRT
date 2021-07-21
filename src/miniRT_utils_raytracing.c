/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_raytracing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:13:01 by cgladis           #+#    #+#             */
/*   Updated: 2021/05/03 15:49:28 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_closest_obj	closest_intersection(t_coordinates camera,
				t_coordinates ray, t_ray_tracing *data, t_t_minmax t_minmax)
{
	t_obj			*obj;
	double			t;
	t_list			*list_obj;
	t_closest_obj	closest_obj;

	closest_obj.obj = NULL;
	closest_obj.closest_t = __DBL_MAX__;
	list_obj = data->vars->obj;
	while (list_obj)
	{
		obj = list_obj->content;
		t = get_t(obj, ray, camera);
		if (t > t_minmax.t_min && t < t_minmax.t_max
			&& t < closest_obj.closest_t)
		{
			closest_obj.obj = obj;
			closest_obj.closest_t = t;
		}
		list_obj = list_obj->next;
	}
	return (closest_obj);
}

t_color	compute_lighting_sub_get_color(t_color color, t_obj *lighting,
								t_ray_tracing *data, t_coordinates l)
{
	double	n_dot_l;
	double	tempi;

	tempi = 0;
	n_dot_l = scalar_product(data->normal, norm_vector(l));
	if (n_dot_l > 0)
		tempi = lighting->size1 * n_dot_l;
	color = add_color(color, multi_color(color, lighting->rgb, tempi));
	return (color);
}

void	compute_lighting_sub_trace_obj(t_trace_obj	*trace_obj,
									t_ray_tracing *data, t_obj *lighting)
{
	trace_obj->obj = lighting;
	trace_obj->l = minus_vector(lighting->xyz, data->p);
	trace_obj->shaddow_obj = closest_intersection(data->p, trace_obj->l,
			data, (t_t_minmax){0.1, 1});
	ft_lstadd_back(&data->lights, ft_lstnew(trace_obj));
}

t_color	compute_lighting_sub(t_color color, t_ray_tracing *data)
{
	t_obj		*lighting;
	t_list		*list_obj;
	t_trace_obj	*trace_obj;

	list_obj = data->vars->obj;
	while (list_obj)
	{
		lighting = list_obj->content;
		if (lighting->identifier == 9)
		{
			trace_obj = (t_trace_obj *)malloc(sizeof(t_trace_obj));
			compute_lighting_sub_trace_obj(trace_obj, data, lighting);
			if (trace_obj->shaddow_obj.obj != NULL)
			{
				list_obj = list_obj->next;
				continue ;
			}
			color = compute_lighting_sub_get_color(color, lighting, data,
					trace_obj->l);
		}
		list_obj = list_obj->next;
	}
	return (color);
}

t_color	compute_lighting(t_ray_tracing *data, t_obj *obj)
{
	t_color			color;

	color.color = BACKGROUND_COLOR;
	color = compute_lighting_sub(color, data);
	color = multi_color(color, data->vars->canva.color,
			data->vars->canva.ambient);
	color = gradient(color, obj->rgb);
	return (color);
}
