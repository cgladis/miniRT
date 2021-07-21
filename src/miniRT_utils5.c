#include "miniRT.h"

void	move_camera_standart(t_vars *vars, int keycode, int x, int y)
{
	static t_xy	xy;
	static int	first_time = 1;

	if (keycode == -1)
	{
		first_time = 1;
		return ;
	}
	if (first_time)
	{
		xy = (t_xy){x, y};
		first_time = 0;
	}
	if (keycode == 4)
	{
		vars->current_camera->xyz = coordinates_point(vars->current_camera->xyz,
				vars->current_camera->vector_3d, vars->canva.x * 0.03);
	}
	if (keycode == 5)
	{
		vars->current_camera->xyz = coordinates_point(vars->current_camera->xyz,
				vars->current_camera->vector_3d, -vars->canva.x * 0.03);
	}
	xy = (t_xy){x, y};
}

void	move_camera_sub1(int keycode, t_vars *vars)
{
	t_coordinates	vector;

	if (keycode == 4 || keycode == 125)
	{
		vector = rotate_vector_v1(coordinates(0, 1, 0), vars);
		vars->current_camera->xyz = coordinates_point(vars->current_camera->xyz,
				vector, vars->canva.y * 0.03);
	}
	if (keycode == 5 || keycode == 126)
	{
		vector = rotate_vector_v1(coordinates(0, 1, 0), vars);
		vars->current_camera->xyz = coordinates_point(vars->current_camera->xyz,
				vector, -vars->canva.y * 0.03);
	}
}

void	move_camera_sub2(int keycode, t_vars *vars)
{
	t_coordinates	vector;

	if (keycode == 6 || keycode == 124)
	{
		vector = rotate_vector_v1(coordinates(1, 0, 0), vars);
		vars->current_camera->xyz = coordinates_point(vars->current_camera->xyz,
				vector, vars->canva.x * 0.03);
	}
	if (keycode == 7 || keycode == 123)
	{
		vector = rotate_vector_v1(coordinates(1, 0, 0), vars);
		vars->current_camera->xyz = coordinates_point(vars->current_camera->xyz,
				vector, -vars->canva.x * 0.03);
	}
}

void	move_camera(t_vars *vars, int x, int y, int keycode)
{
	static int	x1;
	static int	y1;
	static int	first_time = 1;

	move_camera_sub1(keycode, vars);
	move_camera_sub2(keycode, vars);
	if (keycode == -1)
	{
		first_time = 1;
		return ;
	}
	if (first_time)
	{
		x1 = x;
		y1 = y;
		first_time = 0;
	}
	if (keycode == 2)
	{
		vars->current_camera->vector_3d = norm_vector_obj(
				vars->canva.x / 2 + (x1 - x), vars->canva.y / 2 + (y1 - y),
				vars);
		x1 = x;
		y1 = y;
	}
}

void	next_camera(t_vars *vars)
{
	t_list	*obj_list;
	t_obj	*obj;
	t_obj	*first_camera;
	t_obj	*current_camera;

	printf("next_camera\n");
	obj_list = vars->obj;
	first_camera = NULL;
	current_camera = NULL;
	while (obj_list)
	{
		obj = obj_list->content;
		if (obj->identifier == 0 && first_camera == NULL)
			first_camera = obj;
		if (obj->identifier == 0 && current_camera != NULL)
		{
			vars->current_camera = obj_list->content;
			return ;
		}
		if (obj == vars->current_camera)
			current_camera = obj;
		obj_list = obj_list->next;
	}
	vars->current_camera = first_camera;
}
