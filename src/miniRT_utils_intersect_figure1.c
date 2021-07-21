#include "miniRT.h"

double	intersect_ray_sphere(t_coordinates camera, t_coordinates vector_point,
							   t_obj *obj)
{
	double	k1;
	double	k2;
	double	k3;
	double	t1;
	double	t2;

	k1 = scalar_product(vector_point, vector_point);
	k2 = scalar_product(minus_vector(camera, obj->xyz), vector_point) * 2;
	k3 = scalar_product(minus_vector(camera, obj->xyz), minus_vector(camera,
				obj->xyz)) - obj->size1 * obj->size1 * 0.25;
	if ((k2 * k2 - 4 * k1 * k3) < 0 || k1 == 0)
		return (0);
	t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (t1 < t2)
		return (t1);
	else
		return (t2);
}

double	intersect_ray_square(t_coordinates camera, t_coordinates vector_point,
							   t_obj *obj)
{
	double			k1;
	double			k2;
	double			k3;
	t_coordinates	d;
	double			t;

	k1 = scalar_product(minus_vector(obj->xyz, camera), obj->vector_3d);
	k2 = scalar_product(vector_point, obj->vector_3d);
	t = k1 / k2;
	d = minus_vector(sum_vector(vector_na_chislo(vector_point, t), camera),
			obj->xyz);
	k3 = obj->size1 / 2;
	if (ft_abs(d.x) > k3 || ft_abs(d.y) > k3 || ft_abs(d.z) > k3)
		return (0);
	if (t < 0)
		return (0);
	return (t);
}

double	intersect_ray_triangle(t_coordinates camera, t_coordinates vector_point,
								 t_obj *obj)
{
	t_coordinates	v[4];
	double			k[4];
	double			t;

	v[0] = minus_vector(obj->xyz2, obj->xyz);
	v[1] = minus_vector(obj->xyz3, obj->xyz);
	v[2] = multi_vector(vector_point, v[1]);
	k[0] = scalar_product(v[0], v[2]);
	if (ft_abs(k[0]) < 0.01)
		return (0);
	k[3] = 1 / k[0];
	v[3] = minus_vector(camera, obj->xyz);
	k[1] = scalar_product(v[2], v[3]) * k[3];
	if (k[1] < 0 || k[1] > 1)
		return (0);
	v[3] = multi_vector(v[3], v[0]);
	k[2] = scalar_product(vector_point, v[3]) * k[3];
	if (k[2] < 0 || k[1] + k[2] > 1)
		return (0);
	t = scalar_product(v[1], v[3]) * k[3];
	if (t < 0)
		return (0);
	return (t);
}
