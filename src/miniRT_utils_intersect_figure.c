/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_intersect_figure.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:12:34 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/29 00:10:22 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_t_cylinder(double t[2], t_coordinates vector_point, t_obj *obj,
					  t_coordinates sub)
{
	double			m1;
	double			m2;

	m1 = scalar_product(vector_point, obj->vector_3d) * t[0]
		+ scalar_product(sub, obj->vector_3d);
	m2 = scalar_product(vector_point, obj->vector_3d) * t[1]
		+ scalar_product(sub, obj->vector_3d);
	if (t[0] < t[1])
	{
		if (m1 >= 0 && m1 <= obj->size2 && t[0] >= 0)
			return (t[0]);
		else if (m2 >= 0 && m2 <= obj->size2 && t[1] >= 0)
			return (t[1]);
	}
	else if (t[0] > t[1])
	{
		if (m2 >= 0 && m2 <= obj->size2 && t[1] >= 0)
			return (t[1]);
		else if (m1 >= 0 && m1 <= obj->size2 && t[0] >= 0)
			return (t[0]);
	}
	return (0);
}

double	intersect_ray_cylinder(t_coordinates camera, t_coordinates vector_point,
							  t_obj *obj)
{
	double			k[3];
	t_coordinates	sub;
	double			d;
	double			t[2];

	k[0] = scalar_product(vector_point, vector_point) - pow(scalar_product(
				vector_point, obj->vector_3d), 2);
	sub = minus_vector(camera, obj->xyz);
	k[1] = 2 * (scalar_product(vector_point, sub) - (scalar_product(
					vector_point, obj->vector_3d) * scalar_product(sub,
					obj->vector_3d)));
	k[2] = scalar_product(sub, sub) - pow(scalar_product(sub, obj->vector_3d),
			2)
		- pow(obj->size1 / 2, 2);
	d = k[1] * k[1] - (4 * k[0] * k[2]);
	if (d < 0)
		return (0);
	t[0] = (-k[1] - sqrt(d)) / (2 * k[0]);
	t[1] = (-k[1] + sqrt(d)) / (2 * k[0]);
	return (get_t_cylinder(t, vector_point, obj, sub));
}

double	intersect_ray_plane(t_coordinates camera, t_coordinates vector_point,
						   t_obj *obj)
{
	double	k1;
	double	k2;
	double	t1;

	k1 = scalar_product(minus_vector(obj->xyz, camera), obj->vector_3d);
	k2 = scalar_product(vector_point, obj->vector_3d);
	t1 = k1 / k2;
	if (t1 < 0)
		return (0);
	return (t1);
}
