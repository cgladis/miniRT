/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils_screenshot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgladis <cgladis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:13:07 by cgladis           #+#    #+#             */
/*   Updated: 2021/05/03 15:20:32 by cgladis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_pixel(t_vars *vars, int fd)
{
	int	i;
	int	j;
	int	color;

	i = vars->canva.y;
	while (--i >= 0)
	{
		j = 0;
		while (j < vars->canva.x)
		{
			color = *(unsigned int *)(vars->addr + i * vars->line_length
					+ j * vars->bits_per_pixel / 8);
			write(fd, &color, 4);
			j++;
		}
	}
	if (close(fd) < 0)
		error_and_exit("Error in closing file", vars);
	return (1);
}

int	bmp_info(t_vars *vars, int fd)
{
	char				*info;

	info = ft_calloc(BMP_I_SIZE, 1);
	if (!info)
		return (0);
	info[0] = BMP_I_SIZE;
	info[4] = vars->canva.x;
	info[5] = vars->canva.x >> 8;
	info[6] = vars->canva.x >> 16;
	info[7] = vars->canva.x >> 24;
	info[8] = vars->canva.y;
	info[9] = vars->canva.y >> 8;
	info[10] = vars->canva.y >> 16;
	info[11] = vars->canva.y >> 24;
	info[12] = 1;
	info[14] = vars->bits_per_pixel;
	write(fd, info, BMP_I_SIZE);
	free(info);
	get_pixel(vars, fd);
	return (1);
}

int	bmp_header(t_vars *vars, char *filename)
{
	int					fd;
	int					size;
	char				*header;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (0);
	header = ft_calloc(BMP_H_SIZE, 1);
	if (!header)
		return (0);
	size = vars->canva.y * (vars->canva.x) * 4 + BMP_H_SIZE + BMP_I_SIZE ;
	header[0] = 'B';
	header[1] = 'M';
	header[2] = size;
	header[3] = size >> 8;
	header[4] = size >> 16;
	header[5] = size >> 24;
	header[10] = BMP_H_SIZE + BMP_I_SIZE;
	write(fd, header, BMP_H_SIZE);
	free(header);
	if (!bmp_info(vars, fd))
		return (0);
	return (1);
}

void	save_bmp(t_vars *vars)
{
	draw_obj(vars);
	if (!bmp_header(vars, rt_to_bmp(vars->arg[1])))
		error_and_exit("Ошибка записи файла", vars);
	free_vars(vars);
	printf("Скриншот сохранен (%s)\n", vars->arg[1]);
	exit(0);
}
