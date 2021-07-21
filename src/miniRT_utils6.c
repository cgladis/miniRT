#include "miniRT.h"

void	edit_functions_sub2(t_vars *vars, int keycode, char *str, int *i)
{
	if (keycode == 51)
	{
		write(1, "\b", 1);
		str[--*i] = '\0';
	}
	if (keycode >= 123 && keycode <= 126)
		move_camera(vars, 0, 0, keycode);
	if (keycode == 48)
		next_camera(vars);
	if (vars->mode == 2)
		add_sphere_mode(vars, keycode, (t_xy){0, 0}, 0);
	if (vars->mode == 3)
		add_plane_mode(vars, keycode, (t_xy){0, 0}, 0);
	if (vars->mode == 4)
		add_square_mode(vars, keycode, (t_xy){0, 0}, 0);
	if (vars->mode == 5)
		add_triangle_mode(vars, keycode, (t_xy){0, 0}, 0);
	if (vars->mode == 6)
		add_cylinder_mode(vars, keycode, (t_xy){0, 0}, 0);
	if (vars->mode == 9)
		add_light_mode(vars, keycode, (t_xy){0, 0}, 0);
	if (keycode == 53)
		close_w(vars);
}

int	edit_functions_sub(t_vars *vars, char *str)
{
	if (!ft_strncmp(str, "add sphere", 10))
		vars->mode = 2;
	else if (!ft_strncmp(str, "add square", 10))
		vars->mode = 4;
	else if (!ft_strncmp(str, "add light", 9))
		vars->mode = 9;
	else if (!ft_strncmp(str, "add triangle", 12))
		vars->mode = 5;
	else if (!ft_strncmp(str, "add plane", 9))
		vars->mode = 3;
	else if (!ft_strncmp(str, "add cylinder", 12))
		vars->mode = 6;
	else if (!ft_strncmp(str, "add camera", 10))
		create_camera(vars);
	else if (!ft_strncmp(str, "view", 4))
		vars->mode = 0;
	else if (!ft_strncmp(str, "edit", 4))
		vars->mode = 1;
	else if (!ft_strncmp(str, "color ", 6))
		vars->canva.obj_color = read_color_hex(str + 6);
	else if (!ft_strncmp(str, "list", 4))
		print_obj(vars);
	else
		return (0);
	return (1);
}

void	command_clear(t_vars *vars)
{
	vars->need_free_win = 0;
	free_vars(vars);
	vars->need_free_win = 1;
	vars->obj = new_camera(NULL, (t_param_obj){
			coordinates(0, 0, 0), coordinates(0,
				0, 0), coordinates(0, 0, 0),
			coordinates(0, 0, 1),
			DEFAULT_FOV, 0, new_color(0, 0, 0)}, vars);
	vars->current_camera = vars->obj->content;
}

void	edit_functions_sub3(t_vars *vars, char *str, int *i)
{
	if (!ft_strncmp(str, "del ", 4))
		remove_obj(ft_atoi(str + 4), vars);
	else if (!ft_strncmp(str, "export ", 7))
		export(vars, add_rt(str + 7));
	else if (!ft_strncmp(str, "debug", 5))
		debug(vars);
	else if (!ft_strncmp(str, "bmp ", 4))
		bmp_header(vars, add_bmp(str + 4));
	else if (!ft_strncmp(str, "potok", 5))
		vars->potok = !vars->potok;
	else if (!ft_strncmp(str, "clear", 5))
		command_clear(vars);
	else if (!ft_strncmp(str, "import ", 7))
	{
		*i = 0;
		str[0] = 0;
		import(vars, add_rt(str + 7));
	}
	else if (!ft_strncmp(str, "exit", 4))
		exit(0);
	else
		printf("uncorrect command - %s", str);
}

int	edit_functions(int keycode, t_vars *vars)
{
	static char	str[50];
	static int	i = 0;
	char		key;

	key = is_simbol(keycode);
	if (key)
	{
		write(1, &key, 1);
		str[i] = key;
		str[i + 1] = '\0';
		i++;
	}
	edit_functions_sub2(vars, keycode, str, &i);
	if (key == '\n')
	{
		if (!edit_functions_sub(vars, str))
			edit_functions_sub3(vars, str, &i);
		i = 0;
		str[0] = 0;
	}
	return (1);
}
