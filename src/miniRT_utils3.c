#include "miniRT.h"

void	add_triangle_mode(t_vars *vars, int keycode, t_xy xy, int mouse)
{
	t_obj	*obj;

	obj = last_obj(vars->obj);
	if (keycode == 78 && !mouse)
		obj->size1 *= 0.9;
	if (keycode == 69 && !mouse)
		obj->size1 *= 1.1;
	if (keycode == 1 && mouse)
		create_triangle(vars, xy.x, xy.y);
	if (keycode >= 1 && keycode <= 7 && !mouse)
		return ;
	move_camera_standart(vars, keycode, xy.x, xy.y);
}

void	add_cylinder_mode(t_vars *vars, int keycode, t_xy xy, int mouse)
{
	t_obj	*obj;

	obj = last_obj(vars->obj);
	if (keycode == 78 && !mouse)
		obj->size1 *= 0.9;
	if (keycode == 69 && !mouse)
		obj->size1 *= 1.1;
	if (keycode == 1 && mouse)
		create_cylinder(vars, xy.x, xy.y);
	if (keycode >= 1 && keycode <= 7 && !mouse)
		return ;
	move_camera_standart(vars, keycode, xy.x, xy.y);
}

void	add_plane_mode(t_vars *vars, int keycode, t_xy xy, int mouse)
{
	t_obj	*obj;

	obj = last_obj(vars->obj);
	if (keycode == 78 && !mouse)
		obj->size1 *= 0.9;
	if (keycode == 69 && !mouse)
		obj->size1 *= 1.1;
	if (keycode == 1 && mouse)
		create_plane(vars, xy.x, xy.y);
	if (keycode >= 1 && keycode <= 7 && !mouse)
		return ;
	move_camera_standart(vars, keycode, xy.x, xy.y);
}

void	add_light_mode(t_vars *vars, int keycode, t_xy xy, int mouse)
{
	t_obj	*obj;

	obj = last_obj(vars->obj);
	if (keycode == 78 && !mouse)
		obj->size1 *= 0.9;
	if (keycode == 69 && !mouse)
		obj->size1 *= 1.1;
	if (keycode == 1 && mouse)
		create_light(vars, xy.x, xy.y);
	if (keycode >= 1 && keycode <= 7 && !mouse)
		return ;
	move_camera_standart(vars, keycode, xy.x, xy.y);
}

void	edit_mode(int keycode, int x, int y, t_vars *vars)
{
	if (keycode >=4 && keycode <= 7 && vars->mode == 1)
		move_obj(vars, keycode, x, y);
}
