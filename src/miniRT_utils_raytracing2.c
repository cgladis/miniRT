#include "miniRT.h"

double	get_t(t_obj *obj, t_coordinates ray,
				t_coordinates camera)
{
	double			t;

	t = 0;
	if (obj->identifier == 1)
		t = intersect_ray_sphere(camera, ray, obj);
	if (obj->identifier == 2)
		t = intersect_ray_plane(camera, ray, obj);
	if (obj->identifier == 3)
		t = intersect_ray_triangle(camera, ray, obj);
	if (obj->identifier == 4)
		t = intersect_ray_square(camera, ray, obj);
	if (obj->identifier == 5)
		t = intersect_ray_cylinder(camera, ray, obj);
	return (t);
}
