#include "miniRT.h"

int	read_int_rev(int *n, char *str)
{
	int	kol;

	kol = 0;
	*n = 0;
	while (ft_isdigit(*str))
	{
		*n = *n * 10 + *str - '0';
		kol += 1;
		str++;
	}
	return (kol);
}

int	read_int(int *n, char *str)
{
	int	minus;
	int	kol;

	minus = 1;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	kol = read_int_rev(n, str);
	*n = *n * minus;
	if (kol > 9)
		return (0);
	if (kol > 0)
	{
		if (minus == -1)
			kol += 1;
	}
	return (kol);
}

int	read_square_sub(char **str, t_coordinates *coord, t_coordinates *vector)
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
	return (kol);
}

int	read_square(char *str, t_vars *vars)
{
	t_coordinates	coord;
	t_coordinates	vector;
	double			side;
	t_color			color;
	int				kol;

	kol = read_square_sub(&str, &coord, &vector);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_float(&side, str);
	if (!kol)
		return (0);
	str = str + kol;
	str = delete_str(str, " \t");
	kol = read_color(&color, str);
	if (!kol)
		return (0);
	ft_lstadd_back(&vars->obj, new_square(vars->obj, (t_param_obj){
			coord, coordinates(0, 0, 0), coordinates(0, 0, 0),
			vector, side, 0, color}, vars));
	return (1);
}
