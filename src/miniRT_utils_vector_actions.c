/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_vector_actions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:13:22 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/28 19:47:05 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	get_matrix(t_coordinates vector)
{
	t_matrix	result;

	result.cos_x = scalar_product(vector, coordinates(0, 0, 1));
	result.sin_x = sin(acos(result.cos_x));
	result.cos_y = scalar_product(vector, coordinates(0, 0, 1));
	result.sin_y = sin(acos(result.cos_y));
	result.cos_z = scalar_product(vector, coordinates(0, 0, 1));
	result.sin_z = sin(acos(result.cos_z));
	return (result);
}

t_coordinates	rotate_vector(t_coordinates vector, t_matrix matrix)
{
	t_coordinates	result_x;
	t_coordinates	result_y;
	t_coordinates	result_z;

	result_x.x = vector.x;
	result_x.y = vector.y * matrix.cos_x - vector.z * matrix.sin_x;
	result_x.z = vector.y * matrix.sin_x + vector.z * matrix.cos_x;
	result_y.x = result_x.x * matrix.cos_y + result_x.z * matrix.sin_y;
	result_y.y = result_x.y;
	result_y.z = -result_x.x * matrix.sin_y + result_x.z * matrix.cos_y;
	result_z.x = result_y.x * matrix.cos_z - result_y.y * matrix.sin_z;
	result_z.y = result_y.x * matrix.sin_z + result_y.y * matrix.cos_z;
	result_z.z = result_y.z;
	return (result_z);
}

t_coordinates	get_temp(t_vars *vars)
{
	t_coordinates	temp;

	temp = coordinates(0, 1, 0);
	if (vars->current_camera->vector_3d.x == 0
		&& vars->current_camera->vector_3d.z == 0
		&& vars->current_camera->vector_3d.y == 1)
		temp = coordinates(0, 0, -1);
	if (vars->current_camera->vector_3d.x == 0
		&& vars->current_camera->vector_3d.z == 0
		&& vars->current_camera->vector_3d.y == -1)
		temp = coordinates(0, 0, 1);
	return (temp);
}

t_coordinates	rotate_vector_v1(t_coordinates vector, t_vars *vars)
{
	t_coordinates	result_x;
	t_coordinates	result_y;
	t_coordinates	result_z;
	t_coordinates	temp;
	t_coordinates	result;

	temp = get_temp(vars);
	result_z = vars->current_camera->vector_3d;
	result_x = norm_vector(multi_vector(temp, result_z));
	result_y = norm_vector(multi_vector(result_x, result_z));
	result.x = vector.x * result_x.x + vector.y * result_y.x + vector.z
		* result_z.x + vars->current_camera->xyz.x;
	result.y = vector.x * result_x.y + vector.y * result_y.y + vector.z
		* result_z.y + vars->current_camera->xyz.y;
	result.z = vector.x * result_x.z + vector.y * result_y.z + vector.z
		* result_z.z + vars->current_camera->xyz.z;
	result = norm_vector(minus_vector(result, vars->current_camera->xyz));
	return (result);
}
