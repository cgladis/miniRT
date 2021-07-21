//
// Created by Commando Gladis on 4/28/21.
//

#include "miniRT.h"

t_coordinates	coordinates(double x, double y, double z)
{
	t_coordinates	new_coordinates;

	new_coordinates.x = x;
	new_coordinates.y = y;
	new_coordinates.z = z;
	return (new_coordinates);
}

double	calc_length_to_canva(double FOV, int length_x)
{
	return ((length_x / 2) / (tan(FOV * M_PI / 360)));
}

t_coordinates	coordinates_point(t_coordinates camera,
					t_coordinates norm_vector, double t)
{
	t_coordinates	result;

	result.x = camera.x + t * norm_vector.x;
	result.y = camera.y + t * norm_vector.y;
	result.z = camera.z + t * norm_vector.z;
	return (result);
}

t_coordinates	vector_na_chislo(t_coordinates vector, double t)
{
	t_coordinates	result;

	result.x = t * vector.x;
	result.y = t * vector.y;
	result.z = t * vector.z;
	return (result);
}

t_coordinates	multi_vector(t_coordinates v1, t_coordinates v2)
{
	t_coordinates	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
