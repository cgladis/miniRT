#include "miniRT.h"

t_coordinates	minus_vector(t_coordinates vector1, t_coordinates vector2)
{
	t_coordinates	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return (result);
}

double	scalar_product(t_coordinates v1, t_coordinates v2)
{
	double	result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (result);
}

t_coordinates	sum_vector(t_coordinates vector1, t_coordinates vector2)
{
	t_coordinates	result;

	result.x = vector1.x + vector2.x;
	result.y = vector1.y + vector2.y;
	result.z = vector1.z + vector2.z;
	return (result);
}

double	vector_length(t_coordinates vector)
{
	double	length;

	length = sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z);
	return (length);
}

t_coordinates	norm_vector(t_coordinates vector)
{
	double	length;
	double	length_inv;

	length = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	if (length > 0)
	{
		length_inv = 1 / sqrt(length);
		vector.x = vector.x * length_inv;
		vector.y = vector.y * length_inv;
		vector.z = vector.z * length_inv;
	}
	return (vector);
}
