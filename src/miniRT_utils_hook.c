#include "miniRT.h"

int	loop_hook(t_vars *vars)
{
	if (vars->potok)
		draw_obj(vars);
	else
		draw_obj_light(vars);
	if (vars->img == NULL)
		exit(0);
	mouse_press_hook(0, (t_xy){0, 0}, vars, 0);
	if (vars->debug_win)
		refresh_debug_win(vars);
	return (1);
}

void 	mouse_press_hook_sub(int keycode, int x, int y, t_vars *vars)
{
	if (vars->mode == 1)
		edit_mode(keycode, x, y, vars);
	if (keycode >=4 && keycode <= 7 && vars->mode == 0)
		move_camera(vars, x, y, keycode);
	if (vars->mode == 2)
		add_sphere_mode(vars, keycode, (t_xy){x, y}, 1);
	if (vars->mode == 3)
		add_plane_mode(vars, keycode, (t_xy){x, y}, 1);
	if (vars->mode == 4)
		add_square_mode(vars, keycode, (t_xy){x, y}, 1);
	if (vars->mode == 5)
		add_triangle_mode(vars, keycode, (t_xy){x, y}, 1);
	if (vars->mode == 6)
		add_cylinder_mode(vars, keycode, (t_xy){x, y}, 1);
	if (vars->mode == 9)
		add_light_mode(vars, keycode, (t_xy){x, y}, 1);
}

int	mouse_press_hook(int key_code, t_xy xy, t_vars *vars, int press_key)
{
	static int	presskey;
	static int	keycode;

	if (press_key != 0)
	{
		presskey = press_key;
		keycode = key_code;
	}
	if (presskey == 2)
	{
		move_camera(vars, xy.x, xy.y, -1);
		return (1);
	}
	if (press_key == 0)
		mlx_mouse_get_pos(vars->win, &xy.x, &xy.y);
	if (xy.x < 0 || xy.y < 0 || xy.x > vars->canva.x || xy.y > vars->canva.y)
	{
		return (1);
	}
	if (keycode == 2 && presskey == 1)
		move_camera(vars, xy.x, xy.y, keycode);
	if (press_key == 1)
		mouse_press_hook_sub(keycode, xy.x, xy.y, vars);
	return (1);
}

int	push_mouse_key(int keycode, int x, int y, t_vars *vars)
{
	return (mouse_press_hook(keycode, (t_xy){x, y}, vars, 1));
}

int	release_mouse_key(int keycode, int x, int y, t_vars *vars)
{
	return (mouse_press_hook(keycode, (t_xy){x, y}, vars, 2));
}
