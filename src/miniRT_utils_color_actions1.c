#include "miniRT.h"

int	clamp(int data, int min, int max)
{
	if (data > max)
		return (max);
	if (data < min)
		return (min);
	return (data);
}

t_color	new_color(int r, int g, int b)
{
	t_color	color;

	color.t_rgb.r = clamp(r, 0, 255);
	color.t_rgb.g = clamp(g, 0, 255);
	color.t_rgb.b = clamp(b, 0, 255);
	return (color);
}
