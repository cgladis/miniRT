#include "miniRT.h"

int	read_coordinates(t_coordinates *coordinates, char *str)
{
	int	kol1;
	int	kol2;
	int	kol3;

	kol1 = read_float(&coordinates->x, str);
	if (kol1 == 0 || *(str + kol1) != ',')
		return (0);
	kol2 = read_float(&coordinates->y, str + kol1 + 1);
	if (kol2 == 0 || *(str + kol1 + kol2 + 1) != ',')
		return (0);
	kol3 = read_float(&coordinates->z, str + kol1 + kol2 + 2);
	if (kol3 == 0)
		return (0);
	return (kol1 + kol2 + kol3 + 2);
}

int	read_color(t_color *color, char *str)
{
	int	kol1;
	int	kol2;
	int	kol3;
	int	temp;

	color->color = 0;
	kol1 = read_int(&temp, str);
	color->t_rgb.r = temp;
	if (kol1 == 0 || *(str + kol1) != ',' || temp < 0 || temp > 255)
		return (0);
	kol2 = read_int(&temp, str + kol1 + 1);
	color->t_rgb.g = temp;
	if (kol2 == 0 || *(str + kol1 + kol2 + 1) != ',' || temp < 0 || temp > 255)
		return (0);
	kol3 = read_int(&temp, str + kol1 + kol2 + 2);
	color->t_rgb.b = temp;
	if (kol3 == 0 || temp < 0 || temp > 255)
		return (0);
	return (kol1 + kol2 + kol3 + 2);
}

int	read_ambient(char *str, t_vars *vars)
{
	double	ambient;
	int		kol;
	t_color	color;

	if (vars->read_a)
		return (0);
	str = str + 2;
	str = delete_str(str, " \t");
	kol = read_float(&ambient, str);
	if (!kol)
		return (0);
	vars->canva.ambient = ambient;
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	vars->canva.color = color;
	vars->read_a = 1;
	return (1);
}

int	check_resolution(t_vars *vars, int x, int y)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(vars->mlx, &sizex, &sizey);
	if (x > sizex)
		vars->canva.x = sizex;
	if (y > sizey)
		vars->canva.y = sizey;
	if (x > sizex || y > sizey)
		printf("RESOLUTION = %d %d\n", vars->canva.x, vars->canva.y);
	return (1);
}

int	read_resolution(char *str, t_vars *vars)
{
	int	x;
	int	y;
	int	kol;

	if (vars->read_r)
		return (0);
	str = str + 2;
	str = delete_str(str, " \t");
	kol = read_int(&x, str);
	if (!kol || x == 0)
		return (0);
	vars->canva.x = x;
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_int(&y, str);
	if (!kol || y == 0)
		return (0);
	vars->canva.y = y;
	check_resolution(vars, x, y);
	vars->read_r = 1;
	return (1);
}
