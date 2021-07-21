#include "miniRT.h"

void	write_cylinder(int fd, t_obj *obj)
{
	printf("write_cylinder\n");
	write(fd, "cy	", 3);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_coordinates(fd, obj->vector_3d);
	write(fd, "	", 1);
	write_float(fd, obj->size1, 2);
	write(fd, "	", 1);
	write_float(fd, obj->size2, 2);
	write(fd, "	", 1);
	write_color(fd, obj->rgb);
	write(fd, "\n", 1);
}

void	write_triangle(int fd, t_obj *obj)
{
	printf("write_triangle\n");
	write(fd, "tr	", 3);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_coordinates(fd, obj->xyz2);
	write(fd, "	", 1);
	write_coordinates(fd, obj->xyz3);
	write(fd, "	", 1);
	write_color(fd, obj->rgb);
	write(fd, "\n", 1);
}

void	write_ambient(int fd, double n, t_color color)
{
	printf("write_ambient\n");
	write(fd, "A	", 2);
	write_float(fd, n, 2);
	write(fd, "	", 1);
	write_color(fd, color);
	write(fd, "\n", 1);
}

void	write_resolution(int fd, int x, int y)
{
	printf("write_resolution\n");
	write(fd, "R	", 2);
	write_int(fd, x);
	write(fd, " ", 1);
	write_int(fd, y);
	write(fd, "\n", 1);
}
