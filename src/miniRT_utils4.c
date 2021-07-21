#include "miniRT.h"

void	add_sphere_mode(t_vars *vars, int keycode, t_xy xy, int mouse)
{
	t_obj	*obj;

	obj = last_obj(vars->obj);
	if (keycode == 78 && !mouse)
		obj->size1 *= 0.9;
	if (keycode == 69 && !mouse)
		obj->size1 *= 1.1;
	if (keycode == 1 && mouse)
		create_sphere(vars, xy.x, xy.y);
	if (keycode >= 1 && keycode <= 7 && !mouse)
		return ;
	move_camera_standart(vars, keycode, xy.x, xy.y);
}

void	add_square_mode(t_vars *vars, int keycode, t_xy xy, int mouse)
{
	t_obj	*obj;

	obj = last_obj(vars->obj);
	if (keycode == 78 && !mouse)
		obj->size1 *= 0.9;
	if (keycode == 69 && !mouse)
		obj->size1 *= 1.1;
	if (keycode == 1 && mouse)
		create_square(vars, xy.x, xy.y);
	if (keycode >= 1 && keycode <= 7 && !mouse)
		return ;
	move_camera_standart(vars, keycode, xy.x, xy.y);
}

void	move_obj(t_vars *vars, int keycode, int x, int y)
{
	t_coordinates	vector_point;
	t_list			*list_obj;
	t_obj			*obj;

	list_obj = vars->obj;
	vector_point = norm_vector_obj(x, y, vars);
	while (list_obj)
	{
		obj = list_obj->content;
		if (obj->identifier == 1)
			if (intersect_ray_sphere(vars->current_camera->xyz, vector_point,
					obj))
				break ;
		list_obj = list_obj->next;
	}
	if (keycode == 4)
		obj->xyz = coordinates_point(obj->xyz, vector_point, 20);
	if (keycode == 5)
		obj->xyz = coordinates_point(obj->xyz, vector_point, -20);
	if (keycode == 6)
		obj->size1 *= 0.9;
	if (keycode == 7)
		obj->size1 *= 1.1;
	draw_obj(vars);
}
