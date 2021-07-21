#include "miniRT.h"

void	write_sphere(int fd, t_obj *obj)
{
	printf("write_sphere\n");
	write(fd, "sp	", 3);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_float(fd, obj->size1, 2);
	write(fd, "	", 1);
	write_color(fd, obj->rgb);
	write(fd, "\n", 1);
}

void	write_camera(int fd, t_obj *obj)
{
	printf("write_camera\n");
	write(fd, "c	", 2);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_coordinates(fd, obj->vector_3d);
	write(fd, "	", 1);
	write_float(fd, obj->size1, 2);
	write(fd, "\n", 1);
}

void	write_light(int fd, t_obj *obj)
{
	printf("write_light\n");
	write(fd, "l	", 2);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_float(fd, obj->size1, 2);
	write(fd, "	", 1);
	write_color(fd, obj->rgb);
	write(fd, "\n", 1);
}

void	write_plane(int fd, t_obj *obj)
{
	printf("write_plane\n");
	write(fd, "pl	", 3);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_coordinates(fd, obj->vector_3d);
	write(fd, "	", 1);
	write_color(fd, obj->rgb);
	write(fd, "\n", 1);
}

void	write_squere(int fd, t_obj *obj)
{
	printf("write_squere\n");
	write(fd, "sq	", 3);
	write_coordinates(fd, obj->xyz);
	write(fd, "	", 1);
	write_coordinates(fd, obj->vector_3d);
	write(fd, "	", 1);
	write_float(fd, obj->size1, 2);
	write(fd, "	", 1);
	write_color(fd, obj->rgb);
	write(fd, "\n", 1);
}
