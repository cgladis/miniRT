#include "miniRT.h"

int	define_obj(char *str)
{
	if (!ft_strncmp(str, "A ", 2) || !ft_strncmp(str, "A	", 2))
		return (255);
	if (!ft_strncmp(str, "R ", 2) || !ft_strncmp(str, "R	", 2))
		return (254);
	if (!ft_strncmp(str, "c ", 2) || !ft_strncmp(str, "c	", 2))
		return (0);
	if (!ft_strncmp(str, "sp ", 3) || !ft_strncmp(str, "sp	", 3))
		return (1);
	if (!ft_strncmp(str, "pl ", 3) || !ft_strncmp(str, "pl	", 3))
		return (2);
	if (!ft_strncmp(str, "tr ", 3) || !ft_strncmp(str, "tr	", 3))
		return (3);
	if (!ft_strncmp(str, "sq ", 3) || !ft_strncmp(str, "sq	", 3))
		return (4);
	if (!ft_strncmp(str, "cy ", 3) || !ft_strncmp(str, "cy	", 3))
		return (5);
	if (!ft_strncmp(str, "l ", 2) || !ft_strncmp(str, "l	", 2))
		return (9);
	return (-1);
}

int	read_triangle_sub(char **str, t_coordinates *coordinates1,
					  t_coordinates *coordinates2, t_coordinates *coordinates3)
{
	int	kol;

	*str = *str + 2;
	*str = delete_str(*str, " \t");
	kol = read_coordinates(coordinates1, *str);
	if (!kol)
		return (0);
	*str = *str + kol;
	*str = delete_str(*str, " \t");
	kol = read_coordinates(coordinates2, *str);
	if (!kol)
		return (0);
	*str = *str + kol;
	*str = delete_str(*str, " \t");
	kol = read_coordinates(coordinates3, *str);
	if (!kol)
		return (0);
	return (kol);
}

int	read_triangle(char *str, t_vars *vars)
{
	t_coordinates	coordinates1;
	t_coordinates	coordinates2;
	t_coordinates	coordinates3;
	t_color			color;
	int				kol;

	kol = read_triangle_sub(&str, &coordinates1, &coordinates2, &coordinates3);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_triangle(vars->obj, (t_param_obj){
			coordinates1, coordinates2, coordinates3, coordinates(0, 0, 0),
			0, 0, color}, vars));
	return (1);
}

int	read_cylinder_sub(char **str, t_coordinates *coord, t_coordinates *vector,
					  double *diameter)
{
	int	kol;

	*str = *str + 2;
	*str = delete_str(*str, " \t");
	kol = read_coordinates(coord, *str);
	if (!kol)
		return (0);
	*str = *str + kol;
	*str = delete_str(*str, " \t");
	kol = read_coordinates(vector, *str);
	if (!kol || (vector->x == 0 && vector->y == 0 && vector->z == 0))
		return (0);
	*str = *str + kol;
	*str = delete_str(*str, " \t");
	kol = read_float(diameter, *str);
	if (!kol || diameter == 0)
		return (0);
	return (kol);
}

int	read_cylinder(char *str, t_vars *vars)
{
	t_coordinates	coord;
	t_coordinates	vector;
	double			d_and_h[2];
	t_color			color;
	int				kol;

	kol = read_cylinder_sub(&str, &coord, &vector, &d_and_h[0]);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_float(&d_and_h[1], str);
	if (!kol || d_and_h[1] == 0)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_cylinder(vars->obj, (t_param_obj){
			coord, coordinates(0, 0, 0), coordinates(0, 0, 0),
			 vector, d_and_h[0], d_and_h[1], color}, vars));
	return (1);
}
