/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_color_actions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:11:53 by cgladis           #+#    #+#             */
/*   Updated: 2021/04/29 03:47:15 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	gradient(t_color color1, t_color color2)
{
	t_color	color;

	color = new_color(color1.t_rgb.r * color2.t_rgb.r / 255,
			color1.t_rgb.g * color2.t_rgb.g / 255,
			color1.t_rgb.b * color2.t_rgb.b / 255);
	return (color);
}

t_color	add_color(t_color color1, t_color color2)
{
	t_color	color;

	color.t_rgb.r = clamp(color1.t_rgb.r + color2.t_rgb.r, 0, 255);
	color.t_rgb.g = clamp(color1.t_rgb.g + color2.t_rgb.g, 0, 255);
	color.t_rgb.b = clamp(color1.t_rgb.b + color2.t_rgb.b, 0, 255);
	return (color);
}

t_color	umn_color(t_color color, double n)
{
	if (color.t_rgb.r * n > 255)
		color.t_rgb.r = 255;
	else
		color.t_rgb.r *= n;
	if (color.t_rgb.g * n > 255)
		color.t_rgb.g = 255;
	else
		color.t_rgb.g *= n;
	if (color.t_rgb.b * n > 255)
		color.t_rgb.b = 255;
	else
		color.t_rgb.b *= n;
	return (color);
}

t_color	multi_color(t_color color, t_color light_color, double n)
{
	light_color = umn_color(light_color, n);
	color = add_color(color, light_color);
	return (color);
}

t_color	plus_color(t_color color, t_color light_color, double n)
{
	double	nr;
	double	ng;
	double	nb;

	nr = n / 255 * light_color.t_rgb.r;
	ng = n / 255 * light_color.t_rgb.g;
	nb = n / 255 * light_color.t_rgb.b;
	color = new_color(color.t_rgb.r + color.t_rgb.r * nr, color.t_rgb.g
			+ color.t_rgb.g * ng, color.t_rgb.b + color.t_rgb.b * nb);
	return (color);
}
