#include "miniRT.h"

char	*rt_get_float(double num, int precision)
{
	char	*str;

	str = ft_strdup("");
	if (num < 0)
	{
		str = ft_cont_str(str, ft_strdup("-"));
		num = -num;
	}
	str = ft_cont_str(str, ft_get_float(num, precision));
	return (str);
}

char	*rt_get_int(int num)
{
	char	*str;

	str = ft_itoa(num);
	return (str);
}

char	*rt_get_coordinates(t_coordinates coordinates)
{
	char	*str;

	str = rt_get_float(coordinates.x, 2);
	str = ft_cont_str(str, ft_strdup(", "));
	str = ft_cont_str(str, rt_get_float(coordinates.y, 2));
	str = ft_cont_str(str, ft_strdup(", "));
	str = ft_cont_str(str, rt_get_float(coordinates.z, 2));
	return (str);
}

char	*rt_get_color(t_color color)
{
	char	*str;

	str = rt_get_int(color.t_rgb.r);
	str = ft_cont_str(str, ft_strdup(", "));
	str = ft_cont_str(str, rt_get_int(color.t_rgb.g));
	str = ft_cont_str(str, ft_strdup(", "));
	str = ft_cont_str(str, rt_get_int(color.t_rgb.b));
	return (str);
}
