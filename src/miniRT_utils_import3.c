#include "miniRT.h"

int	read_camera(char *str, t_vars *vars)
{
	t_coordinates	coord;
	double			fov;
	t_coordinates	vector;
	int				kol;

	str = str + 2;
	str = delete_str(str, " \t");
	kol = read_coordinates(&coord, str);
	if (!kol)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_coordinates(&vector, str);
	if (!kol || (vector.x == 0 && vector.y == 0 && vector.z == 0))
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_float(&fov, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_camera(vars->obj, (t_param_obj){
			coord, coordinates(0, 0, 0), coordinates(0, 0, 0),
			vector, fov, 0, new_color(0, 0, 0)}, vars));
	vars->current_camera = last_obj(vars->obj);
	return (1);
}

int	read_light(char *str, t_vars *vars)
{
	t_coordinates	coord;
	double			brightness;
	t_color			color;
	int				kol;

	str = str + 2;
	str = delete_str(str, " \t");
	kol = read_coordinates(&coord, str);
	if (!kol)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_float(&brightness, str);
	if (!kol)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_light(vars->obj, (t_param_obj){coord,
			coordinates(0, 0, 0), coordinates(0, 0, 0),
			coordinates(0, 0, 0), brightness, 0, color}, vars));
	return (1);
}

int	read_sphere(char *str, t_vars *vars)
{
	t_coordinates	coord;
	double			d;
	t_color			color;
	int				kol;

	str = str + 2;
	str = delete_str(str, " \t");
	kol = read_coordinates(&coord, str);
	if (!kol)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_float(&d, str);
	if (!kol || d == 0)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_sphere(vars->obj, (t_param_obj){coord,
			coordinates(0, 0, 0), coordinates(0, 0, 0),
			coordinates(0, 0, 0), d, 0, color}, vars));
	return (1);
}

int	read_plane(char *str, t_vars *vars)
{
	t_coordinates	coord;
	t_coordinates	vector;
	t_color			color;
	int				kol;

	str = str + 2;
	str = delete_str(str, " \t");
	kol = read_coordinates(&coord, str);
	if (!kol)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_coordinates(&vector, str);
	if (!kol || (vector.x == 0 && vector.y == 0 && vector.z == 0))
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_plane(vars->obj, (t_param_obj){coord,
			coordinates(0, 0, 0), coordinates(0, 0, 0), vector,
			0, 0, color}, vars));
	return (1);
}
