#include "miniRT.h"

void	write_float(int fd, double num, int precision)
{
	char	*str;

	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	str = ft_get_float(num, precision);
	write(fd, str, ft_strlen(str));
	free(str);
}

void	write_int(int fd, int num)
{
	char	*str;

	str = ft_itoa(num);
	write(fd, str, ft_strlen(str));
	free(str);
}

void	write_coordinates(int fd, t_coordinates coordinates)
{
	write_float(fd, coordinates.x, 2);
	write(fd, ",", 1);
	write_float(fd, coordinates.y, 2);
	write(fd, ",", 1);
	write_float(fd, coordinates.z, 2);
}

void	write_color(int fd, t_color color)
{
	write_int(fd, color.t_rgb.r);
	write(fd, ",", 1);
	write_int(fd, color.t_rgb.g);
	write(fd, ",", 1);
	write_int(fd, color.t_rgb.b);
}
