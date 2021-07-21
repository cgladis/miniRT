/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_normal_lighting.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:12:46 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/28 21:28:26 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	light_plane(t_vars *vars, t_obj *obj, t_coordinates p)
{
	t_coordinates	v;
	double			k;

	k = scalar_product(obj->vector_3d, norm_vector(minus_vector(vars
					->current_camera->xyz, p)));
	if (k <= 0)
		v = norm_vector(vector_na_chislo(obj->vector_3d, -1));
	else
		v = obj->vector_3d;
	return (v);
}

t_coordinates	light_triangle(t_vars *vars, t_obj *obj, t_coordinates p)
{
	t_coordinates	ab;
	t_coordinates	bc;
	t_coordinates	v;
	double			k;

	ab = minus_vector(obj->xyz, obj->xyz2);
	bc = minus_vector(obj->xyz2, obj->xyz3);
	v = norm_vector(multi_vector(ab, bc));
	k = scalar_product(v, norm_vector(minus_vector(vars->current_camera
					->xyz, p)));
	if (k <= 0)
		v = vector_na_chislo(v, -1);
	return (v);
}

t_coordinates	light_square(t_vars *vars, t_obj *obj, t_coordinates p)
{
	t_coordinates	v;
	double			k;

	k = scalar_product(obj->vector_3d, norm_vector(minus_vector(vars
					->current_camera->xyz, p)));
	if (k <= 0)
		v = norm_vector(vector_na_chislo(obj->vector_3d, -1));
	else
		v = obj->vector_3d;
	return (v);
}

t_coordinates	light_cylinder(t_vars *vars, t_obj *obj, t_coordinates p)
{
	double			length;
	t_coordinates	ray;
	t_coordinates	v;
	double			m;

	length = vector_length(minus_vector(vars->current_camera->xyz, p));
	ray = norm_vector(minus_vector(p, vars->current_camera->xyz));
	m = scalar_product(ray, obj->vector_3d) * length
		+ scalar_product(minus_vector(vars->current_camera->xyz, obj->xyz),
			obj->vector_3d);
	v = norm_vector(minus_vector(minus_vector(p, obj->xyz),
				vector_na_chislo(obj->vector_3d, m)));
	if (scalar_product(ray, v) < 0)
		return (v);
	return (vector_na_chislo(v, -1));
}
